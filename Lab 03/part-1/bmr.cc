
#include <iostream>

// Given a person's weight (in pounds), height (in inches), and age (in
// years), calculate the BMR of that person using the Mifflin St Jeor
// equation for men.
double BMRMan(double weight, double height, int age) {
  return (4.536 * weight) + (15.88 * height) - (5 * age) + 5;
}

// Given a person's weight (in pounds), height (in inches), and age (in
// years), calculate the BMR of that person using the Mifflin St Jeor
// equation for women.
double BMRWoman(double weight, double height, int age) {
  return (4.536 * weight) + (15.88 * height) - (5 * age) - 161;
}

int main(int argc, char* argv[]) {
  double input_weight = 0;
  std::cout << "Enter weight in pounds: ";
  std::cin >> input_weight;

  double input_height = 0;
  std::cout << "Enter height in inches: ";
  std::cin >> input_height;

  int input_age = 0;
  std::cout << "Enter age in years: ";
  std::cin >> input_age;

  double bmr_man = BMRMan(input_weight, input_height, input_age);

  double bmr_woman = BMRWoman(input_weight, input_height, input_age);

  std::cout << "Man: " << bmr_man << " calories per day" << "\n";

  std::cout << "Woman: " << bmr_woman << " calories per day" << "\n";

  return 0;
}
