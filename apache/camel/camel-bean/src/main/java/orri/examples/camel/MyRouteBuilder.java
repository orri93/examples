package orri.examples.camel;

import org.apache.camel.builder.RouteBuilder;

/**
 * A Camel Java DSL Router
 */
public class MyRouteBuilder extends RouteBuilder {
	/**
	 * Let's configure the Camel routing rules using Java code...
	 */
	public void configure() {
		// here is a sample which processes the input files
		// (leaving them in place - see the 'noop' flag)
		// then performs content based routing on the message using XPath
		Generator generator = new Generator();
		from(Constants.TimerUrl).id(Constants.NodeId).routeId(Constants.RouteId).
		bean(generator, "generateItem").to("log:my");
		    //.to("file:data-selection.html?charset=utf-8");
	}

}
