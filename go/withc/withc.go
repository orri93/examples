package main

// #cgo CFLAGS: -I../../include
// #cgo LDFLAGS: -L../../artifacts/RelWithDebInfo/lib -llibgosforgo
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
}
