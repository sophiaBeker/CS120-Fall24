
#include <iostream>
#include <string>
#include <vector>

#include "states_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::vector<std::string>> states{
      ReadCSV("state_demographics.csv")};

  // TODO: Initialize densest_state to the first state from the
  // states vector.
  std::vector<std::string> densest_state;

  // TODO: Initialize sparsest_state to the first state from the
  // states vector.
  std::vector<std::string> sparsest_state;

  // TODO: Write a for loop and iterate through the states vector.
  // For each state in the states vector, check to see if the
  // population density is greater than the densest_state. If true,
  // then update densest_state to be the new state.
  // Next, check to see if the population density is less than the
  // sparsest_state. If true, then update sparsest_state to be the
  // new state.

  std::cout << "The densest state is " << Name(densest_state) << " ("
            << PopulationDensity(densest_state) << ")\n";

  std::cout << "The sparsest state is " << Name(sparsest_state) << " ("
            << PopulationDensity(sparsest_state) << ")\n";

  return 0;
}
