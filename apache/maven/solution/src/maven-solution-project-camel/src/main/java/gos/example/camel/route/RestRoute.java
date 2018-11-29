package gos.example.camel.route;

import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.env.Environment;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestMapping;

import gos.example.camel.processor.FileContentProcessor;
import gos.example.provider.BookOrderAccess;

public class RestRoute extends RouteBuilder {

	@Autowired
	private Environment env;

	@Autowired
	FileContentProcessor processor;
	
	@RequestMapping(value="/api/getImageList", method=RequestMethod.GET, headers="Accept=application/json")
	public ResponseEntity<Collection<String>> getImageList(){
	}
	
	@Override
	public void configure() {

		restConfiguration().contextPath("/rest").apiContextPath("/api-doc")
		    .apiProperty("api.title", "Camel REST API")
		    .apiProperty("api.version", "1.0")
		    .apiProperty("cors", "true")
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

		rest("/form").produces(MediaType.TEXT_HTML_VALUE)
		    .bindingMode(RestBindingMode.auto).description("Form REST service")
		    .get("/").description("Display a HTML form").route().routeId("form-api")
		    .setBody(simple("source-selection.html"))
		    .setHeader("fileprocessor.filepath",
		        simple("src/main/resources/form/html/"))
		    .setHeader(Exchange.CONTENT_TYPE, simple(MediaType.TEXT_HTML_VALUE))
		    .process(this.processor);
/*
		rest("/css").produces("text/css").bindingMode(RestBindingMode.auto)
		    .description("CSS Service").get("/{cssFile}")
		    .description("Resolve a CSS file").route().routeId("form-css")
		    .setBody(simple("${header.cssFile}"))
		    .setHeader("fileprocessor.filepath",
		        simple("src/main/resources/form/html/css/"))
		    .setHeader(Exchange.CONTENT_TYPE, simple("text/css"))
		    .process(this.processor);
	*/ /*
		rest("/js").produces("application/javascript").bindingMode(RestBindingMode.auto)
		    .description("JS Service").get("/{jsFile}")
		    .description("Resolve a JS file").route().routeId("form-js")
		    .setBody(simple("${header.jsFile}"))
		    .setHeader("fileprocessor.filepath",
		        simple("src/main/resources/form/html/js/"))
		    .setHeader(Exchange.CONTENT_TYPE, simple("application/javascript"))
		    .process(this.processor);
*/
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
