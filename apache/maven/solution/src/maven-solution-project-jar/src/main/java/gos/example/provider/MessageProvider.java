package gos.example.provider;

import gos.example.item.Message;

public class MessageProvider {
  private int count = 0;
  
  public Message getMessage() {
    Message message = new Message();
    message.setText(String.format("Hello no. %d", count++));
    return message;
  }
}
