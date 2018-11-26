package gos.example.camel;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.camel.CamelContext;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.spring.javaconfig.CamelConfiguration;
import org.apache.camel.spring.javaconfig.Main;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.ComponentScan.Filter;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;

@Configuration
@ComponentScan(
		basePackages = {
				"gos.example.component",
				"gos.example.camel.route"
		},
		excludeFilters = {
				@Filter(type = FilterType.ASSIGNABLE_TYPE,
						value =  {
								gos.example.component.OrderService.class					
						}),
		},
		basePackageClasses = {
		gos.example.component.ReceiveBean.class,
		gos.example.camel.route.JmsRoute.class})
//@PropertySource(factory = YamlPropertySourceFactory.class, value = "classpath:application.yml")
public class CamelDevelopment extends CamelConfiguration {
  public static void main( String[] args ) throws Exception {
  	Main main = new Main();
    main.setConfigClass(CamelDevelopment.class);
    main.run();
  }
  
  @Override
  protected void setupCamelContext(CamelContext camelContext) throws Exception {
      // setup the ActiveMQ component
      ActiveMQConnectionFactory connectionFactory = new ActiveMQConnectionFactory();
      connectionFactory.setBrokerURL("vm://localhost?broker.persistent=false&broker.useJmx=false");

      // and register it into the CamelContext
      JmsComponent answer = new JmsComponent();
      answer.setConnectionFactory(connectionFactory);
      camelContext.addComponent("jms", answer);
  }
}
