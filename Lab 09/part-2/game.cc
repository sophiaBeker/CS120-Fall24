
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
  std::ifstream infile("secret.dat");
  if (!infile.good()) {
    std::cerr << "error: cannot read secret.dat\n";
    return 1;
  }

  int secret = 0;
  infile >> secret;
  if (infile.fail()) {
    std::cerr << "error: secret.dat malformed\n";
    return 1;
  }

  if (secret < 1 || secret > 10) {
    std::cerr << "error: secret.dat malformed\n";
    return 1;
  }

  int guess = 0;
  std::cout << "Enter your guess: ";
  std::cin >> guess;

  if (guess == secret) {
    std::cout << "Correct, you win!\n";
  } else {
    std::cout << "Incorrect, the secret number was " << secret
              << ", you lose.\n";
  }
  return 0;
}