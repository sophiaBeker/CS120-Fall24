
#include <iostream>
#include <string>
#include <vector>

#include "spelling_functions.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> command{argv, argv + argc};

  if (argc != 2) {
    std::cout << "error: you must give a document filename ";
    return 1;
  }

  std::string filename = command.at(1);

  std::vector<std::string> dictionary{ReadWords("words.txt")};

  std::vector<std::string> words{ReadWords(filename)};

  std::vector<std::string> misspelled{MisspelledWords(dictionary, words)};

  std::cout << "spelling errors: \n";
  for (const std::string& curr_word : misspelled) {
    std::cout << curr_word << "\n";
  }

  return 0;
}
