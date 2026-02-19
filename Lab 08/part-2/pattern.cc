
#include <iostream>

const int kCounterMax{22};

int main(int argc, char const *argv[]) {
  for (int i = 0; i < kCounterMax; i++) {
    for (int j = i; j > 0; j--) {
      std::cout << "-";
    }
    std::cout << "*";
    for (int k = i; k < kCounterMax; k++) {
      std::cout << "|";
    }
    std::cout << "\n";
  }

  return 0;
}
