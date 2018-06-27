package com.apress.prospring2.ch02.decoupled;

public class DecoupledHelloWorld {
  public static void main(String[] args) {
    MessageSource source = new SimpleMessageSource("Hello, world");
    MessageDestination destination = new StdoutMessageDestination();
    destination.write(source.getMessage());
  }
}
