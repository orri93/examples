package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;

public class SayRouter extends RouteBuilder {
	@Override
	public void configure() {
		from("timer:hello?period={{timer.period:60s}}").routeId("hello").transform()
		    .method("sayBean", "saySomething")
		    .filter(simple("${body} contains 'foo'")).to("log:say").end()
		    .to("stream:out");
	}

}
