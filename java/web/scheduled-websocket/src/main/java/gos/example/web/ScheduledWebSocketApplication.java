package gos.example.web;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.scheduling.annotation.EnableScheduling;

@EnableScheduling
@SpringBootApplication
public class ScheduledWebSocketApplication {
  private static final Logger LOGGER = LoggerFactory.getLogger(ScheduledWebSocketApplication.class);

  public static void main(String[] args) {
    LOGGER.info("Starting Scheduled Web Socket Example");
    SpringApplication.run(ScheduledWebSocketApplication.class, args);
  }
}
