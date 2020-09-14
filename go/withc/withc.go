package main

//
// Calling C code from go
//
// Go provides a pseudo package called “C” to interface with C libraries.
// Its not very straightforward how to do this though.
// In this tutorial, we’ll go over creating a simple C function,
// and calling it from go. After that, we’ll move on to a slightly
// more complex example involving C structs.
//
// See https://karthikkaranth.me/blog/calling-c-code-from-go
//

// #cgo CFLAGS: -I../../include
// #cgo LDFLAGS: -L../../lib -lgosforgo -Wl,-rpath=../../lib
// #include <stdlib.h>
// #include <gos/forgo.h>
import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	name := C.CString("Gopher")
	defer C.free(unsafe.Pointer(name))

	size := C.size_t(1024)
	year := C.int(2018)

	ptr := C.malloc(C.sizeof_char * 1024)
	defer C.free(unsafe.Pointer(ptr))

	result := C.gos_for_go_greet((*C.char)(ptr), size, name, year)

  b := C.GoBytes(ptr, result)
	fmt.Println(string(b))

	g := C.struct_GosForGoGreetee {
		buffer: ptr,
		size: size,
		name: name,
		year: year
	}

	result := C.gos_for_go_greet_st(&g)

	b := C.GoBytes(ptr, result)
	fmt.Println(string(b))
}
