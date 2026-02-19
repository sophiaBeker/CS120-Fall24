
#include <iostream>

#include "units_functions.h"

int main(int argc, char const *argv[]) {
  double volume{0};
  std::cout << "Enter ml: ";
  std::cin >> volume;

  double tsp{MlToTsp(volume)};
  double tbsp{MlToTbsp(volume)};
  double ounces{MlToOz(volume)};
  double cup{MlToCup(volume)};

  std::cout << volume << " ml = " << tsp << " tsp = " << tbsp
            << " tbsp = " << ounces << " oz = " << cup << " cups\n";
  return 0;
}