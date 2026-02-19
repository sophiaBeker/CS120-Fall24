// TODO: Add your header

/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>

#include <cassert>
#include <climits>
#include <cstdio>
#include <future>

#include "judge_functions.h"

// Thanks to Paul Inventado
// https://github.com/google/googletest/issues/348#issuecomment-431714269
#define MAX_DURATION_MS 500
// Fail immediately.
// NOLINT(cppcoreguidelines-macro-usage)
#define ASSERT_DURATION_LE(millisecs, stmt)                                 \
  {                                                                         \
    std::promise<bool> completed;                                           \
    auto stmt_future = completed.get_future();                              \
    std::thread(                                                            \
        [&](std::promise<bool>& completed) {                                \
          stmt;                                                             \
          completed.set_value(true);                                        \
        },                                                                  \
        std::ref(completed))                                                \
        .detach();                                                          \
    if (stmt_future.wait_for(std::chrono::milliseconds(millisecs)) ==       \
        std::future_status::timeout)                                        \
      GTEST_FATAL_FAILURE_("\tExecution time greater than " #millisecs      \
                           " milliseconds.\n\tRevise algorithm for better " \
                           "performance and check for "                     \
                           "infinite loops.");                              \
  }

// Defer failure
// NOLINT(cppcoreguidelines-macro-usage)
#define EXPECT_DURATION_LE(millisecs, stmt)                                    \
  {                                                                            \
    std::promise<bool> completed;                                              \
    auto stmt_future = completed.get_future();                                 \
    std::thread(                                                               \
        [&](std::promise<bool>& completed) {                                   \
          stmt;                                                                \
          completed.set_value(true);                                           \
        },                                                                     \
        std::ref(completed))                                                   \
        .detach();                                                             \
    if (stmt_future.wait_for(std::chrono::milliseconds(millisecs)) ==          \
        std::future_status::timeout)                                           \
      GTEST_NONFATAL_FAILURE_("\tExecution time greater than " #millisecs      \
                              " milliseconds.\n\tRevise algorithm for better " \
                              "performance and check for "                     \
                              "infinite loops.");                              \
  }

#define FP_DELTA 0.001
namespace {

// Test JudgeAverage
TEST(Judge, JudgeAverage) {
  std::vector<std::vector<double>> test_values{
      {
          5.0,
          5.0,
          5.0,
      },
      {
          0.0,
          0.0,
          0.0,
      },
      {
          1.0,
          2.0,
          3.0,
      },
      {
          3.0,
          2.0,
          1.0,
      },
      {
          5.1,
          8.7,
          9.0,
          2.6,
          1.9,
      },
      {
          3.0,
          5.0,
          7.0,
          8.0,
      },
      {
          3.0,
          5.0,
          8.0,
          7.0,
      },
      {
          3.0,
          7.0,
          5.0,
          8.0,
      },
      {
          3.0,
          7.0,
          8.0,
          5.0,
      },
      {
          3.0,
          8.0,
          5.0,
          7.0,
      },
      {
          3.0,
          8.0,
          7.0,
          5.0,
      },
      {
          5.0,
          3.0,
          7.0,
          8.0,
      },
      {
          5.0,
          3.0,
          8.0,
          7.0,
      },
      {
          5.0,
          7.0,
          3.0,
          8.0,
      },
      {
          5.0,
          7.0,
          8.0,
          3.0,
      },
      {
          5.0,
          8.0,
          3.0,
          7.0,
      },
      {
          5.0,
          8.0,
          7.0,
          3.0,
      },
      {
          7.0,
          3.0,
          5.0,
          8.0,
      },
      {
          7.0,
          3.0,
          8.0,
          5.0,
      },
      {
          7.0,
          5.0,
          3.0,
          8.0,
      },
      {
          7.0,
          5.0,
          8.0,
          3.0,
      },
      {
          7.0,
          8.0,
          3.0,
          5.0,
      },
      {
          7.0,
          8.0,
          5.0,
          3.0,
      },
      {
          8.0,
          3.0,
          5.0,
          7.0,
      },
      {
          8.0,
          3.0,
          7.0,
          5.0,
      },
      {
          8.0,
          5.0,
          3.0,
          7.0,
      },
      {
          8.0,
          5.0,
          7.0,
          3.0,
      },
      {
          8.0,
          7.0,
          3.0,
          5.0,
      },
      {
          8.0,
          7.0,
          5.0,
          3.0,
      },
      {
          3.0,
          1.0,
          1.0,
          5.0,
      },
      {
          4.0,
          2.0,
          9.0,
          9.0,
          3.0,
      },
  };
  std::vector<double> expected_value{
      5.0, 0.0, 2.0, 2.0, 5.46667, 6.0, 6.0, 6.0, 6.0,    6.0, 6.0,
      6.0, 6.0, 6.0, 6.0, 6.0,     6.0, 6.0, 6.0, 6.0,    6.0, 6.0,
      6.0, 6.0, 6.0, 6.0, 6.0,     6.0, 6.0, 2.0, 5.33333};
  assert(test_values.size() == expected_value.size());
  auto tv_it = test_values.begin();
  auto expected_it = expected_value.begin();
  while (tv_it != test_values.end()) {
    double val = JudgeAverage(*tv_it);
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_NEAR(*expected_it, val, FP_DELTA));
    ++tv_it;
    ++expected_it;
  }
}

}  // namespace
