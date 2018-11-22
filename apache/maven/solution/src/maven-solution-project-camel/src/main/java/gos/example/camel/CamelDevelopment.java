package gos.example.camel;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@SpringBootApplication
@Configuration
@ComponentScan("gos.example.camel")
public class CamelDevelopment {
  public static void main( String[] args ) {
    SpringApplication.run(CamelDevelopment.class, args);
  }
}
