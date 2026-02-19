
#include <iostream>
#include <string>
#include <vector>

#include "parking_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argv + argc};

  if (command_line.size() != 5) {
    std::cout << "error: you must supply four arguments";
    return 1;
  }

  std::string street = command_line.at(1);
  std::string day = command_line.at(2);
  int hour = std::stoi(command_line.at(3));
  int minute = std::stoi(command_line.at(4));

  if ((street != "ash") && (street != "beech") && (street != "cedar") &&
      (street != "date")) {
    std::cout << "error: invalid street\n";
    return 1;
  }

  if ((day != "mon") && (day != "tue") && (day != "wed") && (day != "thu") &&
      (day != "fri") && (day != "sat") && (day != "sun")) {
    std::cout << "error: invalid day\n";
    return 1;
  }

  if (!(hour <= 23 && hour >= 0)) {
    std::cout << "error: invalid hour\n";
    return 1;
  }

  if (!(minute <= 59 && minute >= 0)) {
    std::cout << "error: invalid minute\n";
    return 1;
  }

  bool allowed_parking = true;
  if (street == "ash") {
    if (!CanParkOnAsh(day, hour)) {
      allowed_parking = false;
    }
  } else if (street == "beech") {
    if (!CanParkOnBeech(day, hour)) {
      allowed_parking = false;
    }
  } else if (street == "cedar") {
    if (!CanParkOnCedar(day, hour)) {
      allowed_parking = false;
    }
  } else if (street == "date") {
    if (!CanParkOnDate(day, hour, minute)) {
      allowed_parking = false;
    }
  }

  if (allowed_parking) {
    std::cout << "allowed\n";
  } else {
    std::cout << "not allowed\n";
  }

  return 0;
}
