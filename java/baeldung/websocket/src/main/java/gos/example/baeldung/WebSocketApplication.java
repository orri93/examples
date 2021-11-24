package gos.example.baeldung;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.servlet.support.SpringBootServletInitializer;
import org.springframework.scheduling.annotation.EnableScheduling;

@SpringBootApplication
@EnableScheduling
public class WebSocketApplication extends SpringBootServletInitializer {
  public static void main(String[] args) {
    System.out.println("Starting Baeldung Web Socket Example");
    SpringApplication.run(WebSocketApplication.class, args);
  }
}
