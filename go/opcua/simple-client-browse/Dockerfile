FROM golang
LABEL maintainer="orri93@gmail.com"

WORKDIR /go/src/simple-client-browse
COPY . .
RUN go mod download
RUN go build -o main .

CMD ["/go/src/simple-client-browse/main"]
