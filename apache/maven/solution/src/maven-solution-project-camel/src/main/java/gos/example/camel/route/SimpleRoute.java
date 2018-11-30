package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import gos.example.camel.processor.SimpleProcessor;
import gos.example.provider.MessageProvider;

@Component
public class SimpleRoute extends RouteBuilder {

  private static final Logger Log = LoggerFactory.getLogger(SimpleRoute.class);

  private MessageProvider provider;
  private SimpleProcessor processor;

  public SimpleRoute() {
    this.provider = new MessageProvider();
    this.processor = new SimpleProcessor();
  }

  @Override
  public void configure() throws Exception {
  	StringBuilder builder = new StringBuilder("file://");
  	builder.append("{{gos.example.directory:src/main/resources/static/}}?");
  	builder.append("fileName=output.txt&fileExist=Override&");
  	builder.append("charset={{gos.example.charset:utf-8}}");
    from("scheduler://example?delay={{gos.example.interval:60s}}")
        .autoStartup(true).bean(this.provider, "getMessage")
        .process(this.processor)
        .to(builder.toString())
        .to("log:example");
  }

}
