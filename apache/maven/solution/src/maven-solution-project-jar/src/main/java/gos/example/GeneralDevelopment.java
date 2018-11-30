package gos.example;

import gos.example.item.Message;
import gos.example.provider.MessageProvider;

public class GeneralDevelopment {
  public static void main( String[] args ) {
    MessageProvider provider = new MessageProvider();
    Message message = provider.getMessage();
    System.out.println(message.getText());
  }
}
