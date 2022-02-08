#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
  double r, x, y, x0, y0;
  if (argc >= 2) {
    x0 = atof(argv[0]);
    y0 = atof(argv[1]);
    r = atof(argv[2]);
  } else {
    fprintf(stderr, "usage: circle x y r");
    return EXIT_FAILURE;
  }
  for (y = y0 - r; y <= y0 + r; y = y + 0.1) {
    x = sqrt(r*r - (y-y0) * (y-y0)) + x0; 
    printf("%lf\t%lf\n", x, y);
  }
  for (y = y0 + r; y >= y0 - r; y = y - 0.1) {
    x = -sqrt(r*r - (y-y0)*(y-y0))+x0; 
    printf("%lf\t%lf\n", x, y);
  }
  return EXIT_SUCCESS;
}
