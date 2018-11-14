#include "MathFunctions.h"

double mysqrt(double x)
{
// if we have both log and exp then use them
#if defined (HAVE_LOG) && defined (HAVE_EXP)
  return exp(log(x)*0.5);
#else // otherwise use an iterative approach
  return sqrt(x);
#endif
}