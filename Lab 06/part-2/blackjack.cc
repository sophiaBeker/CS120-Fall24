
#include <iostream>
#include <string>
#include <vector>

#include "blackjack_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argv + argc};

  if (command_line.size() != 3) {
    std::cout << "error: you must supply two arguments";
    return 1;
  }

  std::string first_card = command_line.at(1);

  std::string second_card = command_line.at(2);

  if ((!IsCardName(first_card)) || (!IsCardName(second_card))) {
    std::cout << "error: unknown card";
    return 1;
  }

  int total_score = TwoCardHandScore(first_card, second_card);

  std::cout << total_score;
  return 0;
}
