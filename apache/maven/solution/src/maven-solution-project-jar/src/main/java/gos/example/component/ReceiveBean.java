package gos.example.component;

import org.springframework.stereotype.Component;

@Component
public class ReceiveBean {
	public void receiveMethod(String body) {
    System.out.println("Received: " + body);
	}
}
