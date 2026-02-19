
#include "spelling_functions.h"

#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> ReadWords(const std::string& filename) {
  std::vector<std::string> words;

  std::ifstream file(filename);
  std::string word;

  while (file >> word) {
    words.push_back(word);
  }
  file.close();
  return words;
}

bool InDictionary(const std::vector<std::string>& dictionary,
                  const std::string& word) {
  for (const std::string& curr_word : dictionary) {
    if (curr_word == word) {
      return true;
    }
  }
  return false;
}

std::vector<std::string> MisspelledWords(
    const std::vector<std::string>& dictionary,
    const std::vector<std::string>& document) {
  std::vector<std::string> misspelled;

  for (const std::string& curr_word : document) {
    if (!InDictionary(dictionary, curr_word)) {
      misspelled.push_back(curr_word);
    }
  }

  return misspelled;
}
