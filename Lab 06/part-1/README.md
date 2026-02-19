
# Command Line Mad Lib

## What to Do

1. Read the entire README with your partner before doing anything else.
1. If you haven't already, write `AUTHORS.md` in the parent directory. Follow the guidelines in the lab's root directory README.
1. With your partner, edit the `sandwich.cc` source file using VS Code. Replace all the TODO comments with working code.
1. Compile your program with the `make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `./sandwich` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated test with the `make test` command. Debug any runtime errors or logic errors using the same procedures.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `make format` shell command. Correct any errors.
1. Check for lint errors with the `make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

## Introduction

[Mad Libs](https://en.wikipedia.org/wiki/Mad_Libs) are a word game that involves a sentence with blanks. Players fill in the blanks in amusing ways. In this part, you will write a program that fills in the blanks for a sentence about a sandwich order:

"A *PROTEIN* sandwich on *BREAD* with *CONDIMENT*."

The italics *PROTEIN*, *BREAD*, and *CONDIMENT* are fill-in-the blanks. For example, if you fill in *PROTEIN*=tuna, *BREAD*=wheat, and *CONDIMENT*=lettuce, the sentence becomes:

"A tuna sandwich on wheat with lettuce."

As you know, computer programs are very good at following patterns. The `sandwich` program will follow a pattern to read the components of a sandwich from command-line arguments, and write out a sentence describing an order for that sandwich as output. A program like this could be a part of a cash register software or ordering app.

In the prompt code, `main` begins with
```c++
int main(int argc, char* argv[]) {
  std::vector<std::string> command_line{argv, argv + argc};
```
The first statement declares and initializes `command_line`. `command_line` is a `std::vector` container object, and each element is a `std::string` containing one part of the shell command that ran your program.

For example, if you run the `sandwich` program with the shell command
```bash
$ ./sandwich spam white mustard
```
then `command_line` contains:

| element | `"./sandwich"` | `"spam"` | `"white"` | `"mustard"` |
| -- | -- | -- | -- | -- |
| **index**   | 0              | 1        | 2         | 3           |

Remember that **the command name is included at index 0**. This is counter-intuitive because the command name `"./sandwich"` is not really part of the input to the `sandwich` program. But, this is simply how Unix command lines work, and is something your program needs to work around. This is an exercise in [data cleaning](https://en.wikipedia.org/wiki/Data_cleansing). Your program needs to make use of the `command_line` vector, even though `command_line` contains an element that your program does not need.

## Input Validation

Your program should validate that the number of command line arguments is correct. In other words, `command_line.size()` will return the number of elements in the command line. The number of arguments in the command line must be three. The user should provide exactly three arguments after the command name.

If the number of arguments is wrong, your program should print the error message
```
error: you must supply three arguments
```
and return a non-zero exit code.

The error message should appear when the user gives too few arguments like this:
```
$ ./sandwich turkey wheat
error: you must supply three arguments
```
The error message should also appear when the user gives too many arguments:
```
$ ./sandwich chicken multigrain pickles peppers
error: you must supply three arguments
```

Your program must not suffer a runtime error in these situations.

## Example Input and Output

```
$ ./sandwich spam white mustard
Your order:
A spam sandwich on white with mustard.
```

```
$ ./sandwich caprese ciabbata oil
Your order:
A caprese sandwich on ciabbata with oil.
```

```
$ ./sandwich bologna
error: you must supply three arguments
```

```
$ ./sandwich chicken multigrain pickles peppers
error: you must supply three arguments
```

## Test Cases

As usual, test your program against the test suite below.

| Test Case | Input                              | Expected Output                          |
|-----------|------------------------------------|------------------------------------------|
| 1         | ham               | `error: you must supply three arguments` |
| 2         | ham rye                  | `error: you must supply three arguments`    |
| 3         | ham rye tomato lettuce                  | `error: you must supply three arguments`    |
| 4         | ham rye mayo                  | `Your order:` <br> `A ham sandwich on rye with mayo.` |
| 5         | tuna wheat mustard                  | `Your order:` <br> `A tuna sandwich on wheat with mustard.` |
| 6         | "roast beef" "kaiser roll" "horse radish and mayo"                  | `Your order:` <br> `A roast beef sandwich on kaiser roll with horse radish and mayo.` |
| 7         | salami white mustard                  | `Your order:` <br> `A salami sandwich on white with mustard.` |


## Next Steps

After you have pushed your code, move on to part 2.
