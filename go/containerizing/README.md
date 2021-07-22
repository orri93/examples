# Containerizing Go Applications

See [Containerizing your Go Applications with Docker - Tutorial](https://tutorialedge.net/golang/go-docker-tutorial/)

## Testing

execute

```go run main.go```

then browse to [http://localhost:8081](http://localhost:8081)

## Building

execute

```docker build -t containerizing-go .```

## Run

execute

```docker run -p 8080:8081 -it containerizing-go```
