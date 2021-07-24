FROM maven
LABEL maintainer="orri93@gmail.com"

WORKDIR /opt/src/opcua
COPY .. .
WORKDIR /opt/src/opcua/simple-client-browse
RUN mvn package

#CMD ["java"]