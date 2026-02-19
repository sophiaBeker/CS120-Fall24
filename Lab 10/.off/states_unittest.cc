
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>

#include "states_functions.h"

// Thanks to Paul Inventado
// https://github.com/google/googletest/issues/348#issuecomment-431714269
// Fail immediately.
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

TEST(StateTest, ReadCSV) {
  std::vector<std::vector<std::string>> states{
      ReadCSV("state_demographics.csv")};
  ASSERT_FALSE(states.empty());
  ASSERT_EQ(50, states.size());

  ASSERT_EQ(3, states.at(1).size());
  EXPECT_EQ("Connecticut", states.at(0).at(0));
  EXPECT_EQ("4842.36", states.at(0).at(2));

  ASSERT_EQ(3, states.at(49).size());
  EXPECT_EQ("Wyoming", states.at(49).at(0));
  EXPECT_EQ("97093.14", states.at(49).at(2));
}

TEST(StateTest, PopulationDensity) {
  std::vector<std::string> california{"California", "39538223", "155779.22"};
  std::vector<std::string> vermont{"Vermont", "643077", "9216.66"};
  EXPECT_NEAR(253.809, PopulationDensity(california), 0.1);
  EXPECT_NEAR(69.773, PopulationDensity(vermont), 0.1);
}

TEST(StateTest, Name) {
  std::vector<std::string> california{"California", "39538223", "155779.22"};
  std::vector<std::string> vermont{"Vermont", "643077", "9216.66"};
  EXPECT_EQ("California", Name(california));
  EXPECT_EQ("Vermont", Name(vermont));
}

TEST(StateTest, Population) {
  std::vector<std::string> california{"California", "39538223", "155779.22"};
  std::vector<std::string> vermont{"Vermont", "643077", "9216.66"};
  EXPECT_EQ(39538223, Population(california));
  EXPECT_EQ(643077, Population(vermont));
}

TEST(StateTest, LandArea) {
  std::vector<std::string> california{"California", "39538223", "155779.22"};
  std::vector<std::string> vermont{"Vermont", "643077", "9216.66"};
  EXPECT_NEAR(155779.22, LandArea(california), 0.1);
  EXPECT_NEAR(9216.66, LandArea(vermont), 0.1);
}
