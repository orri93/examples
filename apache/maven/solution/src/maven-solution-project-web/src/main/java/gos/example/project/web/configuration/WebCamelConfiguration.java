package gos.example.project.web.configuration;

import java.util.List;
import javax.annotation.Resource;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.camel.CamelContext;
import org.apache.camel.Route;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.component.properties.PropertiesComponent;
import org.apache.camel.spring.javaconfig.CamelConfiguration;
import org.apache.camel.spring.spi.SpringTransactionPolicy;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;
import org.springframework.context.annotation.Import;
import org.springframework.context.annotation.ComponentScan.Filter;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.stereotype.Component;

import gos.example.camel.route.BookOrderRoute;
import gos.example.camel.route.RestRoute;
import gos.example.camel.route.SayRouter;

@Configuration
@ComponentScan(basePackages = {
		"gos.example.boot",
		"gos.example.camel.route",
		"gos.example.camel.processor",
		"gos.example.repository",
		"gos.example.component",
		"gos.example.provider",
		"gos.example.item" },
    basePackageClasses = {
                gos.example.configuration.SecurityConfiguration.class,
                gos.example.component.ReceiveBean.class,
                gos.example.camel.route.JmsRoute.class })
@EnableJpaRepositories("gos.example.repository")
//@Import(PersistenceConfiguration.class)
public class WebCamelConfiguration extends CamelConfiguration {

	/*
	@Value("${logging.trace.enabled}")
	private Boolean tracingEnabled;
	*/

	@Component
	class MySpringBootRouter extends SayRouter {
	}

	@Component
	class RestApi extends RestRoute {
	}

	@Component
	class Backend extends BookOrderRoute {
	}

	// @Resource
	// PersistenceConfiguration persistenceConfiguration;

	@Override
	protected void setupCamelContext(CamelContext camelContext) throws Exception {
		// setup the ActiveMQ component
		ActiveMQConnectionFactory connectionFactory = new ActiveMQConnectionFactory();
		connectionFactory.setBrokerURL(
		    "vm://localhost?broker.persistent=false&broker.useJmx=false");

		// and register it into the CamelContext
		JmsComponent answer = new JmsComponent();
		answer.setConnectionFactory(connectionFactory);
		camelContext.addComponent("jms", answer);

		/*
		 * PropertiesComponent pc = new PropertiesComponent();
		 * pc.setLocation("classpath:application.properties");
		 * camelContext.addComponent("properties", pc); // see if trace logging is
		 * turned on if (tracingEnabled) { camelContext.setTracing(true); }
		 */

		super.setupCamelContext(camelContext);
	}

	@Bean
	public SpringTransactionPolicy camelTransactionPolicy() {
		SpringTransactionPolicy springTransactionPolicy = new SpringTransactionPolicy();
		// springTransactionPolicy.setTransactionManager(persistenceConfiguration.transactionManager(persistenceConfiguration.entityManagerFactory().getObject()));
		springTransactionPolicy.setPropagationBehaviorName("PROPAGATION_REQUIRED");
		return springTransactionPolicy;
	}

}
