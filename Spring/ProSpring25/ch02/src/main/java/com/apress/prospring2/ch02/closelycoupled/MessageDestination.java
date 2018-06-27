package com.apress.prospring2.ch02.closelycoupled;

import java.io.PrintStream;

public class MessageDestination {
  public void write(PrintStream out, String message)
  {
    out.println(message);
  }
}
