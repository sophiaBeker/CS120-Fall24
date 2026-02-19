
#include <fstream>
#include <iostream>
#include <sstream>

#include "states_functions.h"


double PopulationDensity(std::vector<std::string> state) {
  // TODO: Calculate the population density of a state by dividing
  // the state's population by it's area. Return the quotient as
  // a double.
  return 0.0;
}

std::string Name(std::vector<std::string> state) {
  std::string name;
  // TODO: Given the vector state, extract the name of the state from the
  // vector and return it.
  return name;
}

int Population(std::vector<std::string> state) {
  int population{-1};
  // TODO: Given the vector state, extract the population of the state from
  // the vector. Be aware that the population is stored as a std::string and
  // must be converted to an integer using the std::stoi() function.
  return population;
}

double LandArea(std::vector<std::string> state) {
  double land_area{0.0};
  // TODO: Given the vector state, extract the land area of the state from
  // the vector. Be aware that the land area is stored as a std::string and
  // must be converted to an double using the std::stod() function.
  return land_area;
}

/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

std::vector<std::string> CSVGetLine(std::ifstream& input_file_stream) {
  // Do not change this function.
  std::vector<std::string> tokens;
  std::string line;
  std::getline(input_file_stream, line);
  std::stringstream line_stream{line};
  std::string token;
  while (std::getline(line_stream, token, ',')) {
    if (token.size() > 1) {
      tokens.push_back(token);
    }
  }
  return tokens;
}

std::vector<std::vector<std::string>> ReadCSV(const std::string& csv_filename) {
  // Do not change this function.
  std::vector<std::vector<std::string>> table;
  std::ifstream file{csv_filename};
  if (!file.is_open()) {
    std::cout << "The file " << csv_filename << " could not be opened.\n";
    return table;
  }
  std::string cell_buffer;
  while (!file.eof() && file.good()) {
    std::vector<std::string> row{CSVGetLine(file)};
    if (row.size() >= 3) {
      table.push_back(row);
    }
  }
  return table;
}
