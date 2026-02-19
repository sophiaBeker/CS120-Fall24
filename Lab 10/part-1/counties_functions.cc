
#include "counties_functions.h"

#include <string>
#include <vector>

std::string AllCountiesString(
    const std::vector<std::vector<std::string>>& counties) {
  std::string all_counties_string;
  for (const auto& entry : counties) {
    all_counties_string += entry.at(0) + " ";
  }
  return all_counties_string;
}

int CountyPopulation(const std::vector<std::vector<std::string>>& counties,
                     const std::string& match_county) {
  int population{-1};
  for (const auto& entry : counties) {
    if (entry.at(0) == match_county) {
      population = std::stoi(entry.at(1));
      break;
    }
  }
  return population;
}

int StatePopulation(const std::vector<std::vector<std::string>>& counties) {
  int population{0};
  for (const auto& entry : counties) {
    population += std::stoi(entry.at(1));
  }
  return population;
}