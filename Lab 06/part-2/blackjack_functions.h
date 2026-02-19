
/* Do not edit below this line. */
/* Do not edit below this line. */
/* Do not edit below this line. */

#ifndef BLACKJACK_FUNCTIONS_H
#define BLACKJACK_FUNCTIONS_H

#include <string>

// Determine whether card_name is the name of an ace ("A").
// Returns true if card_name represents an ace, or false otherwise.
bool IsAce(const std::string& card_name);

// Determine whether card_name is the name of a face card ("J", "Q", or "K").
// Returns true if card_name represents a face card, or false otherwise.
bool IsFaceCard(const std::string& card_name);

// Determine whether card_name is the name of a number card ("2", "3",
// through "10").
// Returns true if card_name represents a number card, or false otherwise.
bool IsNumberCard(const std::string& card_name);

// Determine whether str is a valid card name.
// Returns true if str is an ace, face card, or number card; or false
// otherwise.
bool IsCardName(const std::string& str);

// Calculate the score for one card.
// An ace is worth 1 point; a face card is worth 10 points; and a number card
// is worth its value (so for example, "4" is worth 4 points).
// This function assumes that card_name is a valid card name.
// Returns the number of points for the card.
int CardPoints(const std::string& card_name);

// Determine whether a blackjack hand score is a bust.
// A score is a bust when it is greater than 21.
// Returns true if score is a bust, or false otherwise.
bool IsBust(int score);

// Calculate the score for a hand of two cards.
// A hand scores points for each card. In addition, if the hand contains an
// ace, the "ace bonus" increases the score by 10, unless that would cause
// the score to bust.
// This function assumes that card_1 and card_2 are valid card names.
// Returns the score for a hand containing card_1 and card_2.
int TwoCardHandScore(const std::string& card_1, const std::string& card_2);

#endif