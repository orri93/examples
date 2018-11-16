package com.apress.prospring2.ch02.decoupled;

public class StdoutMessageDestination implements MessageDestination {
  @Override
  public void write(String message) {
    System.out.println(message);
  }
}
