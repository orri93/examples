package gos.example.camel;

import java.io.File;
import java.io.IOException;
import java.util.Map;
import java.util.Properties;

import org.apache.camel.EndpointInject;
import org.apache.camel.Produce;
import org.apache.camel.ProducerTemplate;
import org.apache.camel.RoutesBuilder;
import org.apache.camel.component.mock.MockEndpoint;
import org.apache.camel.test.junit4.CamelTestSupport;
import org.apache.camel.test.spring.CamelSpringTestSupport;
import org.junit.Assert;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.support.AbstractApplicationContext;
import org.springframework.core.env.MapPropertySource;
import org.springframework.core.env.PropertySource;
import org.springframework.core.io.ClassPathResource;
import org.springframework.core.io.Resource;
import org.springframework.test.context.junit4.SpringRunner;

import gos.example.camel.processor.FileContentProcessor;
import gos.example.camel.route.JmsRoute;
import gos.example.camel.route.SimpleRoute;
import gos.example.configuration.YamlPropertySourceLoader;
import gos.example.parser.YamlPropertyConverter;
import gos.example.parser.YamlPropertyConverterImpl;

@RunWith(SpringRunner.class)
//@ContextConfiguration({ "test/resources/application.yml" })
public class IntegrationTest extends CamelSpringTestSupport {
	Logger Log = LoggerFactory.getLogger(FileContentProcessor.class);

	private static final String ExpectedFileLocation = "src/main/resources/static/";

	@EndpointInject(uri = "mock:result")
	protected MockEndpoint resultEndpoint;

	@Produce(uri = "direct:start")
	protected ProducerTemplate template;

	@Override
	protected Properties useOverridePropertiesWithPropertiesComponent() {
		Properties properties = new Properties();
		YamlPropertyConverter converter = new YamlPropertyConverterImpl();
		try {
			Map<String, Properties> map = converter
			    .convert("src/test/resources/application.yml");
			if (map.size() > 0) {
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		properties.setProperty("spring.activemq.broker-url",
		    "tcp://localhost:61616");
		return properties;
	}

	@Override
	protected RoutesBuilder createRouteBuilder() throws Exception {
		return new SimpleRoute();
	}

	@Test
	public void testSimpleRoute() throws InterruptedException {
		Thread.sleep(5000);
		File file = new File(ExpectedFileLocation);
		assertTrue(file.isDirectory());
		assertEquals(1, file.listFiles().length);

	}

	// @Test
	public void testCamelRulesDeployCorrectlyInSpring() throws Exception {
		// let's boot up the Spring application context for 2 seconds to check that
		// it works OK
		CamelDevelopment.main(new String[] { "-duration", "2s", "-cc",
		    "gos.example.camel.CamelDevelopment"/*
		                                         * , "-bp",
		                                         * "gos.example.camel.route"
		                                         */ });
	}

	@Override
	protected AbstractApplicationContext createApplicationContext() {
		AnnotationConfigApplicationContext context =
				new AnnotationConfigApplicationContext();
		context.register(IntegrationTestConfiguration.class);
		context.refresh();
		return context;
	}

	/*
	 * @Override protected Properties
	 * useOverridePropertiesWithPropertiesComponent() { YamlPropertySourceLoader
	 * loader = new YamlPropertySourceLoader(); try { PropertySource<?>
	 * applicationYamlPropertySource = loader.load( "properties", new
	 * ClassPathResource("application.yml"),null); Map source =
	 * ((MapPropertySource) applicationYamlPropertySource).getSource(); Properties
	 * properties = new Properties(); properties.putAll(source); return
	 * properties; } catch (IOException e) {
	 * Log.error("Config file cannot be found."); }
	 * 
	 * return null; }
	 */
}
