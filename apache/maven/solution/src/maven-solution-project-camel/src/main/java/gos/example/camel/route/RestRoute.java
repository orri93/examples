package gos.example.camel.route;

import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;
import gos.example.camel.processor.FileContentProcessor;
import gos.example.provider.BookOrderAccess;

public class RestRoute extends RouteBuilder {
	
	@Autowired
	private Environment env;
	
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
		    .bean(BookOrderAccess.class, "findBooks").endRest().get("order/{id}")
		    .description("Details of an order by id").route().routeId("order-api")
		    .bean(BookOrderAccess.class, "findOrder(${header.id})");
	}

}
