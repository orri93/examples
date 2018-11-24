package gos.example.camel.route;

import org.apache.camel.builder.RouteBuilder;

public class BookOrderRoute extends RouteBuilder {
	@Override
	public void configure() {
		from("timer://runOnce?repeatCount=1&delay=1s")
		    .bean("orderService", "generateBook(1)")
		    .to("jpa:gos.example.item.Book")
		    .log("Inserted new book ${body.id}")
		    .bean("orderService", "generateBook(2)")
		    .to("jpa:gos.example.item.Book")
		    .log("Inserted new book ${body.id}");

		// A first route generates some orders and queue them in DB
		from("timer:new-order?delay=10s&period={{example.generateOrderPeriod:2s}}")
		    .routeId("generate-order").bean("orderService", "generateOrder")
		    .to("jpa:jpa:gos.example.item.Order")
		    .log("Inserted new order ${body.id}");

		// A second route polls the DB for new orders and processes them
		from("jpa:gos.example.item.Order"
		    + "?consumer.namedQuery=new-orders"
		    + "&consumer.delay={{example.processOrderPeriod:5s}}"
		    + "&consumeDelete=false").routeId("process-order").log(
		        "Processed order #id ${body.id} with ${body.amount} copies of the '${body.book.description}' book");
	}

}
