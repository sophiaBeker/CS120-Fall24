# Guessing A Secret Number In A File

## What to Do

1. Read the entire README with your partner before doing anything else.
1. If you haven't already, write `AUTHORS.md` in the parent directory. Follow the guidelines in the lab's root directory README.
1. With your partner, edit the `secret.cc` and `game.cc` source files using VS Code. Add the required header. Replace all the TODO comments with working code.
1. Compile your program with the `$ make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your programs with the `$ ./secret` and `$ ./game` shell commands.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated test with the `$ make test` command. Debug any runtime errors or logic errors using the same procedures.
1. Check your `AUTHORS.md` with the `$ make authors` shell command. Correct any errors.
1. Check for format errors with the `$ make format` shell command. Correct any errors.
1. Check for lint errors with the `$ make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

## Introduction

We have created a few variations on a game about guessing a secret number.
So far the "secret" has been obvious, because it has been part of the program
input and visible to the player.
In this exercise, we will use file I/O to make the secret number hidden from the player.
This makes for a more engaging and realistic game.

This exercise involves **two programs:**
1. `secret` is run by player 1 to choose a secret number and write that number to a file named `secret.dat`.
2. `game` is run by player 2 to actually play the guessing game. The secret number is input from `secret.dat`, so player 2 never sees the secret number.

## secret

The first of two programs is called `secret`, and its source code is in `secret.cc`.

Player 1 runs the program and gives a secret number, one through ten, as a command line argument.
`secret` validates its input and then writes the secret number into a file named `secret.dat`.
Like other Unix programs, when an error arises, `secret` prints a command error;
but when `secret` succeeds, it does not print any output at all.

In detail, `secret` should:
1. Initialize a vector with the command line arguments (this is provided).
1. Validate that there is one command line argument. If not, print the error message
   `"error: you must provide a secret number\n"`
   and return a non-zero exit code.
1. Declare an `int` variable to store the secret number. Initialize the variable
   with the command line argument. *Hint:* You can convert the argument `std::string`
   to an `int` with the `std::stoi` function.
1. Validate that the secret number is between one and ten. If it is not,
   print the error message
   `"error: secret number must be between 1 and 10\n"`
   and return a non-zero exit code.
1. Open `secret.dat` as an output file. *Hint:* You can do this by declaring
   and initializing a variable with the `std::ofstream` data type.
1. Insert the secret number into the file. *Hint:* You can do this with the
   stream insertion operator `<<`.
1. Return exit code zero (this is provided).

## game

The second of the two programs is `game`, and its source code is in `game.cc`.

Player 2 runs this program after player 1 ran `secret`. `game` reads the secret number from `secret.dat`.
This way, player 2 doesn't see the secret number, and it is a true surprise.
If `secret.dat` is missing or malformed, `game` prints a command error.
The player gets just one chance to guess the secret, and then learns whether they
win or lose.

(The focus of this exercise is on reading and writing files, so we are keeping the gameplay simple.)

In detail, `game` should:
1. Open `secret.dat` as an input file. *Hint:* You can do this by declaring
   and initializing a variable with the `std::ifstream` data type.
1. If the open operation suffered an I/O error, that means that `secret.dat`
   does not exist. Print the error message
   `"error: cannot read secret.dat\n"`
   and return a non-zero exit code.
   *Hint:* You can determine whether the previous I/O operation succeeded by
   calling the `std::ifstream::good` member function; or by converting
   the `std::ifstream` object to `bool`.
1. Declare an `int` variable to store the secret number. Extract the secret number
   from the file into the variable.
   If that operation fails, print the error message
   `"error: secret.dat malformed\n"`
   and return a non-zero exit code.
1. Validate that the secret number is between one and ten. If it is not,
   print the same error message as the previous step
   (`"error: secret.dat malformed\n"`)
   and return a non-zero exit code.
1. Declare an `int` variable to hold the player's guess.
   Prompt the player with the output
   `"Enter your guess: "`
   and read a guess from standard input into the guess variable.
1. If the guess matches the secret, print output
   `"Correct, you win!\n"`.
   Otherwise (they don't match),
   print the output
   `"Incorrect, the secret number was *SECRET*, you lose.\n"`.
   For example,
   `"Incorrect, the secret number was 5, you lose.\n"`
1. Return exit code zero (this is provided).

## Manipulating `secret.dat`

`secret` writes to a file named `secret.dat`. In order to test and debug `secret`, you will need to view the contents of `secret.dat`. Likewise, `game` reads from `secret.dat`, so testing and debugging `secret` will involve modifying `secret.dat`.

Your `secret.dat` will be a text file that stores an integer. You can view and edit this file in VS Code just like any other text file. As usual, you need to Save after making changes in VS Code.

You can also use the `cat` shell command to print out the contents of a file. For example, if `secret.dat` contains
```
7
```
then the output of the `cat` command looks like:
```
$ cat secret.dat
7
```

## Example Input and Output

### secret

Missing command line argument:
```
$ ./secret
error: you must provide a secret number
```

Too many command line arguments:
```
$ ./secret 5 6
error: you must provide a secret number
```

Secret number too large:
```
./secret 11
error: secret number must be between 1 and 10
```

Secret number too small:
```
./secret 0
error: secret number must be between 1 and 10
```

Works properly:
```
./secret 7
```
After running this command, `secret.dat` contains
```
7
```

### game

Error: `secret.dat` does not exist:
```
$ ./game
error: cannot read secret.dat
```

Error: `secret.dat` contains `cheese`:
```
$ ./game
error: secret.dat malformed
```

Error: `secret.dat` is empty:
```
$ ./game
error: secret.dat malformed
```

Error: `secret.dat` contains `100`, which is out of range:
```
$ ./game
error: secret.dat malformed
```

Win for secret number 7:
```
$ ./secret 7
$ ./game
Enter your guess: 7
Correct, you win!
```

Lose for secret number 5:
```
$ ./secret 5
$ ./game
Enter your guess: 1
Incorrect, the secret number was 5, you lose.
```

## Test Cases

| Test Case | **secret** Command Line Arguments                              | Expected Output              |
|-----------|------------------------------------|------------------------------|
| 1         | (none)                 | `error: you must provide a secret number`                |
| 2         | 1 2     | `error: you must provide a secret number`       |
| 3         | 15      | `error: secret number must be between 1 and 10` |
| 4         | 0      | `error: secret number must be between 1 and 10` |
| 5         | -1      | `error: secret number must be between 1 and 10` |
| 6         | 5       | no standard output; `secret.dat` contains `5` |
| 7         | 1       | no standard output; `secret.dat` contains `1` |
| 8         | 10       | no standard output; `secret.dat` contains `10` |

| Test Case | `secret.dat` | **game** Input | Expected Output              |
|-----------|------------|----------------|------------------------------|
| 9         | `3`        | 3              | `Correct, you win!`  |
| 10        | `9`        | 9              | `Correct, you win!`  |
| 11        | `9`        | 8              | `Incorrect, the secret number was 9, you lose.` |
| 12        | `1`        | 5              | `Incorrect, the secret number was 1, you lose.` |
| 13        | `10`       | 5              | `Incorrect, the secret number was 10, you lose.` |
| 14         | does not exist | (none) | `error: cannot read secret.dat` |
| 15         | `bread` | (none) | `error: secret.dat malformed` |
| 16         | empty | (none) | `error: secret.dat malformed` |
| 17         | `15` | (none) | `error: secret.dat malformed` |

## Next Steps

After you have pushed your code, you are done with this lab. You may ask your TA for permission to sign out and leave.

