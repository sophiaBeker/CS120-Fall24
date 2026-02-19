
#include "animated_gradient_functions.h"

#include <cmath>
#include <iostream>

bool HasMatchingFileExtension(const std::string& file_name,
                              const std::string& extension) {
  return file_name.size() > extension.size() &&
         file_name.compare(file_name.size() - extension.size(),
                           extension.size(), extension) == 0;
}

std::vector<double> BuildSineLookupTable(int image_width) {
  std::vector<double> lookup_table;
  lookup_table.reserve(image_width);
  double radian_step{M_PI / image_width};
  for (int column = 0; column < image_width; column++) {
    lookup_table.push_back(sin(radian_step * column));
  }
  return lookup_table;
}
