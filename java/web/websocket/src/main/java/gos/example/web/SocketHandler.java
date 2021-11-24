package gos.example.web;

import java.io.IOException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

public class SocketHandler extends TextWebSocketHandler {
  private static final Logger LOGGER = LoggerFactory.getLogger(SocketHandler.class);

  @Override
  public void handleTextMessage(WebSocketSession session, TextMessage message) throws InterruptedException, IOException {
    LOGGER.info("Handling Text Message");
    String payload = message.getPayload();
    session.sendMessage(new TextMessage("Hello there! Your message payload is '" + payload + "'"));
  }

  @Override
  public void afterConnectionEstablished(WebSocketSession session) throws Exception {
    LOGGER.info("After Connections Established");
  }
}
