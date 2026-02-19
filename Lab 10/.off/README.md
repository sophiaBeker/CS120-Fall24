# US States

This uses a file to store population and land area information for US states. Again, we're storing everything in a 2D std::vector which means that all our data is stored as the same type. This means that we're storing the population and the land area of each state as a std::string.

Code is provided which loads the data from a file into a `std::vector<std::vector<std::string>>`. Your role is to write the code which will calculate the state with the densest and the sparsest population density.

Population density is defined as the ration of how many people over how much area. For example, California has 37,253,956 people and a land area of 155779.22 square miles. The population density is approximately 239.15 people per square mile or $\frac{37253956}{155779.22}$.

## What to Do

1. With your partner, edit the `states.cc` and `states_functions.cc` source files using VS Code. Add the required header. Replace all the TODO comments with working code.
1. Compile your program with the `$ make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `$ ./states` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated test with the `$ make test` command. Debug any runtime errors or logic errors using the same procedures.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `$ make format` shell command. Correct any errors.
1. Check for lint errors with the `$ make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

As [explained in learncpp.com section 2.11](https://www.learncpp.com/cpp-tutorial/header-files/),
source modules should be divided into two linked files, a `.h` *header file* and `.cc` *source file.* This lab is following this practice.

This project is defined in 4 files:
* `states.cc`
* `states_functions.h`
* `states_functions.cc`

The program is intended to:
1. Read from the [State Demographics CSV File](https://corgis-edu.github.io/corgis/csv/state_demographics/).
1. Create a `std::vector` of `std::vector<std::string>` objects.
1. Loop through the `State`s to find the state with the highest, and lowest, population density. A state's population density is the population divided by the land area.
1. Print out the name and density of the states with the highest and lowest density.

## Example Input and Output

```
$ ./states
The densest state is New Jersey (1195.49)
The sparsest state is Alaska (1.24462)
```


## Test Cases

This program does not have manual test cases. Instead, test your function definitions with `$ make unittest` and test your entire program behavior with `$ make test`.


## Next Steps

After you have pushed your code, you are done with this lab. You may ask your TA for permission to sign out and leave.
