package gos.example.boot;

import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.core.env.Environment;
import org.springframework.stereotype.Component;

@SpringBootApplication
@ComponentScan(basePackages = {
		"gos.examples.boot",
		"gos.examples.configuration" },
basePackageClasses = { gos.example.configuration.SecurityConfiguration.class })
public class SpringBootDevelopment extends SpringBootServletInitializer {

	@Autowired
	private Environment env;
	
	public static void main(String[] args) {
		SpringApplication.run(SpringBootDevelopment.class, args);
	}

	@Component
	class MySpringBootRouter extends RouteBuilder {

		@Override
		public void configure() {
			from("timer:hello?period={{timer.period}}").routeId("hello").transform()
			    .method("myBean", "saySomething")
			    .filter(simple("${body} contains 'foo'")).to("log:foo").end()
			    .to("stream:out");
		}
	}

	@Component
	class RestApi extends RouteBuilder {

		@Autowired
		FileContentProcessor processor;

		@Override
		public void configure() {
			
			restConfiguration().contextPath("/rest")
					.apiContextPath("/api-doc")
			    .apiProperty("api.title", "Camel REST API")
			    .apiProperty("api.version", "1.0").apiProperty("cors", "true")
			    .apiContextRouteId("doc-api")
			    .port(env.getProperty("server.port", "8080"))
			    .bindingMode(RestBindingMode.auto);
			
			rest("/html").produces("test/html").bindingMode(RestBindingMode.auto)
				.description("HTML REST service").get("/")
				.description("Display the HTML").route().routeId("html-api")
				.setBody(simple("test.html"))
				.setHeader("fileprocessor.filepath", simple("src/main/resources/"))
				.setHeader(Exchange.CONTENT_TYPE, simple("text/html"))
				.process(this.processor);

			rest("/test").bindingMode(RestBindingMode.json)
			    .description("Test REST service").get("/")
			    .description("Show all the test").route().routeId("test-api")
			    .setBody(simple("test.html"))
			    .setHeader("fileprocessor.filepath", simple("src/main/resources/"))
			    .process(this.processor);

			rest("/books").bindingMode(RestBindingMode.json)
			    .description("Books REST service").get("/")
			    .description("The list of all the books").route().routeId("books-api")
			    .bean(Database.class, "findBooks").endRest().get("order/{id}")
			    .description("Details of an order by id").route().routeId("order-api")
			    .bean(Database.class, "findOrder(${header.id})");
		}
	}

	@Component
	class Backend extends RouteBuilder {

		@Override
		public void configure() {
			from("timer://runOnce?repeatCount=1&delay=1s")
			    .bean("orderService", "generateBook(1)")
			    .to("jpa:gos.examples.example.project.boot.items.Book")
			    .log("Inserted new book ${body.id}")
			    .bean("orderService", "generateBook(2)")
			    .to("jpa:gos.examples.example.project.boot.items.Book")
			    .log("Inserted new book ${body.id}");

			// A first route generates some orders and queue them in DB
			from(
			    "timer:new-order?delay=10s&period={{example.generateOrderPeriod:2s}}")
			        .routeId("generate-order").bean("orderService", "generateOrder")
			        .to("jpa:gos.examples.example.project.boot.items.Order")
			        .log("Inserted new order ${body.id}");

			// A second route polls the DB for new orders and processes them
			from("jpa:gos.examples.example.project.boot.items.Order"
			    + "?consumer.namedQuery=new-orders"
			    + "&consumer.delay={{example.processOrderPeriod:5s}}"
			    + "&consumeDelete=false").routeId("process-order").log(
			        "Processed order #id ${body.id} with ${body.amount} copies of the «${body.book.description}» book");
		}
	}

}
