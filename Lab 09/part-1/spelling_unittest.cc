
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>

#include <cassert>
#include <climits>
#include <cstdio>
#include <future>

#include "spelling_functions.h"

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

TEST(Spelling, ReadWords) {
  {  // fox.txt
    std::vector<std::string> words;
    EXPECT_DURATION_LE(MAX_DURATION_MS, words = ReadWords("fox.txt"));
    ASSERT_EQ(9, words.size());
    EXPECT_EQ("the", words.at(0));
    EXPECT_EQ("quick", words.at(1));
    EXPECT_EQ("brown", words.at(2));
    EXPECT_EQ("fox", words.at(3));
    EXPECT_EQ("jumps", words.at(4));
    EXPECT_EQ("over", words.at(5));
    EXPECT_EQ("the", words.at(6));
    EXPECT_EQ("lazy", words.at(7));
    EXPECT_EQ("dog", words.at(8));
  }

  {  // 120.txt
    std::vector<std::string> words;
    EXPECT_DURATION_LE(MAX_DURATION_MS, words = ReadWords("120.txt"));

    // check only the size, first three words, and last three words
    ASSERT_EQ(42, words.size());

    EXPECT_EQ("Introduction", words.at(0));
    EXPECT_EQ("to", words.at(1));
    EXPECT_EQ("the", words.at(2));

    EXPECT_EQ("and", words.at(39));
    EXPECT_EQ("object-oriented", words.at(40));
    EXPECT_EQ("methodologies.", words.at(41));
  }

  {  // leota.txt
    std::vector<std::string> words;
    EXPECT_DURATION_LE(MAX_DURATION_MS, words = ReadWords("leota.txt"));

    // check only the size, first three words, and last three words
    ASSERT_EQ(56, words.size());

    EXPECT_EQ("Serpents", words.at(0));
    EXPECT_EQ("and", words.at(1));
    EXPECT_EQ("spiders,", words.at(2));

    EXPECT_EQ("from", words.at(53));
    EXPECT_EQ("regions", words.at(54));
    EXPECT_EQ("beyond!", words.at(55));
  }

  {  // lincoln.txt
    std::vector<std::string> words;
    EXPECT_DURATION_LE(MAX_DURATION_MS, words = ReadWords("lincoln.txt"));

    // check only the size, first three words, and last three words
    ASSERT_EQ(102, words.size());

    EXPECT_EQ("Four", words.at(0));
    EXPECT_EQ("score", words.at(1));
    EXPECT_EQ("and", words.at(2));

    EXPECT_EQ("should", words.at(99));
    EXPECT_EQ("do", words.at(100));
    EXPECT_EQ("this.", words.at(101));
  }

  {  // words.txt
    std::vector<std::string> words;
    EXPECT_DURATION_LE(MAX_DURATION_MS, words = ReadWords("words.txt"));

    // check only the size, first three words, and last three words
    ASSERT_EQ(102401, words.size());

    EXPECT_EQ("A", words.at(0));
    EXPECT_EQ("A's", words.at(1));
    EXPECT_EQ("AMD", words.at(2));

    EXPECT_EQ("étude", words.at(102398));
    EXPECT_EQ("étude's", words.at(102399));
    EXPECT_EQ("études", words.at(102400));
  }

  {  // Returns an empty vector if there is an I/O error.
    std::vector<std::string> words{ReadWords("NONEXISTENT_FILE.txt")};
    EXPECT_TRUE(words.empty());
  }
}

TEST(Spelling, InDictionary) {
  // small dictionary: fox.txt
  {
    std::vector<std::string> dictionary;
    EXPECT_DURATION_LE(MAX_DURATION_MS, dictionary = ReadWords("fox.txt"));
    EXPECT_FALSE(dictionary.empty());

    // words that actually are in dictionary
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "the")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "quick")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "brown")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "fox")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "jumps")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "over")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "the")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "lazy")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "dog")));

    // words that are not in dictionary
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "computer")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "science")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "is")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "fun")));
  }

  // large dictionary: words.txt
  {
    std::vector<std::string> dictionary;
    EXPECT_DURATION_LE(MAX_DURATION_MS, dictionary = ReadWords("words.txt"));
    EXPECT_FALSE(dictionary.empty());

    // words that actually are in dictionary
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "computer")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "science")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "is")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "fun")));

    // words that are not in dictionary
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "asdf")));
    EXPECT_DURATION_LE(MAX_DURATION_MS, EXPECT_FALSE(InDictionary(
                                            dictionary, "phrase with spaces")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_FALSE(InDictionary(dictionary, "123")));

    // special cases: first and last
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "A")));
    EXPECT_DURATION_LE(MAX_DURATION_MS,
                       EXPECT_TRUE(InDictionary(dictionary, "études")));
  }
}

TEST(Spelling, MisspelledWordsSmallCases) {
  // tiny dictionary
  std::vector<std::string> dictionary{"computer", "science", "is", "fun"};

  std::vector<std::string> misspelled;

  // no misspelled words
  // two words
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"computer", "science"}));
  EXPECT_TRUE(misspelled.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {"is", "fun"}));
  EXPECT_TRUE(misspelled.empty());
  // one word
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {"computer"}));
  EXPECT_TRUE(misspelled.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {"science"}));
  EXPECT_TRUE(misspelled.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {"is"}));
  EXPECT_TRUE(misspelled.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {"fun"}));
  EXPECT_TRUE(misspelled.empty());
  // no words
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, {}));
  EXPECT_TRUE(misspelled.empty());
  // entire dictionary
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, dictionary));
  EXPECT_TRUE(misspelled.empty());

  // one misspelled word at index 0
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"the", "fun", "is",
                                                       "computer", "science"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  // one misspelled word at index 1
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"fun", "the", "is",
                                                       "computer", "science"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  // one misspelled word at index 2
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"fun", "is", "the",
                                                       "computer", "science"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  // one misspelled word at index 3
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"fun", "is", "computer",
                                                       "the", "science"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  // one misspelled word at index 4
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"fun", "is", "computer",
                                                       "science", "the"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));

  // one different misspelled word
  EXPECT_DURATION_LE(MAX_DURATION_MS, misspelled = MisspelledWords(
                                          dictionary, {"fun", "is", "score",
                                                       "computer", "science"}));
  ASSERT_EQ(1, misspelled.size());
  EXPECT_EQ("score", misspelled.at(0));

  // two misspelled words
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"the", "score", "fun", "is", "computer", "science"}));
  ASSERT_EQ(2, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"the", "fun", "score", "is", "computer", "science"}));
  ASSERT_EQ(2, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"the", "fun", "is", "score", "computer", "science"}));
  ASSERT_EQ(2, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"the", "fun", "is", "computer", "score", "science"}));
  ASSERT_EQ(2, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"the", "fun", "is", "computer", "science", "score"}));
  ASSERT_EQ(2, misspelled.size());
  EXPECT_EQ("the", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));

  // all misspelled words
  EXPECT_DURATION_LE(
      MAX_DURATION_MS,
      misspelled = MisspelledWords(
          dictionary, {"Four", "score", "and", "seven", "years", "ago"}));
  ASSERT_EQ(6, misspelled.size());
  EXPECT_EQ("Four", misspelled.at(0));
  EXPECT_EQ("score", misspelled.at(1));
  EXPECT_EQ("and", misspelled.at(2));
  EXPECT_EQ("seven", misspelled.at(3));
  EXPECT_EQ("years", misspelled.at(4));
  EXPECT_EQ("ago", misspelled.at(5));
}

TEST(Spelling, MisspelledWordsLargeCases) {
  // full dictionary
  std::vector<std::string> dictionary;
  EXPECT_DURATION_LE(MAX_DURATION_MS, dictionary = ReadWords("words.txt"));

  std::vector<std::string> document;
  std::vector<std::string> misspelled;

  EXPECT_DURATION_LE(MAX_DURATION_MS, document = ReadWords("fox.txt"));
  EXPECT_FALSE(document.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, document));
  EXPECT_TRUE(misspelled.empty());

  EXPECT_DURATION_LE(MAX_DURATION_MS, document = ReadWords("120.txt"));
  EXPECT_FALSE(document.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, document));
  ASSERT_EQ(11, misspelled.size());
  EXPECT_EQ("Introduction", misspelled.at(0));
  EXPECT_EQ("tasks,", misspelled.at(1));
  EXPECT_EQ("programs;", misspelled.at(2));
  EXPECT_EQ("programs;", misspelled.at(3));
  EXPECT_EQ("assignment;", misspelled.at(4));
  EXPECT_EQ("flow;", misspelled.at(5));
  EXPECT_EQ("input/output;", misspelled.at(6));
  EXPECT_EQ("functions;", misspelled.at(7));
  EXPECT_EQ("Structured", misspelled.at(8));
  EXPECT_EQ("object-oriented", misspelled.at(9));
  EXPECT_EQ("methodologies.", misspelled.at(10));

  EXPECT_DURATION_LE(MAX_DURATION_MS, document = ReadWords("leota.txt"));
  EXPECT_FALSE(document.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, document));
  ASSERT_EQ(18, misspelled.size());
  EXPECT_EQ("Serpents", misspelled.at(0));
  EXPECT_EQ("spiders,", misspelled.at(1));
  EXPECT_EQ("rat,", misspelled.at(2));
  EXPECT_EQ("spirits,", misspelled.at(3));
  EXPECT_EQ("at!", misspelled.at(4));
  EXPECT_EQ("Rap", misspelled.at(5));
  EXPECT_EQ("-", misspelled.at(6));
  EXPECT_EQ("respond.", misspelled.at(7));
  EXPECT_EQ("Send", misspelled.at(8));
  EXPECT_EQ("beyond...", misspelled.at(9));
  EXPECT_EQ("Goblins", misspelled.at(10));
  EXPECT_EQ("ghoulies", misspelled.at(11));
  EXPECT_EQ("Halloween,", misspelled.at(12));
  EXPECT_EQ("tambourine!", misspelled.at(13));
  EXPECT_EQ("Creepies", misspelled.at(14));
  EXPECT_EQ("crawlies,", misspelled.at(15));
  EXPECT_EQ("pond,", misspelled.at(16));
  EXPECT_EQ("beyond!", misspelled.at(17));

  EXPECT_DURATION_LE(MAX_DURATION_MS, document = ReadWords("lincoln.txt"));
  EXPECT_FALSE(document.empty());
  EXPECT_DURATION_LE(MAX_DURATION_MS,
                     misspelled = MisspelledWords(dictionary, document));
  ASSERT_EQ(18, misspelled.size());
  EXPECT_EQ("Four", misspelled.at(0));
  EXPECT_EQ("continent,", misspelled.at(1));
  EXPECT_EQ("nation,", misspelled.at(2));
  EXPECT_EQ("Liberty,", misspelled.at(3));
  EXPECT_EQ("equal.", misspelled.at(4));
  EXPECT_EQ("Now", misspelled.at(5));
  EXPECT_EQ("war,", misspelled.at(6));
  EXPECT_EQ("nation,", misspelled.at(7));
  EXPECT_EQ("dedicated,", misspelled.at(8));
  EXPECT_EQ("endure.", misspelled.at(9));
  EXPECT_EQ("We", misspelled.at(10));
  EXPECT_EQ("battle-field", misspelled.at(11));
  EXPECT_EQ("war.", misspelled.at(12));
  EXPECT_EQ("We", misspelled.at(13));
  EXPECT_EQ("field,", misspelled.at(14));
  EXPECT_EQ("live.", misspelled.at(15));
  EXPECT_EQ("It", misspelled.at(16));
  EXPECT_EQ("this.", misspelled.at(17));
}

}  // namespace
