
#ifndef MAKE_MESSAGE_FUNCTIONS_H
#define MAKE_MESSAGE_FUNCTIONS_H

#include <random>
#include <string>

// Fonts in Ubuntu 24 have gone through a change. They have transitioned from
// gsfonts to fonts-urw-base35 and in the process changed the location of the
// fonts and changed the name of the fonts. The Ubuntu GraphicsMagick package
// (graphicsmagick) hard codes the path to the old
// location (/usr/share/fonts/type1/gsfonts) rather than the new location
// (/usr/share/fonts/type1/urw-base35) and uses the old name (n019003l.pfb)
// rather than the new name (NimbusSans-Regular.t1).
extern const std::string kMessageFont;

// Check to see if file_name ends with the string extension, returns true if
// file_name ends with extension, false otherwise.
bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension);

// Flips a coin and returns true some of the time and false the rest of the
// time.
bool CoinFlip();

// Generate a randome number between 0 and 1
// returns A random number between 0 and 1
double RandomDouble01();

// The RandomNumberGenerator class is a wrapper around the Standard C++
// Library's Mersenne Twister pseudo random number generator.
// This class is complete and correct; please do not make any changes to it.
//
// In lieu of directly working with the Mersenne Twister class
// https://en.cppreference.com/w/cpp/numeric/random/mersenne_twister_engine,
// this class serves as a lightweight wrapper around the necessary elements of
// the library. The usage of this class is very simple and requires a
// minimum and maximum value for initialization.
class RandomNumberGenerator {
 private:
  // A Mersenne Twister engine
  std::mt19937 mt_engine_;
  // A uniform distribution; select numbers randomly in a uniform manner
  std::uniform_real_distribution<double> uniform_dist_;

 public:
  // Constructor to the RandomNumberGenerator class
  //
  // The RandomNumberGenerator generates random integer numbers between
  // minimum and maximum. The constructor initializes and prepares
  // the engine. To generate a number use the <RandomNumberGenerator::Next>()
  // method.
  //
  // minimum The lowest double value the random number generator will return
  // maximum The largest double value the random number generator will return
  RandomNumberGenerator(double minimum, double maximum, std::seed_seq& seed) {
    // A Mersenne Twister engine
    mt_engine_ = std::mt19937{seed};
    // A uniform distribution; select numbers randomly in a uniform manner
    uniform_dist_ = std::uniform_real_distribution<double>{minimum, maximum};
  }

  // Return a random number
  //
  // Returns a random integer number between the minimum and maximum set
  // when the constructor was called.
  //
  // returns An integer between the minimum and maximum set when
  // the constructor was called
  double Next() {
    double random_number = uniform_dist_(mt_engine_);
    // std::cout << "Debugging: The random number is " << random_number << "\n";
    return random_number;
  }
};

#endif