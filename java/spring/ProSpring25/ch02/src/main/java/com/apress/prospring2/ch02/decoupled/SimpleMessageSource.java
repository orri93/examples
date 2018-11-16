package com.apress.prospring2.ch02.decoupled;

public class SimpleMessageSource implements MessageSource {
  private final String message;
  
  public SimpleMessageSource(String message) {
    this.message = message;
  }
  
  @Override
  public String getMessage() {
    return this.message;
  }
}
