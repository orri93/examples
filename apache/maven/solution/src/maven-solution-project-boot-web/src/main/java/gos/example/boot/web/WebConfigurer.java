package gos.example.boot.web;

import java.util.concurrent.TimeUnit;

import org.springframework.http.CacheControl;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.ViewResolverRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

public class WebConfigurer implements WebMvcConfigurer {
  

  /*
   * @Override public void addResourceHandlers(ResourceHandlerRegistry registry)
   * {
   * 
   * String rootpath = "/rest"; String formpath = "/form";
   * 
   * String[] cssResources = new String[] { rootpath + formpath + "/css/**",
   * rootpath + "/css/**", formpath + "/css/**" };
   * 
   * String[] jsResources = new String[] { rootpath + formpath + "/js/**",
   * rootpath + "/js/**", formpath + "/js/**" };
   * 
   * String[] cssLocations = new String[] { "classpath:/form/html/css/",
   * "classpath:/static/css/", "file://src/main/webapp/static/css/",
   * "file://main/webapp/static/css/", "file://webapp/static/css/",
   * "file://static/css/", };
   * 
   * String[] jsLocations = new String[] { "classpath:/form/html/js/",
   * "classpath:/static/js/", "file://src/main/webapp/static/js/",
   * "file://main/webapp/static/js/", "file://webapp/static/js/",
   * "file://static/js/", };
   * 
   * createResourceHandlers(registry, cssResources, cssLocations);
   * createResourceHandlers(registry, jsResources, jsLocations);
   * 
   * registry.addResourceHandler("/rest/css/**") .addResourceLocations(
   * "classpath:/form/html/css/" ) .setCacheControl(CacheControl.maxAge(2,
   * TimeUnit.HOURS).cachePublic()); registry.addResourceHandler("/rest/js/**")
   * .addResourceLocations( "classpath:/form/html/js/" )
   * .setCacheControl(CacheControl.maxAge(2, TimeUnit.HOURS).cachePublic()); }
   * 
   * private void createResourceHandlers(ResourceHandlerRegistry registry,
   * String[] resources, String[] locations) { for(String resource : resources)
   * { for(String location : locations) {
   * registry.addResourceHandler(resource).addResourceLocations(location); } } }
   */
}
