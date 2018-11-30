package gos.examples.xsd.forms.configuration;

import java.util.concurrent.TimeUnit;

import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.CacheControl;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@EnableWebMvc
@Configuration
@ComponentScan({ "gos.examples.xsd.forms" })
public class SpringConfiguration implements WebMvcConfigurer {
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
