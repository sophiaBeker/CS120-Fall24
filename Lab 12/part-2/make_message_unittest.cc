
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>
#include <limits.h>

#include <cstdio>
#include <future>

#include "make_message_functions.h"

#define MAX_DURATION_MS 500

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
namespace {

// Tests bool HasMatchingFileExtension(const std::string& file_name, const
// std::string& extension);
TEST(HasMatchingFileExtension, Exists) {
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(true, HasMatchingFileExtension("image.jpg", ".jpg")));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(true, HasMatchingFileExtension("image.png", ".png")));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(true, HasMatchingFileExtension("image.JPEG", ".JPEG")));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(true, HasMatchingFileExtension("image.GIF", ".GIF")));
}

TEST(HasMatchingFileExtension, NotExist) {
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(false, HasMatchingFileExtension("image.jpg", ".foo")));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(false, HasMatchingFileExtension("image.png", ".foo")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(false, HasMatchingFileExtension(".fo", ".foo")));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      EXPECT_EQ(false, HasMatchingFileExtension("image.FOO", ".foo")));
}

TEST(RandomDouble_01, PredictableSeries) {
  std::vector<double> rng_01_data{
      0.58231516549037909414, 0.13479628997421794212,  0.64552797773575854023,
      0.27581615048304697346, 0.53162577114150422197,  0.73923126604255440242,
      0.62415379153687022828, 0.317402652348019787,    0.21461918869016097244,
      0.82128335137607044736, 0.97977227094070373781,  0.6257096265741706187,
      0.40112491637792774268, 0.028305164998422574496, 0.15491651941801320991,
      0.47041200178050718295, 0.10320131647333954938,  0.89535648001162149168,
      0.60738285819446014013, 0.40632942511192926549};

  for (int i = 0; i < rng_01_data.size(); i++) {
    EXPECT_DOUBLE_EQ(RandomDouble01(), rng_01_data.at(i));
  }
}

TEST(CoinFlip, PredictableSeries) {
  std::vector<bool> coin_flip_data{1, 0, 1, 0, 1, 1, 1, 0, 0, 1,
                                   1, 1, 0, 0, 0, 0, 0, 1, 1, 0};
  for (int i = 0; i < coin_flip_data.size(); i++) {
    EXPECT_EQ(CoinFlip(), coin_flip_data.at(i));
  }
}

}  // namespace
