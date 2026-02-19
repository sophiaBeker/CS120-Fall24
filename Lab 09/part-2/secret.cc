
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
  std::vector<std::string> command{argv, argv + argc};

  if (command.size() != 2) {
    std::cerr << "error: you must provide a secret number\n";
    return 1;
  }

  int secret = 0;
  try {
    secret = std::stoi(command[1]);
  } catch (const std::invalid_argument&) {
    std::cerr << "error: secret number must be between 1 and 10\n";
    return 1;
  }

  if (secret < 1 || secret > 10) {
    std::cerr << "error: secret number must be between 1 and 10\n";
    return 1;
  }

  std::ofstream out_file("secret.dat");
  if (!out_file) {
    std::cerr << "error: cannot open secret.dat for writing\n";
    return 1;
  }

  out_file << secret;
  if (!out_file) {
    std::cerr << "error: failed to write to secret.dat\n";
    return 1;
  }

  return 0;
}
