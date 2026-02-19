
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>

#include <climits>
#include <cstdio>
#include <future>

#include "blackjack_functions.h"

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

// Test IsAce
TEST(BlackJack, IsAce) {
  // true
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsAce("A")));

  // false: other card names
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("K")));

  // false: not a card name
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce(" ")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("1")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsAce("apple")));
}

// Test IsFaceCard
TEST(BlackJack, IsFaceCard) {
  // true
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsFaceCard("J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsFaceCard("Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsFaceCard("K")));

  // false: other card names
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("10")));

  // false: not a card name
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard(" ")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("1")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsFaceCard("apple")));
}

// Test IsNumberCard
TEST(BlackJack, IsNumberCard) {
  // true
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsNumberCard("10")));

  // false: other card names
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("K")));

  // false: not a card name
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard(" ")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("1")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsNumberCard("apple")));
}

// Test IsCardName
TEST(BlackJack, IsCardName) {
  // true
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsCardName("K")));

  // false: not a card name
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsCardName("")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsCardName(" ")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsCardName("1")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsCardName("apple")));
}

// Test CardPoints
TEST(BlackJack, CardPoints) {
  // face cards are worth 10
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, CardPoints("J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, CardPoints("Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, CardPoints("K")));

  // number cards are worth their value
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(2, CardPoints("2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(3, CardPoints("3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(4, CardPoints("4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(5, CardPoints("5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(6, CardPoints("6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(7, CardPoints("7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, CardPoints("8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, CardPoints("9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, CardPoints("10")));

  // ace is worth 1
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(1, CardPoints("A")));
}

// Test IsBust
TEST(BlackJack, IsBust) {
  // false: score less than 21
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(0)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(1)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(2)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(3)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(4)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(5)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(6)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(7)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(8)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(9)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(10)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(11)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(12)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(13)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(14)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(15)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(16)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(17)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(18)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(19)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(20)));

  // edge case: 21 is not a bust
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_FALSE(IsBust(21)));

  // true: scores greater than 21
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(22)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(23)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(24)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(25)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(26)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(27)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(28)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(29)));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_TRUE(IsBust(30)));
}

// Test TwoCardHandScore
// These hands do not have aces, so the calculation does not involve the ace
// bonus.
TEST(BlackJack, TwoCardHandScoreNoAce) {
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(4, TwoCardHandScore("2", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(5, TwoCardHandScore("2", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(6, TwoCardHandScore("2", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(7, TwoCardHandScore("2", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, TwoCardHandScore("2", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("2", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("2", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("2", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("2", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("2", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("2", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("2", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(5, TwoCardHandScore("3", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(6, TwoCardHandScore("3", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(7, TwoCardHandScore("3", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, TwoCardHandScore("3", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("3", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("3", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("3", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("3", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("3", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("3", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("3", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("3", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(6, TwoCardHandScore("4", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(7, TwoCardHandScore("4", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, TwoCardHandScore("4", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("4", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("4", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("4", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("4", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("4", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("4", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("4", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("4", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("4", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(7, TwoCardHandScore("5", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, TwoCardHandScore("5", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("5", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("5", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("5", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("5", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("5", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("5", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("5", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("5", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("5", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("5", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(8, TwoCardHandScore("6", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("6", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("6", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("6", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("6", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("6", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("6", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("6", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("6", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("6", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("6", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("6", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(9, TwoCardHandScore("7", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("7", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("7", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("7", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("7", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("7", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("7", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("7", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("7", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("7", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("7", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("7", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(10, TwoCardHandScore("8", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("8", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("8", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("8", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("8", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("8", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("8", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("8", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("8", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("8", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("8", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("8", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(11, TwoCardHandScore("9", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("9", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("9", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("9", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("9", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("9", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("9", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("9", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("9", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("9", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("9", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("9", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("10", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("10", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("10", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("10", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("10", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("10", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("10", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("10", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("10", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("10", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("10", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("10", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("J", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("J", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("J", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("J", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("J", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("J", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("J", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("J", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("J", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("J", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("J", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("J", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("Q", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("Q", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("Q", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("Q", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("Q", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("Q", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("Q", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("Q", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("Q", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("Q", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("Q", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("Q", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("K", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("K", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("K", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("K", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("K", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("K", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("K", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("K", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("K", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("K", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("K", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("K", "K")));
}

// Test TwoCardHandScore
// These hands have an ace.
TEST(BlackJack, TwoCardHandScoreHasAce) {
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("A", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("A", "2")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("A", "3")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("A", "4")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("A", "5")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("A", "6")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("A", "7")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("A", "8")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("A", "9")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("A", "10")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("A", "J")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("A", "Q")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("A", "K")));

  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(12, TwoCardHandScore("A", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(13, TwoCardHandScore("2", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(14, TwoCardHandScore("3", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(15, TwoCardHandScore("4", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(16, TwoCardHandScore("5", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(17, TwoCardHandScore("6", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(18, TwoCardHandScore("7", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(19, TwoCardHandScore("8", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(20, TwoCardHandScore("9", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("10", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("J", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("Q", "A")));
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     EXPECT_EQ(21, TwoCardHandScore("K", "A")));
}

}  // namespace
