#ifndef GOS_EX_C_FOR_GO_H_
#define GOS_EX_C_FOR_GO_H_

#include <stdlib.h>

/*
 * Calling C code from go
 *
 * Go provides a pseudo package called “C” to interface with C libraries.
 * Its not very straightforward how to do this though.
 * In this tutorial, we’ll go over creating a simple C function,
 * and calling it from go. After that, we’ll move on to a slightly
 * more complex example involving C structs.
 * 
 * See https://karthikkaranth.me/blog/calling-c-code-from-go
 * 
 */

struct GosForGoGreetee {
  char* buffer;
  size_t size;
  const char* name;
  int year;
};


#ifdef __cplusplus
extern "C" {
#endif

int gos_for_go_greet(char* buffer, size_t size, const char* name, int year);

int gos_for_go_greet_st(struct GosForGoGreetee* greetee);

#ifdef __cplusplus
}
#endif

#endif
