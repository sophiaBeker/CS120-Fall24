
#ifndef SPELLING_FUNCTIONS_H
#define SPELLING_FUNCTIONS_H

#include <string>
#include <vector>

// Read all of the words contained in the given filename.
// Returns an empty vector if there is an I/O error.
std::vector<std::string> ReadWords(const std::string& filename);

// Return true if word is present in dictionary, or false otherwise.
// dictionary is intended to be a vector containing all words from a words.txt
// file.
// word is intended to be a string from a document file, that may or may not
// be spelled properly.
bool InDictionary(const std::vector<std::string>& dictionary,
                  const std::string& word);

// Return a vector containing all of the misspelled words in document.
// dictionary is intended to be a vector containing all words from a words.txt
// file.
// document is intended to be a vector of all of the words from a document
// file.
// The returned vector should contain the misspelled words, in the same order
// that they appeared in document.
std::vector<std::string> MisspelledWords(
    const std::vector<std::string>& dictionary,
    const std::vector<std::string>& document);

#endif  // SPELLING_FUNCTIONS_H
