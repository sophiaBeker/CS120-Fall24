
#include "states_functions.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> ReadCSV(const std::string& csv_filename) {
  std::vector<std::vector<std::string>> table;
  std::ifstream file(csv_filename);

  // read each row
  std::string line;
  while (std::getline(file, line)) {
    // read each column in this row
    std::vector<std::string> row;

    std::stringstream line_stream{line};
    while (line_stream) {
      std::string cell;
      line_stream.ignore(1);  // leading quote
      if (!std::getline(line_stream, cell, '"')) {
        break;
      }
      if (line_stream.peek() == ',') {
        line_stream.ignore(1);  // comma delimiter
      }
      row.push_back(cell);
    }

    table.push_back(row);
  }

  return table;
}

State::State(const std::string& name, int population, double land_area)
    : name_(name), population_(population), land_area_(land_area) {}

State::State() : population_(0), land_area_(0.0) {}

const std::string& State::Name() const { return name_; }

int State::Population() const { return population_; }

double State::LandArea() const { return land_area_; }

double State::PopulationDensity() const { return Population() / LandArea(); }

std::vector<State> ReadStates(const std::string& csv_filename) {
  std::vector<State> states;
  std::vector<std::vector<std::string>> rows = ReadCSV(csv_filename);
  int index = 0;
  for (const std::vector<std::string>& csv : rows) {
    if (index == 0) {
      index++;
      continue;
    }
    std::string name = csv.at(0);
    int population = std::stoi(csv.at(2));
    double land_area = std::stod(csv.at(47));
    State state(name, population, land_area);
    states.push_back(state);
  }
  return states;
}