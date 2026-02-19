
#include "rng.h"

// See the header file for documentation

// Secret global variable that is used by RandomDouble_01()
// NOLINTNEXTLINE
static RandomNumberGenerator rng_01{0, 1};

// Secret global variable that is used by RandomDouble_11()
// NOLINTNEXTLINE
static RandomNumberGenerator rng_11{-1, 1};

double RandomDouble(double min, double max) {
  RandomNumberGenerator rng(min, max);
  return rng.Next();
}

double RandomDouble01() { return rng_01.Next(); }

double RandomDouble11() { return rng_11.Next(); }
