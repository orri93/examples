package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import gos.example.camel.processor.SimpleProcessor;
import gos.example.provider.MessageProvider;

@Component
public class SimpleRoute extends RouteBuilder {

  private static final Logger LOG = LoggerFactory.getLogger(SimpleRoute.class);

  private MessageProvider provider;
  private SimpleProcessor processor;

  public SimpleRoute() {
    this.provider = new MessageProvider();
    this.processor = new SimpleProcessor();
  }

  @Override
  public void configure() throws Exception {
    from(
        "scheduler://example?delay={{gos.example.interval}}")
        .autoStartup(true).bean(this.provider, "getMessage")
        .process(this.processor).
        to("file://{{gos.example.directory}}?fileName=output.txt&fileExist=Override&charset={{gos.example.charset}}")
        .to("log:example");
  }

}
