package gos.example.boot.web;

import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRegistration;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.EnableAutoConfiguration;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.boot.web.embedded.tomcat.TomcatServletWebServerFactory;
import org.springframework.boot.web.servlet.server.ConfigurableServletWebServerFactory;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.context.WebApplicationContext;
import org.springframework.web.context.request.async.WebAsyncUtils;
import org.springframework.web.context.support.AnnotationConfigWebApplicationContext;
import org.springframework.web.context.support.StaticWebApplicationContext;
import org.springframework.web.servlet.DispatcherServlet;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import gos.example.camel.route.BookOrderRoute;
import gos.example.camel.route.RestRoute;
import gos.example.camel.route.SayRouter;
import gos.example.component.OrderService;

@SpringBootApplication
@EnableAutoConfiguration
@ComponentScan(basePackages = {
    "gos.example.boot",
    "gos.example.camel.processor",
    "gos.example.repository",
    "gos.example.component",
    "gos.example.provider",
    "gos.example.item" } /*
                          * , basePackageClasses = {
                          * gos.example.configuration.SecurityConfiguration.
                          * class}
                          */)
@EnableJpaRepositories("gos.example.repository")
@EntityScan("gos.example.item")
public class SpringBootWeb extends SpringBootServletInitializer {

  public static void main(String[] args) {
    SpringApplication.run(SpringBootWeb.class, args);
  }

  // @Component
  // class MySpringBootRouter extends SayRouter {}

  @Component
  class RestApi extends RestRoute {
  }

  // @Component
  // class Backend extends BookOrderRoute {}

  @Component
  @Configuration
  @EnableWebMvc
  @ComponentScan
  class WebConfiguration extends WebConfigurer {
  }

//  @Component
//  @Configuration
//  @EnableWebMvc
//  @ComponentScan
  class ServletConfiguration implements WebMvcConfigurer {

  }

  class MiniServlet extends DispatcherServlet {
    private static final long serialVersionUID = 4792324942155327371L;
    
    Logger Log = LoggerFactory.getLogger(MiniServlet.class);

    public MiniServlet(WebApplicationContext webApplicationContext) {
      super(webApplicationContext);
    }

    @Override
    protected void doService(HttpServletRequest request,
        HttpServletResponse response) throws Exception {
      Log.info("Doing Service");
    }

  }

  @Override
  public void onStartup(ServletContext servletContext) throws ServletException {
    super.onStartup(servletContext);
    AnnotationConfigWebApplicationContext web =
        new AnnotationConfigWebApplicationContext();
    web.register(ServletConfiguration.class);
    
    servletContext.addListener(className);
    
    web.refresh();

    // Create and register the servlet
    MiniServlet servlet = new MiniServlet(web);
    ServletRegistration.Dynamic registration =
        servletContext.addServlet("app", servlet);
    registration.setLoadOnStartup(1);
    registration.addMapping("/mini/*");
  }

}
