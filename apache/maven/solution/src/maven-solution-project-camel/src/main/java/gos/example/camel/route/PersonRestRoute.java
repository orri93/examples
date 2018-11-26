package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;

import gos.example.provider.PersonProvider;

public class PersonRestRoute extends RouteBuilder {
	
	private String path;
	private int port;
	
	public PersonRestRoute(String path, int port) {
		this.path = path;
		this.port = port;
	}
	
	@Override
	public void configure() throws Exception {

		// configure we want to use servlet as the component for the rest DSL
		// and we enable json binding mode
		restConfiguration().component("servlet").bindingMode(RestBindingMode.json)
		    // and output using pretty print
		    .dataFormatProperty("prettyPrint", "true")
		    // setup context path and port number that Apache Tomcat will deploy
		    // this application with, as we use the servlet component, then we
		    // need to aid Camel to tell it these details so Camel knows the url
		    // to the REST services.
		    // Notice: This is optional, but needed if the RestRegistry should
		    // enlist accurate information. You can access the RestRegistry
		    // from JMX at runtime
		    .contextPath(this.path).port(this.port);

		// this provider REST service is json only
		rest("/provider").description("Provider rest service")
		    .consumes("application/json").produces("application/json")

		    .get("/{id}").description("Find provider by id")
		    .outType(PersonProvider.class)
		    .to("bean:providerService?method=getProvider(${header.id})")

		    .put().description("Updates or create a provider")
		    .type(PersonProvider.class)
		    .to("bean:providerService?method=updateProvider")

		    .get().description("List all providers")
		    .outTypeList(PersonProvider.class)
		    .to("bean:providerService?method=listProviders")

		    .get("/search").description("Search by Zip")
		    .outTypeList(PersonProvider.class).route()
		    .log("Incoming zip: ${header.zip}")
		    .to("bean:providerService?method=searchByZip(${header.zip})").endRest();
	}
}
