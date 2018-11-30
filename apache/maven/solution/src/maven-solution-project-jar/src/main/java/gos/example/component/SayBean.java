package gos.example.component;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component("sayBean")
public class SayBean {
  @Value("${greeting}")
  private String say;

  public String saySomething() {
      return say;
  }
}
