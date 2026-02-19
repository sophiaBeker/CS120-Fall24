
#include "make_message_functions.h"

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  return file_name.size() > extension.size() &&
         file_name.compare(file_name.size() - extension.size(),
                           extension.size(), extension) == 0;
}

// Secret global variable to make the random number generator
// predictable
std::seed_seq rng_seed{1, 2, 3, 4, 5};

// Secret global variable that is used by RandomDouble_01()
RandomNumberGenerator rng_01{0, 1, rng_seed};

// Secret global variable that is used by CoinFlip()
RandomNumberGenerator rng_coin_flip{-1, 1, rng_seed};

// Returns a random double between 0 and 1
double RandomDouble01() { return rng_01.Next(); }

/// Return a True or False depending on a random value.
/// Generates a random number and then decides to return True or False
bool CoinFlip() {
  if (rng_coin_flip.Next() > 0.0) {
    return true;
  }
  return false;
}

// Do not edit below this line!
// Do not change the value of kMessageFont.
#ifdef OSX
// macOS with MacPorts
const std::string kMessageFont{
    "/opt/local/share/fonts/Type1/gsfonts/n019003l.pfb"};
#else
// Ubuntu 24 and later
const std::string kMessageFont{
    "/usr/share/fonts/type1/urw-base35/NimbusSans-Regular.t1"};
#endif