package gos.example.web;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.messaging.simp.SimpMessagingTemplate;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;

@Service
public class ScheduledPushMessages {
  private static final Logger LOGGER = LoggerFactory.getLogger(ScheduledPushMessages.class);

  private final SimpMessagingTemplate simpMessagingTemplate;

  public ScheduledPushMessages(SimpMessagingTemplate simpMessagingTemplate) {
    this.simpMessagingTemplate = simpMessagingTemplate;
  }

  @Scheduled(fixedRate = 5000)
  public void sendMessage() {
    LOGGER.info("Send Message Scheduled");
  }
}
