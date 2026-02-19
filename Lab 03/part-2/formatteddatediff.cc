
#include <iostream>
#include <string>

// Given a month, day, and year, calculate the Julian day number using the
// Fliegel & Van Flandern equation.
int JulianDay(int month, int day, int year) {
  int julian_day = day - 32075 + 1461 * (year + 4800 + (month - 14) / 12) / 4 +
                   367 * (month - 2 - (month - 14) / 12 * 12) / 12 -
                   3 * ((year + 4900 + (month - 14) / 12) / 100) / 4;
  return julian_day;
}

// Return the number of days between a start date and end date.
int DateDifference(int start_month, int start_day, int start_year,
                   int end_month, int end_day, int end_year) {
  int year_diff = end_year - start_year;
  int year_into_day = year_diff * 365;
  int month_diff = end_month - start_month;
  int month_into_day = month_diff * 30;
  int day_diff = end_day - start_day;
  int day_total = year_into_day + month_into_day + day_diff;

  return day_total;
}

// Print the given date to standard output in the format MM/DD/YYYY
void PrintDate(int month, int day, int year) {
  std::cout << month << "/" << day << "/" << year;
}

// Prompt the computer with a question, capture their answer, and return it to
// the caller
int PromptForInt(std::string query) {
  std::cout << query;
  int answer = 0;
  std::cin >> answer;
  return answer;
}

int main(int argc, char* argv[]) {
  std::string start_month_prompt = "Enter a start month: ";
  int start_month = PromptForInt(start_month_prompt);
  std::string start_day_prompt = "Enter a start day: ";
  int start_day = PromptForInt(start_day_prompt);
  std::string start_year_prompt = "Enter a start year: ";
  int start_year = PromptForInt(start_year_prompt);

  std::string end_month_prompt = "Enter an end month: ";
  int end_month = PromptForInt(end_month_prompt);
  std::string end_day_prompt = "Enter an end day: ";
  int end_day = PromptForInt(end_day_prompt);
  std::string end_year_prompt = "Enter an end year: ";
  int end_year = PromptForInt(end_year_prompt);

  int difference = DateDifference(start_month, start_day, start_year, end_month,
                                  end_day, end_year);

  std::cout << "The number of days between";
  PrintDate(start_month, start_day, start_year);
  std::cout << " and ";
  PrintDate(end_month, end_day, end_year);
  std::cout << " is ";
  std::cout << difference;
  std::cout << " days.\n";

  return 0;
}
