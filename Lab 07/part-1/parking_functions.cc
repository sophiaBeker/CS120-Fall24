
#include "parking_functions.h"

#include <string>

bool CanParkOnAsh(const std::string& day, int hour) {
  if (day == "wed") {
    if ((hour >= 10) && (hour < 12)) {
      return false;
    }
  }
  return true;
}

bool CanParkOnBeech(const std::string& day, int hour) {
  if (day == "fri") {
    if ((hour >= 8) && (hour < 12)) {
      return false;
    }
  }
  return true;
}

bool CanParkOnCedar(const std::string& day, int hour) {
  if (hour >= 19 || hour < 7) {
    return false;
  }
  if (day == "tue") {
    if (hour >= 8 && hour < 10) {
      return false;
    }
  }
  return true;
}

bool CanParkOnDate(const std::string& day, int hour, int min) {
  if (day != "sat" && day != "sun") {
    if (hour == 6) {
      if (min >= 30) {
        return false;
      }
    } else if (hour >= 6 && hour < 16) {
      return false;
    }
  }
  return true;
}
