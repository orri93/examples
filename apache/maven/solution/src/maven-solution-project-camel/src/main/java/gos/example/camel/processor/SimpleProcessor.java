package gos.example.camel.processor;

import org.apache.camel.Exchange;
import org.apache.camel.Message;
import org.apache.camel.Processor;

public class SimpleProcessor implements Processor {

  @Override
  public void process(Exchange exchange) throws Exception {
    Message in = exchange.getIn();
    Message out = exchange.getOut();
    gos.example.item.Message message =
    		in.getBody(gos.example.item.Message.class);
    if(message != null) {
      String body = message.getText();
      if(body != null) {
        out.setBody(body);
      }
    }
    out.setHeaders(in.getHeaders());
  }
}
