package main

import (
	"fmt"
	"time"
)

var start time.Time

func main() {
	p := fmt.Println

	now := time.Now()
	start = now

	p(now)

	then := time.Date(
		2009, 11, 17, 20, 34, 58, 651387237, time.UTC)
	p(then)

}
