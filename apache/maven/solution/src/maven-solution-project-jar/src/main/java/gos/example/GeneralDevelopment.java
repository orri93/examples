package gos.example;

public class GeneralDevelopment {
  public static void main( String[] args ) {
    Provider provider = new Provider();
    Message message = provider.getMessage();
    System.out.println(message.getText());
  }
}
