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

#include <stdlib.h>
#include <stdio.h>

#include <gos/forgo.h>

int gos_for_go_greet(char* buffer, size_t size, const char* name, int year) {
  int result;
  result = snprintf(
    buffer,
    size,
    "Greetings, %s from %d! We come in peace :)",
    name,
    year);
  return result;
}

int gos_for_go_greet_st(struct GosForGoGreetee* greetee) {
  int result;
  result = snprintf(
    greetee->buffer,
    greetee->size,
    "Greetings, %s from %d! We come in peace with structures :)",
    greetee->name,
    greetee->year);
}
