package gos.example.baeldung;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan(basePackages="gos.example.baeldung")
public class CamelApplication {
  public static void main(String[] args) {
    SpringApplication.run(CamelApplication.class, args);
  }

}
