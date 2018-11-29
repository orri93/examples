package gos.example.boot.web;

import java.util.concurrent.TimeUnit;

import org.springframework.http.CacheControl;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

public class WebConfigurer implements WebMvcConfigurer {
	@Override
  public void addResourceHandlers(ResourceHandlerRegistry registry) {
    // Register resource handler for CSS and JS
    registry.addResourceHandler("/rest/css/**")
        .addResourceLocations(
            //"classpath:/resources/static/css/"
            "classpath:/form/html/css/"
            //"classpath:/css/"
            )
        .setCacheControl(CacheControl.maxAge(2, TimeUnit.HOURS).cachePublic());
    registry.addResourceHandler("/rest/js/**")
        .addResourceLocations(
            //"classpath:/resources/static/js/"
            "classpath:/form/html/js/"
            //"classpath:/js/"
            )
        .setCacheControl(CacheControl.maxAge(2, TimeUnit.HOURS).cachePublic());
  }
}
