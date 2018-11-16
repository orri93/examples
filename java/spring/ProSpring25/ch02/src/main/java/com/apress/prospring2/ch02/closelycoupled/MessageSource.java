package com.apress.prospring2.ch02.closelycoupled;

public class MessageSource {
  private final String message;
  
  public MessageSource(String message) {
    this.message = message;
  }
  
  public String getMessage() {
    return this.message;
  }
}
