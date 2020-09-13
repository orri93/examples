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
  return gos_for_go_greet(
    greetee->buffer,
    greetee->size,
    greetee->name,
    greetee->year);
}
