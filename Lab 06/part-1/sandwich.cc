
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argv + argc};

  if (command_line.size() != 4) {
    std::cout << "error: you must supply three arguments";
    return 1;
  }

  std::string protein = command_line.at(1);
  std::string bread = command_line.at(2);
  std::string condiment = command_line.at(3);

  std::cout << "Your order: \n"
            << "A " << protein << " sandwich on " << bread << " with "
            << condiment << ".";
  return 0;
}
