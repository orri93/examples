FROM golang
LABEL maintainer="orri93@gmail.com"

WORKDIR /go/src/simple-client-browse
COPY . .
RUN go mod download
#RUN go install github.com/gopcua/opcua@latest
#RUN go get github.com/gopcua/opcua
RUN go build -o main .

#EXPOSE 8081
CMD ["/go/src/simple-client-browse/main"]
