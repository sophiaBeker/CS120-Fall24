
# What to Do

1. Read the entire README with your partner before doing anything else.
1. If you haven't already, write `AUTHORS.md` in the parent directory. Follow the guidelines in the lab's root directory README.
1. With your partner, edit the `bmr.cc` source file using VS Code. Replace all the TODO comments with working code. Remember, make small changes and compile often.
1. Your program must use the `BMRMan` and `BMRWoman` functions. Do not change the prototype of these functions (name, return type, argument types).
1. Compile your program with the `make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `./bmr` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `make format` shell command. Correct any errors.
1. Check for lint errors with the `make lint` shell command. Correct any errors.
1. Test your program against automated tests with the `make test` command. Debug any runtime errors or logic errors using the same procedures.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

# Basal Metabolic Rate (BMR)

A person's [basal metabolic rate (BMR)](https://en.wikipedia.org/wiki/Basal_metabolic_rate) is the amount of energy that
their body expends while at rest. BMR is usually measured as the number of calories expended per day. This information
is useful when someone is trying to avoid malnutrition, gain weight, or lose weight. It is relevant when people are bodybuilding, pregnant, or dieting.

The [Mifflin St Jeor equation](https://www.thecalculatorsite.com/articles/health/bmr-formula.php) is a math equation that estimates
a person's BMR based upon their weight, height, and age. There are two similar equations, one for men, and another for women.

The equation for men is:
$\text{BMR} = (4.536 \times \text{weight in pounds}) + (15.88 \times \text{height in inches}) - (5 \times \text{age in years}) + 5.$

The equation for women is:
$\text{BMR} = (4.536 \times \text{weight in pounds}) + (15.88 \times \text{height in inches}) - (5 \times \text{age in years}) - 161.$

Sustaining a body requires energy, so increases in weight or height correspond to increases in BMR. Peoples' metabolisms
tend to slow down as they age, so increases in age correspond to decreases in BMR.

The BMR of some athletes whose weight, height, and age are public information, are below.
(These figures are accurate as of this writing in 2024.)

| Person | Weight (pounds) | Height (feet and inches) | Height (inches) | Age (years) | Identity | BMR (calories/day) |
|--------|-----------------|--------------------------|-----------------|-------------|----------|--------------------|
| [Dwayne "The Rock" Johnson](https://en.wikipedia.org/wiki/Dwayne_Johnson) | 260 | 6'4" | 76 | 51 | Man | 2136.24 |
| [Simone Biles](https://simonebiles.com/) | 104 | 4'8" | 56 | 26 | Woman | 1070.02 |
| [Kobe Bryant](https://en.wikipedia.org/wiki/Kobe_Bryant) | 212 | 6'6" | 78 | 41 | Man | 2000.27 |

## Requirements

Your program should prompt the user for weight; prompt for height; prompt for age; use a function to calculate BMR for 
a man using those figures; calculate BMR for a woman using those figures; and print both BMRs to standard output.

You shall use [std::cout](https://en.cppreference.com/w/cpp/io/cout) to print messages to the terminal and you shall use [std::cin](https://en.cppreference.com/w/cpp/io/cin) to read in values from the keyboard.

The starting code defines a series of `TODO` comments which you can use to formulate your plan and develop your program.

Write your program progressively. Compile your program often and check that you're making progress. Make sure your program behaves the way you expect.

The output of your program must match the output given in the section _Example Input and Output_ below.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

The Makefile has the following targets:

* all: builds the project
* clean: removes object and dependency files
* spotless: removes everything the clean target removes and all binaries
* format: outputs a [`diff`](https://en.wikipedia.org/wiki/Diff) showing where your formatting differes from the [Google C++ style guide](https://google.github.io/styleguide/cppguide.html)
* lint: output of the [linter](https://en.wikipedia.org/wiki/Lint_(software)) to give you tips on how to improve your code
* authors: check to make sure your AUTHORS.md file exists and is formatted properly
* test: run tests to help you verify your program is meeting the assignment's requirements. This does not grade your assignment.

## Functions

The main goal of this exercise is for you to practice writing a function definition. The starter code has two functions that you need to complete.

### BMRMan

```C++
// Given a person's weight (in pounds), height (in inches), and age (in
// years), calculate the BMR of that person using the Mifflin St Jeor
// equation for men.
double BMRMan(double weight, double height, int age)
```

### BMRWoman

```C++
// Given a person's weight (in pounds), height (in inches), and age (in
// years), calculate the BMR of that person using the Mifflin St Jeor
// equation for women.
double BMRWoman(double weight, double height, int age)
```

### main

As usual, you need to complete the program's `main` function.

## Example Input and Output

The input and output of your program should match the following.

```
$ make
set -e; clang++ -MM -g -O3 -Wall -pedantic -pipe -std=c++17 -D LINUX -nostdinc++ -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -D AMD64 bmr.cc 	| sed 's/\(bmr\)\.o[ :]*/.o bmr.d : /g' > bmr.d; 	[ -s bmr.d ] || rm -f bmr.d
clang++ -g -O3 -Wall -pedantic -pipe -std=c++17 -D LINUX -nostdinc++ -I/usr/include/c++/11 -I/usr/include/x86_64-linux-gnu/c++/11 -D AMD64 -c bmr.cc
clang++ -g -O3 -Wall -pedantic -pipe -std=c++17 -L /usr/lib/gcc/x86_64-linux-gnu/11 -o bmr bmr.o 
$ ./bmr
Enter weight in pounds: 260
Enter height in inches: 76
Enter age in years: 51
Man: 2136.24 calories per day
Woman: 1970.24 calories per day
$ 
```

## Test Cases

Test your program before moving on. For each of the test cases below,

1. Look at the test suite, and identify the first test case, its input, and expected output.
1. Run your program with `./bmr` .
1. Provide the program with the test case input.
1. If the program crashes, use the **debug runtime error** flowchart to debug the error.
1. Observe the program output and decide whether the actual output matches the expected output.
1. If the output **does not match**, declare that the program fails the test. Use the **debug logic error** flowchart to debug the error.
1. Otherwise (the output **does match**), repeat step 2 with the next test case.

If the program works correctly (meaning no runtime or logic errors) for every test case, declare that the program passes the test. You can move on to releasing your code for part 1.

| Test Case | Input             | Expected Output                                 |
|-----------|-------------------|-------------------------------------------------|
| 1         | 260, 76, 51         | `Man: 2136.24 calories per day`, `Woman: 1970.24 calories per day` |
| 2         | 104, 56, 26        | `Man: 1236.02 calories per day`, `Woman: 1070.02 calories per day` |
| 3         | 212, 78, 41        | `Man: 2000.27 calories per day`, `Woman: 1834.27 calories per day` |

## Next Steps

After you have pushed your code, move on to part 2.
