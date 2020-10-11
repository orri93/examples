/*
 * Everything you need to know about Packages in Go
 * https://medium.com/rungo/everything-you-need-to-know-about-packages-in-go-b8bac62b74cc
 *
 * go run entry.go
 *
 */

package main

import (
	"fmt"

	"./greet"
	"./greet/de"
)

func main() {
	fmt.Println(greet.Morning)
	fmt.Println(de.Morning)
}
