
# Strings

A _string_ in programming is a series of zero or more characters. A _string_ can be a letter, a number, a word, or a passage of text. A _string_ can be empty meaning that there are no letters or numbers in the string. A _string_ can also contain _whitespace_. The _whitespace_ in a string contains _non-printing characters_ such as spaces, tabs, new lines, etc. A _string_ can also contain punctuation and special characters.

In C++, we must `#include` the `string` header file to make use of the `std::string` type. This means that at the top of our source code we need to write `#include <string>` just like we write `#include <iostream>`.

To declare a string in C++, we need to prefix the `string` type with `std::` because strings are not part of the language. Strings are part of the [C++ standard library](https://en.cppreference.com/w/cpp/string).

In this exercise, we will write a short program that will prompt the computer user to enter some words and then use the words to create a paragraph of text similar to the comedy word game [Mad Libs](https://en.wikipedia.org/wiki/Mad_Libs).

C++ style and formatting is just as important in this lab as it was in the previous part so please review the information from the previous part regarding C++ style and formatting.

## Requirements

Review the C++ source files and identify all the TODOs.

To compile your program, you use the `clang++` command. If your program does not compile, it will receive a 0 score.

To verify that your formatting is conforming to the standards, you have a special tool named `check_formatting` for this assignment. You can use `check_formatting` to check the formatting of your project. Using the feedback from `check_formatting`, make changes to the source code. Continue editing your project until all warnings and errors have been addressed.

Formatting is graded according to the rubric.

## Prompting

When we talk about a program that asks the computer user for input, we typically refer to this as a _prompt_. Our BASH shell is a [command-line interface](https://en.wikipedia.org/wiki/Command-line_interface) which works by prompting the computer user to write commands and signal the end of a command by pressing the _enter_ or _return_ key. We can produce a similar command-line interface for our programs using `std::cout` to print the prompt to the terminal and `std::cin` to read the computer user's input from the keyboard. (Thankfully, the standard C++ library provides these features so we do not need to know how to ask the computer's operating system for this information.)

To print, we use `std::cout` and `<<` (the insertion operator). To say `"Hello World!\n"`, we wrote the following in C++.

```c++
    std::cout << "Hello World!\n";
```

To print a prompt, we will use `std::cout` and _not_ end the line with a `"\n"` (new line) character. This will keep the terminal's cursor on the same line so the computer user's answer appears on the same line. The computer user will press the _enter_ or _return_ key sending the cursor to the next line. Below is an example of printing a prompt; notice the use of the `": "` characters at the end of the line. 

```c++
    std::cout << "Please enter a plural gerund: ";
```

An incorrect prompt will have a `"\n"` at the end. The following is an _incorrect_ prompt; notice that this prompt uses the `"\n"` (new line) character instead of `": "`.

```c++
    std::cout << "Please enter a plural gerund\n";
```

Reading the computer user's input from the keyboard is achieved by using `std::cin` and `>>` (the extraction operator). We can use the extraction operator to read in a value from the keyboard to a variable. Remember that C++ is a strongly typed language so the variable must match the type you want the computer user to enter. In this exercise, we want to save the word the computer user is typing so we need to use a variable of type `std::string`. Here is an example where we save a word that is typed on the keyboard to a variable.

```c++
    std::string plural_gerund{"default value"};
    std::cout << "Please enter a plural gerund: ";
    std::cin >> plural_gerund;
    std::cout << "You entered: " << plural_gerund << "\n";
```

To the computer user, what they will see on the terminal when the program runs is the following:

```
Please enter a plural gerund: runnings
You entered: runnings
```

The prompting pattern always prints a message to the terminal first asking for the computer user to provide input and then reads the input storing it into an appropriately typed variable. 

## Line Wrapping

When using strings, it is very common for our lines of C++ code to become very long. One of the rules in the Google C++ Style guide tells us that [lines of text in our code should be no longer than 80 characters long](https://google.github.io/styleguide/cppguide.html#Line_Length). This means that we have to take long lines and [wrap the lines](https://en.wikipedia.org/wiki/Line_wrap_and_word_wrap).

For example, imagine that we have a line of code that looks like the following:

```c++
    std::cout << "People can " << present_tense_verb << " too but computers do it better.\n";
```

The space between `do` and `it` is at the 80th character position in that line starting from the left and counting the four spaces of indentation. This means we need to wrap the line so that this one statement uses more than one line.

Use your judgement on where you break up a line and wrap it. In the given example, a good place to wrap the line is at the insertion operators. Operators are a good place to break up a line. Applying this idea to the example, the wrapped line will look like the following example.

```c++
    std::cout << "People can "
              << present_tense_verb
              << " too but computers do it better.\n";
```

Notice how the operators are indented and aligned. This makes it easy to identify as belonging to the same statement and pleasant to look at.

## Compiling

Make sure your program is always compiling correctly. Compile early and compile often.

When you make a small change to a C++ source file, save your work, and compile the program. This will tell you immediately if you have made any mistakes.

_Do not write many, many lines of code and then compile._ This is a bad strategy. You will not catch small mistakes until there are many small mistakes. Correcting a small mistake hidden under many other small mistakes is more difficult than you can imagine.

The compiler we are using is `clang++`. To compile your program, use the following command:
```
$ clang++ madlib.cc
```

If the program compiles correctly, there will be nothing printed to the screen. Instead a new file will be created named `a.out`.

To run the program, use the following command:
```
$ ./a.out 
Please enter a singular noun: pizza
Please enter a plural noun: lemons
Please enter a present tense verb: fly

Computers are small enough to fit into a pizza.
Computers can add, multiply, divide, and fly.
People can fly too but computers do it better.
Computers have many lemons which gives them the advantage
over people for many computational tasks.
```

Another example:
```
$ ./a.out 
Please enter a singular noun: pencil
Please enter a plural noun: sweaters
Please enter a present tense verb: jump

Computers are small enough to fit into a pencil.
Computers can add, multiply, divide, and jump.
People can jump too but computers do it better.
Computers have many sweaters which gives them the advantage
over people for many computational tasks.
```

The program will execute, prompt the computer user for some words, and then print out a paragraph of text using the given words.

If your program does not compile, make sure you undo your changes. _If your program does not compile, then it will receive a 0 grade._


## Formatting

To verify that your formatting is conforming to the standards, you have a special tool named `check_formatting` for this assignment. You can use `check_formatting` to check the formatting of your project. Using the feedback from `check_formatting`, make changes to the source code. Continue editing your project until all warnings and errors have been addressed.

Below is an example of how to run `check_formatting` and the output shows that the project is well formatted (no changes are needed).

```
$ ./check_formatting 
2023-02-09 19:38:46,746 - INFO - Checking format for file: /home/mshafae/cpsc120/cpsc-120-lab-02-team-solo/part-1/madlib.cc
2023-02-09 19:38:47,702 - INFO - 😀 Formatting looks pretty good! 🥳
2023-02-09 19:38:47,702 - INFO - This is not an auto-grader.
2023-02-09 19:38:47,702 - INFO - Make sure you followed all the instructions and requirements.
```

## Don't Forget

Please remember that:

- You need to follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).
- Remove the word `TODO` in the comments once you have completed the task. You can leave the rest of the comment in place.

## Testing Your Code

Computers only ever do exactly what they are told, exactly the way they are told it, and never anything else. Testing is an important process to writing a program. You need to test for the program to behave correctly and test that the program behaves incorrectly in a predictable way.

As programmers we have to remember that there are a lot of ways that we can write the wrong program and only one to a few ways to write the correct program. We have to be aware of [cognitive biases](https://en.wikipedia.org/wiki/List_of_cognitive_biases) that we may exercise that lead us to believe we have correctly completed our program. That belief may be incorrect and our software may have errors. [Errors in software](https://www.wired.com/2005/11/historys-worst-software-bugs/) may lead to loss of [life](https://www.nytimes.com/2019/03/14/business/boeing-737-software-update.html), [property](https://en.wikipedia.org/wiki/Mariner_1), [reputation](https://en.wikipedia.org/wiki/Pentium_FDIV_bug), or [all of the above](https://en.wikipedia.org/wiki/2009%E2%80%9311_Toyota_vehicle_recalls).

### Test strategy

Start simple, and work your way up. Good tests are specific, cover a broad range of fundamentally different possibilities, can identify issues quickly, easily, and directly, without need for much set up, and can almost be diagnosed by inspection if the code fails to execute the test correctly.

## Example Output

Please ensure your program's output is identical to the example below.

```
$ clang++ madlib.cc 
$ ./a.out 
Please enter a singular noun: pizza
Please enter a plural noun: lemons
Please enter a present tense verb: fly

Computers are small enough to fit into a pizza.
Computers can add, multiply, divide, and fly.
People can fly too but computers do it better.
Computers have many lemons which gives them the advantage
over people for many computational tasks.
$ ./a.out 
Please enter a singular noun: pencil
Please enter a plural noun: sweaters
Please enter a present tense verb: jump

Computers are small enough to fit into a pencil.
Computers can add, multiply, divide, and jump.
People can jump too but computers do it better.
Computers have many sweaters which gives them the advantage
over people for many computational tasks.
```
