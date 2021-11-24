package gos.example.web;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;

@Configuration
@EnableWebSocket
public class WebSocketConfiguration implements WebSocketConfigurer {
  private static final Logger LOGGER = LoggerFactory.getLogger(WebSocketConfiguration.class);

  @Override
  public void registerWebSocketHandlers(WebSocketHandlerRegistry registry) {
    LOGGER.info("Register a WebSocket handler at path /name");
    registry.addHandler(new SocketHandler(), "/name");
  }
}
