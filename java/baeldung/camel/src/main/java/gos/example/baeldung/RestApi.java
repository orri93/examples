package gos.example.baeldung;

import org.apache.camel.CamelContext;
import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.impl.DefaultCamelContext;
import org.springframework.stereotype.Component;

@Component
class RestApi extends RouteBuilder {
  @Override
  public void configure() {
    CamelContext context = new DefaultCamelContext();

    restConfiguration()
      .contextPath(contextPath) 
      .port(serverPort)
      .enableCORS(true)
      .apiContextPath("/api-doc")
      .apiProperty("api.title", "Test REST API")
      .apiProperty("api.version", "v1")
      .apiContextRouteId("doc-api")
      .component("servlet")
      .bindingMode(RestBindingMode.json);

    rest("/api/")
      .id("api-route")
      .consumes("application/json")
      .post("/bean")
      .bindingMode(RestBindingMode.json_xml)
      .type(MyBean.class)
      .to("direct:remoteService");

    from("direct:remoteService")
      .routeId("direct-route")
      .tracing()
      .log(">>> ${body.id}")
      .log(">>> ${body.name}")
      .transform().simple("Hello ${in.body.name}")
      .setHeader(Exchange.HTTP_RESPONSE_CODE, constant(200));
  }
}
