package com.apress.prospring2.ch02.closelycoupled;

public class CloselyCoupledHelloWorld {
  public static void main(String[] args) {
    MessageSource source = new MessageSource("hello, world");
    MessageDestination destination = new MessageDestination();
    destination.write(System.out, source.getMessage());
  }
}
