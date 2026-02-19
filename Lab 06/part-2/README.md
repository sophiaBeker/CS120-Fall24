
# Blackjack Score

In this exercise, you will write a program that computes the score for a hand of blackjack. To keep things simple, the program will only deal with hands that contain exactly two cards.

## What to Do

1. Read the entire README with your partner before doing anything else.
1. If you haven't already, write `AUTHORS.md` in the parent directory. Follow the guidelines in the lab's root directory README.
1. With your partner, edit the source files in VS Code: `blackjack.cc` and  `blackjack_functions.cc`. Replace all the TODO comments with working code.
1. Compile your program with the `$ make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `$ ./blackjack` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated unit tests with the `$ make unittest` command. Debug any runtime errors or logic errors using the same procedures.
1. Test your program against automated black box tests with the `$ make test` command. Debug any errors.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `$ make format` shell command. Correct any errors.
1. Check for lint errors with the `$ make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

## Scoring

[Blackjack](https://en.wikipedia.org/wiki/Blackjack) is a casino card game. If you are new to Blackjack, read/watch one of the following to understand the rules:
- [Blackjack (Hoyle)](../Hoyle_blackjack_compressed.pdf)
- [How to Play Blackjack (YouTube)](https://youtu.be/eyoh-Ku9TCI)

As explained in the resources above, the game involves a dealer, who is usually a casino employee, and one or more players. Players take turns. On a player's turn, they may "**hit**", meaning draw one card; or "**stand**", meaning to end their turn without taking any cards. (There are additional options that we are omitting for now.)

The objective of the game is to attain the highest score possible, without going over 21. A total score greater than 21 is called a "**bust**" and is an automatic loss.

Each card contributes to a player's score as follows:

| Card Type | Score |
|-----------|-------|
| Number card (2 through 10) | the value of the number |
| Face card (jack, queen, or king) | 10 |
| Ace | 1, plus possible bonus; see below |

**Ace bonus**: If a player's hand includes an ace, they may count that ace as 11 points instead of 1. To avoid a bust, this bonus only applies when it increases the score to 21 or less.

Only one ace bonus will ever apply. Two aces with the bonus would count for 22 points, surely a bust. So if the ace bonus is used, it is only used once.

When a player's first two cards total 21 exactly, this is called a "**blackjack**".  A blackjack is a combination of one ace, with one 10 or face card. A blackjack is an automatic win (or tie with other blackjacks).

Here are some scoring examples:

| Cards | Score |
|-------|-------|
| 9, 5 | 14 |
| 3, jack | 13 |
| queen, king | 20 |
| ace, 9 | 20 (uses ace bonus) |
| jack, ace | 21 (uses ace bonus, blackjack) |
| ace, ace | 12 (uses ace bonus once) |

The input to your program is the name of two cards, given as command line arguments. Your program should recognize the following names for cards:

| Card | Name as Input | Score |
|-------|------|-------|
| 2 | 2 | 2 |
| 3 | 3 | 3 |
| 4 | 4 | 4 |
| 5 | 5 | 5 |
| 6 | 6 | 6 |
| 7 | 7 | 7 |
| 8 | 8 | 8 |
| 9 | 9 | 9 |
| 10 | 10 | 10 |
| jack | J | 10 |
| queen | Q | 10 |
| king | K | 10 |
| ace | A | 1 or 11 |

Observe that each card name is either a **whole number** or a **capital letter**.

Your program should compute the score of the two given cards, and print that number to standard output on its own line.

## Input Validation

Your program should validate the command line arguments. That means checking that the number of arguments is correct; and that each argument contains a valid card name.

The user should provide exactly two arguments after the command name.

If the number of arguments is wrong, your program should print the error message
```
error: you must supply two arguments
```
and return a non-zero exit code.

If either of the arguments is not a valid card name, your program should print the error message
```
error: invalid card name
```
and return a non-zero exit code.

Your program must not suffer a runtime error in these situations.

## Functions

Just like the previous part, the starter code has several functions that you need to complete.

### `IsAce`

```C++
// Determine whether card_name is the name of an ace ("A").
// Returns true if card_name represents an ace, or false otherwise.
bool IsAce(const std::string& card_name)
```

### `IsFaceCard`

```C++
// Determine whether card_name is the name of a face card ("J", "Q", or "K").
// Returns true if card_name represents a face card, or false otherwise.
bool IsFaceCard(const std::string& card_name)
```

### `IsNumberCard`

```C++
// Determine whether card_name is the name of a number card ("2", "3",
// through "10").
// Returns true if card_name represents a number card, or false otherwise.
bool IsNumberCard(const std::string& card_name)
```

### `IsCardName`

```C++
// Determine whether str is a valid card name.
// Returns true if str is an ace, face card, or number card; or false
// otherwise.
bool IsCardName(const std::string& str)
```

### `CardPoints`

```C++
// Calculate the score for one card.
// An ace is worth 1 point; a face card is worth 10 points; and a number card
// is worth its value (so for example, "4" is worth 4 points).
// This function assumes that card_name is a valid card name.
// Returns the number of points for the card.
int CardPoints(const std::string& card_name)
```

### `IsBust`

```C++
// Determine whether a blackjack hand score is a bust.
// A score is a bust when it is greater than 21.
// Returns true if score is a bust, or false otherwise.
bool IsBust(int score)
```

### `TwoCardHandScore`

```C++
// Calculate the score for a hand of two cards.
// A hand scores points for each card. In addition, if the hand contains an
// ace, the "ace bonus" increases the score by 10, unless that would cause
// the score to bust.
// This function assumes that card_1 and card_2 are valid card names.
// Returns the score for a hand containing card_1 and card_2.
int TwoCardHandScore(const std::string& card_1, const std::string& card_2);
```

### `main`

As usual, you need to complete the program's `main` function.

This program's `main` needs to
1. validate the number of arguments (must be two)
1. validate the contents of the arguments (must all be valid card names)
1. calculate the total score of the blackjack hand
1. print the score to standard output

## Example Input and Output

```
$ ./blackjack 3 4 5
error: you must supply two arguments
```

```
$ ./blackjack 3
error: you must supply two arguments
```

```
$ ./blackjack
error: you must supply two arguments
```

```
$ ./blackjack 3 apple
error: unknown card
```

```
$ ./blackjack 9 5
14
```

```
$ ./blackjack 3 J
13
```

```
$ ./blackjack Q K
20
```

```
$ ./blackjack A 9
20
```

```
$ ./blackjack A A
12
```

## Test Cases

As usual, test your program against the test suite below.

| Test Case | Input                              | Expected Output                          |
|-----------|------------------------------------|------------------------------------------|
| 1         | (no arguments)      | `error: you must supply two arguments` |
| 2         | A               | `error: you must supply two arguments` |
| 3         | A A A              | `error: you must supply two arguments` |
| 4         | X A             | `error: unknown card` |
| 5         | A X               | `error: unknown card` |
| 6         | X X               | `error: unknown card` |
| 7         | 2 3               | `5` |
| 8         | 5 Q             | `15` |
| 9         | K J            | `20` |
| 10        | A 10            | `21` |
| 11        | 5 A           | `16` |
| 12        | A A           | `12` |


## Next Steps

After you have pushed your code, you are done with this lab. You may ask your TA for permission to sign out and leave.
