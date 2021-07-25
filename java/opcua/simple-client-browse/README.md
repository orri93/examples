# OPC UA Browse Java Examples

## Building

execute

```mvn package```

or

```mvn install```

### Building with docker

execute

```docker build -t gos-example-java-simple-client-browse .```

## Testing

execute

```java -jar simple-client-browse-0.0.1-jar-with-dependencies.jar opc.tcp://192.168.1.93:4840/```

or

```java -jar simple-client-browse-0.0.1-jar-with-dependencies.jar opc.tcp://192.168.1.93:4840/ i=84```

or

```mvn exec:java -Dexec.args="opc.tcp://192.168.1.93:4840/"```
