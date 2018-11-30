package gos.example.project.web.configuration;

import java.util.concurrent.TimeUnit;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;
import org.springframework.context.annotation.PropertySource;
import org.springframework.http.CacheControl;
import org.springframework.web.servlet.ViewResolver;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;
import org.springframework.web.servlet.view.InternalResourceViewResolver;

import gos.example.configuration.SecurityConfiguration;

@EnableWebMvc
@Configuration
@ComponentScan(basePackages = { "gos.examples.xsd.forms" })
//@PropertySource(value = {"classpath:fds.properties"})
@Import({/* PersistenceConfiguration.class, */ SecurityConfiguration.class, WebCamelConfiguration.class})
public class SpringConfiguration implements WebMvcConfigurer {

	/*
  @Bean(name = "SFS")
  public ViewResolver viewResolver() {
      InternalResourceViewResolver viewResolver = new InternalResourceViewResolver();
      viewResolver.setSuffix(".zul");
      return viewResolver;
  }
  */

	
  @Override
  public void addResourceHandlers(ResourceHandlerRegistry registry) {
    // Register resource handler for CSS and JS
    registry.addResourceHandler("/css/**")
        .addResourceLocations(
            //"classpath:/resources/static/css/"
            "classpath:/static/css/"
            //"classpath:/css/"
            )
        .setCacheControl(CacheControl.maxAge(2, TimeUnit.HOURS).cachePublic());
    registry.addResourceHandler("/js/**")
        .addResourceLocations(
            //"classpath:/resources/static/js/"
            "classpath:/static/js/"
            //"classpath:/js/"
            )
        .setCacheControl(CacheControl.maxAge(2, TimeUnit.HOURS).cachePublic());
  }
}
