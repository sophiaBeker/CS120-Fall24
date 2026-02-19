
#include "dffi_functions.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

double PromptForDouble(const std::string& query) {
  std::cout << query;
  double user_input = 0.0;
  std::cin >> user_input;
  return user_input;
}

int TruncateDouble(double decimal_number) {
  double integer_part = trunc(decimal_number);
  int converted_integer_part = 0;
  if (integer_part >= std::numeric_limits<int>::max()) {
    converted_integer_part = std::numeric_limits<int>::max();
  } else if (integer_part <= std::numeric_limits<int>::min()) {
    converted_integer_part = std::numeric_limits<int>::min();
  } else {
    converted_integer_part = static_cast<int>(integer_part);
  }
  return converted_integer_part;
}
