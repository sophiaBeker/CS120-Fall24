
#include <iostream>
#include <string>
#include <vector>

#include "judge_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argv + argc};

  if (command_line.size() < 4) {
    std::cout << "error: you must give at least three scores\n";
    return 1;
  }

  std::vector<double> scores;

  for (int element{1}; element < command_line.size(); element++) {
    scores.push_back(std::stod(command_line.at(element)));
  }

  std::cout << "average is " << JudgeAverage(scores) << "\n";

  return 0;
}
