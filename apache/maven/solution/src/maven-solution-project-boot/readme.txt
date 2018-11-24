Build
You can build this example using:

$ mvn package
Run
You can run this example with Maven using:

$ mvn spring-boot:run -Dspring.profiles.active=dev
Alternatively, you can also run this example using the executable JAR:

$ java -jar -Dspring.profiles.active=dev target/camel-example-spring-boot-rest-jpa-${project.version}.jar

You can then access the REST API directly from your Web browser, e.g.:

http://localhost:8080/camel-rest-jpa/books
http://localhost:8080/camel-rest-jpa/books/order/1
The Camel application can be stopped pressing ctrl+c in the shell.

Swagger API
The example provides API documentation of the service using Swagger using the context-path camel-rest-jpa/api-doc. You can access the API documentation from your Web browser at http://localhost:8080/camel-rest-jpa/api-doc.

Forum, Help, etc