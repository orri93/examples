package gos.example.camel;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.FilterType;
import org.springframework.context.annotation.ComponentScan.Filter;

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
public class IntegrationTestConfiguration {

}
