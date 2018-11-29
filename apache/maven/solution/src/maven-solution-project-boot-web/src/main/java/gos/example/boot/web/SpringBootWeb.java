package gos.example.boot.web;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.stereotype.Component;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;

import gos.example.camel.route.BookOrderRoute;
import gos.example.camel.route.RestRoute;
import gos.example.camel.route.SayRouter;

@SpringBootApplication
@EnableAutoConfiguration
@ComponentScan(basePackages = {
		"gos.example.boot",
		"gos.example.camel.processor",
		"gos.example.repository",
		"gos.example.component",
		"gos.example.provider",
		"gos.example.item"},
basePackageClasses = {
		gos.example.configuration.SecurityConfiguration.class})
@EnableJpaRepositories("gos.example.repository")
@EntityScan("gos.example.item")
public class SpringBootWeb extends SpringBootServletInitializer {
	
	public static void main(String[] args) {
		SpringApplication.run(SpringBootWeb.class, args);
	}
	
	@Component
	class MySpringBootRouter extends SayRouter {}

	@Component
	class RestApi extends RestRoute {}

	@Component
	class Backend extends BookOrderRoute {}
}

