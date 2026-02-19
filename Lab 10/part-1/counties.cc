
/* You do not need to make any changes to this file. */

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "counties_functions.h"

int main(int argc, char const *argv[]) {
  std::vector<std::vector<std::string>> ca_counties{
      {"Alameda", "1648556"},      {"Alpine", "1235"},
      {"Amador", "41259"},         {"Butte", "208309"},
      {"Calaveras", "46221"},      {"Colusa", "21917"},
      {"Contra Costa", "1161413"}, {"Del Norte", "28100"},
      {"El Dorado", "193221"},     {"Fresno", "1013581"},
      {"Glenn", "28805"},          {"Humboldt", "136310"},
      {"Imperial", "179851"},      {"Inyo", "18970"},
      {"Kern", "917673"},          {"Kings", "153443"},
      {"Lake", "68766"},           {"Lassen", "33159"},
      {"Los Angeles", "9829544"},  {"Madera", "159410"},
      {"Marin", "260206"},         {"Mariposa", "17147"},
      {"Mendocino", "91305"},      {"Merced", "286461"},
      {"Modoc", "8661"},           {"Mono", "13247"},
      {"Monterey", "437325"},      {"Napa", "136207"},
      {"Nevada", "103487"},        {"Orange", "3167809"},
      {"Placer", "412300"},        {"Plumas", "19915"},
      {"Riverside", "2458395"},    {"Sacramento", "1588921"},
      {"San Benito", "66677"},     {"San Bernardino", "2194710"},
      {"San Diego", "3286069"},    {"San Francisco", "815201"},
      {"San Joaquin", "789410"},   {"San Luis Obispo", "283159"},
      {"San Mateo", "737888"},     {"Santa Barbara", "446475"},
      {"Santa Clara", "1885508"},  {"Santa Cruz", "267792"},
      {"Shasta", "182139"},        {"Sierra", "3283"},
      {"Siskiyou", "44118"},       {"Solano", "451716"},
      {"Sonoma", "485887"},        {"Stanislaus", "552999"},
      {"Sutter", "99063"},         {"Tehama", "65498"},
      {"Trinity", "16060"},        {"Tulare", "477054"},
      {"Tuolumne", "55810"},       {"Ventura", "839784"},
      {"Yolo", "216986"},          {"Yuba", "83421"},
  };
  std::vector<std::string> command_line{argv, argv + argc};
  if (command_line.size() < 2) {
    std::cout << "Please specify a county name on the command line. Exiting.\n";
    std::cout << "For example: " << command_line.at(0) << " \"Los Angeles\"\n";
    std::cout << "The counties in California are: ";
    std::cout << AllCountiesString(ca_counties) << "\n";
    return 1;
  }
  int county_population = CountyPopulation(ca_counties, command_line.at(1));
  if (county_population != -1) {
    std::cout << "The population of " << command_line.at(1) << " County is "
              << county_population << ". ";
    // StatePopulation() returns an int and we need to do some floating
    // point division, so cast the int to a double. This is safe because
    // no state has a population that is larger than the maximum double.
    double state_population{static_cast<double>(StatePopulation(ca_counties))};

    // We only need two decimal places so we use std::fixed and
    // std::setprecision(2) to print out only 2 decimal places.
    std::cout << "That represents " << std::fixed << std::setprecision(2)
              << (county_population / state_population) * 100.0
              << "% of the entire state's population.\n";
  } else {
    std::cout << "Error: " << command_line.at(1)
              << " is not in the vector. Please check your spelling.\n";
    std::cout << "The counties in California are: ";
    std::cout << AllCountiesString(ca_counties) << "\n";
    return 1;
  }

  return 0;
}