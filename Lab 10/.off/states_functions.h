
/* You do not need to make any changes to this file. */

#ifndef STATES_H
#define STATES_H

#include <string>
#include <vector>

std::vector<std::vector<std::string>> ReadCSV(const std::string& csv_filename);

double PopulationDensity(std::vector<std::string> state);

std::string Name(std::vector<std::string> state);

int Population(std::vector<std::string> state);

double LandArea(std::vector<std::string> state);

#endif  // STATES_H_
