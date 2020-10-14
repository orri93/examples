package main

//
// Calling C code from go
//
// Go provides a pseudo package called C to interface with C libraries.
// Its not very straightforward how to do this though.
// In this tutorial, we will go over creating a simple C function,
// and calling it from go. After that, we will move on to a slightly
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
	namea := C.CString("Gopher")
	defer C.free(unsafe.Pointer(namea))

	sizea := C.size_t(1024)
	yeara := C.int(2018)

	ptra := C.malloc(C.sizeof_char * 1024)
	defer C.free(unsafe.Pointer(ptra))

	resulta := C.gos_for_go_greet((*C.char)(ptra), sizea, namea, yeara)

	sa := C.GoBytes(ptra, resulta)
	fmt.Println(string(sa))

	nameb := C.CString("Orri")
	defer C.free(unsafe.Pointer(nameb))

	sizeb := C.size_t(512)
	yearb := C.int(1971)

	ptrb := C.malloc(C.sizeof_char * 512)
	defer C.free(unsafe.Pointer(ptrb))

	g := C.struct_GosForGoGreetee{
		buffer: (*C.char)(ptrb),
		size:   sizeb,
		name:   nameb,
		year:   yearb,
	}

	resultb := C.gos_for_go_greet_st(&g)

	sb := C.GoBytes(ptrb, resultb)
	fmt.Println(string(sb))
}
