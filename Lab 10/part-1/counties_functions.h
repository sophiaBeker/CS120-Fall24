
/* You do not need to make any changes to this file. */

#include <string>
#include <vector>

#ifndef COUNTIES_FUNCTIONS_H
#define COUNTIES_FUNCTIONS_H

std::string AllCountiesString(
    const std::vector<std::vector<std::string>>& counties);

int CountyPopulation(const std::vector<std::vector<std::string>>& counties,
                     const std::string& match_county);

int StatePopulation(const std::vector<std::vector<std::string>>& counties);
#endif