
#include "judge_functions.h"

#include <vector>

double JudgeAverage(std::vector<double>& scores) {
  double score_sum{0.0};

  for (double element : scores) {
    score_sum += element;
  }

  double minimum_score = scores.front();

  for (double element : scores) {
    if (element < minimum_score) {
      minimum_score = element;
    }
  }

  double maximum_score{scores.front()};

  for (double element : scores) {
    if (element > maximum_score) {
      maximum_score = element;
    }
  }

  double adjusted_sum = score_sum - minimum_score - maximum_score;

  double denominator = scores.size() - 2;

  double average = adjusted_sum / denominator;

  return average;
}
