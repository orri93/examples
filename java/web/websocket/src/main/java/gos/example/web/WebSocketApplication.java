package gos.example.web;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class WebSocketApplication {
  private static final Logger LOGGER = LoggerFactory.getLogger(WebSocketApplication.class);

  public static void main(String[] args) {
    LOGGER.info("Starting Web Socket Example");
    SpringApplication.run(WebSocketApplication.class, args);
  }
}
