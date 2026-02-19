
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  std::string singular_noun("singular noun");

  std::string plural_noun("plural noun");

  std::string present_tense_verb("present tense verb");

  std::cout << "Please enter a singular noun: ";
  std::cin >> singular_noun;

  std::cout << "Please enter a plural noun: ";
  std::cin >> plural_noun;

  std::cout << "Please enter a present tense verb: ";
  std::cin >> present_tense_verb;

  std::cout << "\n";
  std::cout << "Computers are small enough to fit into a ";
  std::cout << singular_noun;
  std::cout << ".\n";

  std::cout << "Computers can add, multiply, divide, and ";
  std::cout << present_tense_verb;
  std::cout << ".\n";

  std::cout << "People can ";
  std::cout << present_tense_verb;
  std::cout << " too but computers do it better";
  std::cout << ".\n";

  std::cout << "Computers have many ";
  std::cout << plural_noun;
  std::cout << " which gives them the advantage";
  std::cout << "\n";

  std::cout << "over people for many computational tasks";
  std::cout << ".\n";

  return 0;
}
