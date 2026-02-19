
#include "hilo_functions.h"

#include "rng.h"

GameState::GameState(int secret) : secret_(secret), guesses_left_(4) {}

int GameState::Secret() const { return secret_; }

int GameState::GuessesLeft() const { return guesses_left_; }

bool GameState::GuessCorrect(int guess) const {
  if (guess == secret_) {
    return true;
  }
  return false;
}

bool GameState::GuessTooBig(int guess) const {
  if (guess > secret_) {
    return true;
  }
  return false;
}

bool GameState::GuessTooSmall(int guess) const {
  if (guess < secret_) {
    return true;
  }
  return false;
}

void GameState::CountGuess() { --guesses_left_; }

bool GameState::GameOver() const {
  if (guesses_left_ == 0) {
    return true;
  }
  return false;
}

int RandomSecretNumber() { return static_cast<int>(RandomDouble(1, 10)); }
