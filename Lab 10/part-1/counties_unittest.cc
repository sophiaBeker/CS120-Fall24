
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#include <gtest/gtest.h>
#include <limits.h>

#include <cstdio>
#include <future>

#include "counties_functions.h"

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

std::vector<std::vector<std::string>> ca_counties{
    {"Alameda", "1648556"},      {"Alpine", "1235"},
    {"Amador", "41259"},         {"Butte", "208309"},
    {"Calaveras", "46221"},      {"Colusa", "21917"},
    {"Contra Costa", "1161413"}, {"Del Norte", "28100"},
    {"El Dorado", "193221"},     {"Fresno", "1013581"},
    {"Glenn", "28805"},          {"Humboldt", "136310"},
    {"Imperial", "179851"},      {"Inyo", "18970"},
    {"Kern", "917673"},          {"Kings", "153443"},
    {"Lake", "68766"},           {"Lassen", "33159"},
    {"Los Angeles", "9829544"},  {"Madera", "159410"},
    {"Marin", "260206"},         {"Mariposa", "17147"},
    {"Mendocino", "91305"},      {"Merced", "286461"},
    {"Modoc", "8661"},           {"Mono", "13247"},
    {"Monterey", "437325"},      {"Napa", "136207"},
    {"Nevada", "103487"},        {"Orange", "3167809"},
    {"Placer", "412300"},        {"Plumas", "19915"},
    {"Riverside", "2458395"},    {"Sacramento", "1588921"},
    {"San Benito", "66677"},     {"San Bernardino", "2194710"},
    {"San Diego", "3286069"},    {"San Francisco", "815201"},
    {"San Joaquin", "789410"},   {"San Luis Obispo", "283159"},
    {"San Mateo", "737888"},     {"Santa Barbara", "446475"},
    {"Santa Clara", "1885508"},  {"Santa Cruz", "267792"},
    {"Shasta", "182139"},        {"Sierra", "3283"},
    {"Siskiyou", "44118"},       {"Solano", "451716"},
    {"Sonoma", "485887"},        {"Stanislaus", "552999"},
    {"Sutter", "99063"},         {"Tehama", "65498"},
    {"Trinity", "16060"},        {"Tulare", "477054"},
    {"Tuolumne", "55810"},       {"Ventura", "839784"},
    {"Yolo", "216986"},          {"Yuba", "83421"},
};

// Tests std::string AllCountiesString(const std::array<std::array<std::string,
// 58>, 2>& ca_counties);

// "Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El
// Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles
// Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange
// Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San
// Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara
// Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama
// Trinity Tulare Tuolumne Ventura Yolo Yuba "

// Tests negative input.
TEST(AllCountiesString, String) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(
             "Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama Trinity Tulare Tuolumne Ventura Yolo Yuba ",
             AllCountiesString(ca_counties)));
}

// Tests int CountyIndex(const std::array<std::array<std::string, 58>, 2>&
// ca_counties, const std::string match_county);
TEST(CountyPopulation, Found) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(1648556, CountyPopulation(ca_counties, "Alameda")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(1235, CountyPopulation(ca_counties, "Alpine")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(41259, CountyPopulation(ca_counties, "Amador")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(208309, CountyPopulation(ca_counties, "Butte")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(46221, CountyPopulation(ca_counties, "Calaveras")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(21917, CountyPopulation(ca_counties, "Colusa")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(1161413, CountyPopulation(ca_counties, "Contra Costa")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(28100, CountyPopulation(ca_counties, "Del Norte")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(193221, CountyPopulation(ca_counties, "El Dorado")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(1013581, CountyPopulation(ca_counties, "Fresno")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(28805, CountyPopulation(ca_counties, "Glenn")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(136310, CountyPopulation(ca_counties, "Humboldt")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(179851, CountyPopulation(ca_counties, "Imperial")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(18970, CountyPopulation(ca_counties, "Inyo")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(917673, CountyPopulation(ca_counties, "Kern")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(153443, CountyPopulation(ca_counties, "Kings")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(68766, CountyPopulation(ca_counties, "Lake")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(33159, CountyPopulation(ca_counties, "Lassen")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(9829544, CountyPopulation(ca_counties, "Los Angeles")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(159410, CountyPopulation(ca_counties, "Madera")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(260206, CountyPopulation(ca_counties, "Marin")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(17147, CountyPopulation(ca_counties, "Mariposa")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(91305, CountyPopulation(ca_counties, "Mendocino")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(286461, CountyPopulation(ca_counties, "Merced")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(8661, CountyPopulation(ca_counties, "Modoc")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(13247, CountyPopulation(ca_counties, "Mono")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(437325, CountyPopulation(ca_counties, "Monterey")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(136207, CountyPopulation(ca_counties, "Napa")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(103487, CountyPopulation(ca_counties, "Nevada")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(3167809, CountyPopulation(ca_counties, "Orange")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(412300, CountyPopulation(ca_counties, "Placer")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(19915, CountyPopulation(ca_counties, "Plumas")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(2458395, CountyPopulation(ca_counties, "Riverside")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(1588921, CountyPopulation(ca_counties, "Sacramento")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(66677, CountyPopulation(ca_counties, "San Benito")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(2194710, CountyPopulation(ca_counties, "San Bernardino")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(3286069, CountyPopulation(ca_counties, "San Diego")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(815201, CountyPopulation(ca_counties, "San Francisco")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(789410, CountyPopulation(ca_counties, "San Joaquin")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(283159, CountyPopulation(ca_counties, "San Luis Obispo")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(737888, CountyPopulation(ca_counties, "San Mateo")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(446475, CountyPopulation(ca_counties, "Santa Barbara")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(1885508, CountyPopulation(ca_counties, "Santa Clara")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(267792, CountyPopulation(ca_counties, "Santa Cruz")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(182139, CountyPopulation(ca_counties, "Shasta")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(3283, CountyPopulation(ca_counties, "Sierra")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(44118, CountyPopulation(ca_counties, "Siskiyou")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(451716, CountyPopulation(ca_counties, "Solano")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(485887, CountyPopulation(ca_counties, "Sonoma")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(552999, CountyPopulation(ca_counties, "Stanislaus")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(99063, CountyPopulation(ca_counties, "Sutter")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(65498, CountyPopulation(ca_counties, "Tehama")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(16060, CountyPopulation(ca_counties, "Trinity")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(477054, CountyPopulation(ca_counties, "Tulare")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(55810, CountyPopulation(ca_counties, "Tuolumne")));
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(839784, CountyPopulation(ca_counties, "Ventura")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(216986, CountyPopulation(ca_counties, "Yolo")));
  EXPECT_DURATION_LE(5,
                     EXPECT_EQ(83421, CountyPopulation(ca_counties, "Yuba")));
}

TEST(CountyPopulation, NotFound) {
  EXPECT_DURATION_LE(
      5, EXPECT_EQ(-1, CountyPopulation(ca_counties, "Tulare County")));
  EXPECT_DURATION_LE(5, EXPECT_EQ(-1, CountyPopulation(ca_counties, "Junk")));
}

}  // namespace
