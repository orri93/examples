package gos.example.web;

import java.io.IOException;
import java.util.Map.Entry;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.locks.ReentrantLock;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.scheduling.annotation.Scheduled;
import org.springframework.stereotype.Service;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

@Service
public class SocketHandler extends TextWebSocketHandler {
  private static final Logger LOGGER = LoggerFactory.getLogger(SocketHandler.class);

  private static Map<String, WebSocketSession> SessionMap = new HashMap<>();
  private static ReentrantLock Lock = new ReentrantLock();

  @Override
  public void afterConnectionEstablished(WebSocketSession session) throws Exception {
    String id = session.getId();
    Lock.lock();
    try {
      if (!SessionMap.containsKey(id)) {
        LOGGER.info("After Connections Established. Adding Session ID: {}", id);
        SessionMap.put(id, session);
      } else {
        LOGGER.warn("After Connections Established. Already have Session ID: {}", id);
      }
    } finally {
      Lock.unlock();
    }
  }

  @Override
  public void handleTextMessage(WebSocketSession session, TextMessage message) throws InterruptedException, IOException {
    LOGGER.info("Handling Text Message");
    String payload = message.getPayload();
    JSONParser parser = new JSONParser();
    try {
      JSONObject jsonObject = (JSONObject) parser.parse(payload);
      String name = (String) jsonObject.get("name");
      session.sendMessage(new TextMessage("Hello " + name + "! Your message payload is '" + payload + "'"));
    } catch(ParseException ex) {
      LOGGER.error("Failed to parse JSON payload", ex);
    }
  }

  @Override
  public void afterConnectionClosed(WebSocketSession session, CloseStatus status) throws Exception {
    String id = session.getId();
    Lock.lock();
    try {
      if (SessionMap.containsKey(id)) {
        LOGGER.info("After Connections Closed. Removing Session ID: " + id);
        SessionMap.remove(id);
      } else {
        LOGGER.info("After Connections Closed. No Session ID: " + id);
      }
    } finally {
      Lock.unlock();
    }
  }

  @Scheduled(fixedRate = 1000)
  public void scheduledTask() {
    Lock.lock();
    try {
      LOGGER.info("Scheduled Task - Connection count is {}", SessionMap.size());
      for (Entry<String, WebSocketSession> entry : SessionMap.entrySet()) {
        String id = entry.getKey();
        WebSocketSession session = entry.getValue();
        LOGGER.info("  Sending message to Session ID: " + id);
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("type", "scheduled");
        jsonObject.put("id", id);
        session.sendMessage(new TextMessage(jsonObject.toJSONString()));
      }
    } catch (IOException ex) {
      LOGGER.warn("Failed to send message");
    } finally {
      Lock.unlock();
    }
  }
}
