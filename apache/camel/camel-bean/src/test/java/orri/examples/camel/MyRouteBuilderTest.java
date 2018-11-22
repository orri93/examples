package orri.examples.camel;

import static org.junit.Assert.*;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.camel.ServiceStatus;
import org.apache.camel.builder.ExchangeBuilder;
import org.apache.camel.test.spring.CamelSpringTestSupport;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;

public class MyRouteBuilderTest extends CamelSpringTestSupport {

	@Override
	protected AbstractApplicationContext createApplicationContext() {
		AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext();
		ctx.scan("orri.examples.camel");
		ctx.refresh();
		return ctx;
	}

	@Test
	public void should_hello_route_be_running() throws Exception {
		CamelContext context = context();
		assertNotNull(context);
		ServiceStatus status = context.getRouteStatus(Constants.NodeId);
		assertNotNull(status);
		boolean isStarted = status.isStarted();
		assertTrue(isStarted);
	}
}
