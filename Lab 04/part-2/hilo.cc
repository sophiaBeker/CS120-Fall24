
#include <iostream>

int main(int argc, char const *argv[]) {
  int secret{0};
  std::cout << "Player 1, enter the secret number: ";
  std::cin >> secret;

  int guess{0};
  std::cout << "Player 2, enter your first guess: ";
  std::cin >> guess;

  if (secret == guess) {
    std::cout << "Correct, you win!\n";
  } else {
    if (guess < secret) {
      std::cout << "Too low\n";
    } else {
      std::cout << "Too high\n";
    }
    std::cout << "Player 2, enter your second guess: ";
    std::cin >> guess;

    if (secret == guess) {
      std::cout << "Correct, you win!\n";
    } else {
      std::cout << "Incorrect, the secret number was " << secret
                << ", you lose.\n";
    }
  }
  return 0;
}
