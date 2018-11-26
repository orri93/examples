package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;
import org.springframework.beans.factory.annotation.Autowired;

import gos.example.component.ReceiveBean;

public class JmsRoute extends RouteBuilder {
	@Autowired
	private ReceiveBean receiveBean;

	@Override
	public void configure() throws Exception {
		// you can configure the route rule with Java DSL here

		// populate the message queue with some messages
		from("file:src/data?noop=true").to("jms:queue:inbox");

		from("jms:queue:inbox").bean(receiveBean);
	}
}
