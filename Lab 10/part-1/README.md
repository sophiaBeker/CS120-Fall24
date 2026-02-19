# California Counties

In this exercise, you will write a program that will create a two dimensional data structure from `std::vector` to organize California's population data by county. Your program will be able to search through the vector and report the population of a given county along with what percentage of the state's population lives in that county.

## What to Do

1. With your partner, edit the `counties_functions.cc` source file using VS Code. Add the required header. Replace all the TODO comments with working code.
1. Compile your program with the `$ make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `$ ./counties` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated test with the `$ make test` command. Debug any runtime errors or logic errors using the same procedures.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `$ make format` shell command. Correct any errors.
1. Check for lint errors with the `$ make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

## Introduction

[California](https://en.wikipedia.org/wiki/California) is the most populous and the third largest by area of the fifty states in the [United States of America](https://en.wikipedia.org/wiki/United_States). California is made up of [58 counties](https://en.wikipedia.org/wiki/List_of_counties_in_California) which range in population from 1,235 people in Alpine County to 9,829,544 people in Los Angeles County.

We can create a two dimensional data structure from `std::vector` to organize California's population data by county. We can first observe that each county has a name which we can define as a `std::string`. Trivially, we can define a C++ `std::vector` to store all the names.

```c++
std::vector<std::string> ca_counties{"Alameda", "Alpine", ..., "Yolo", "Yuba"};
```

Population data is numerical so we would want to store that information as integers. Similar to storing all the county names, we can trivially create a vector to store all the population data.

```c++
std::vector<int> ca_counties_population{1648556, 1235, ..., 216986, 83421};
```

Instead of creating two different vectors, we could organize the same information into one two dimensional or 2D `std::vector` such that the data is organized like a table. The first row contains the names of the counties and the second row has the corresponding population. We can imagine that this would look like a spread sheet like Google Sheet or Microsoft Excel.

There's one small problem. We cannot mix types in 2D `std::vector` containers. We have to use the same type in each vector. This means that if we wanted to create a table we would have to use only integers or only strings. The best choice here is strings because we can always convert the strings to integers using `std::stoi()`.

We can declare the 2D `std::vector` for our table of California counties like so:
```c++
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

```

This project is defined in 4 files:
* `counties.cc`
* `counties_functions.cc`
* `counties_functions.h`
* `counties_unittest.cc`

In `counties.cc`, our main function for our program is defined. In this file, the command line arguments are processed.

The file `counties_functions.h` defines two functions which will be used in the main function of the program.

The first function is:
```c++
std::string AllCountiesString(const std::vector<std::vector<std::string>>& ca_counties)
```
`AllCountiesString` returns a single string which has all the names of the counties separated by a space in between each name. (It is OK to have a trailing space.)

```c++
int CountyPopulation(const std::vector<std::vector<std::string>>& counties,
                     const std::string& match_county);
```

`CountyPopulation` searches through the array `ca_counties` and returns the population of the match_county if match_county was found in counties. If match_county was not found then the function returns -1.

```c++
int StatePopulation(const std::vector<std::vector<std::string>>& counties);
```

`StatePopulation` sums all the counties populations and returns the state's total population.


This project demonstrates [modular programming](https://en.wikipedia.org/wiki/Modular_programming) where different elements of our program are defined in different files. Imagine trying to write a large program like a web browser, word processor, or operating system in just a single file. The amount of code in the file would make it difficult to navigate and chnange. For this and many other reasons, programmers like to break their programs down into multiple files. In our project, we have one file which has our main program `rectangle_area.cc` and another file which contains the functions used in our main program `rectangle_area_functions.cc`.

The file `counties_functions.h` is called a [header file](https://google.github.io/styleguide/cppguide.html#Header_Files). Notice that it is almost the same name as `counties_functions.cc` except that the file extension `.cc` has been changed to `.h`. This tells the programmer that it is the header file for the C++ source file named `counties_functions.cc`. The header file is used to help the programmer and compiler know what is available for use in a given `.cc` file.

Another benefit of modular programming is that we can break our program down into independent pieces which can be tested independently. As our programs increase in complexity, we will be writing more units of code that we need to make sure function correctly. One way to do this is to follow the practice of [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development). 

Test-driven development is where the tests are written first and then we develop the software to pass the tests. The motivation is that if the person who wrote the specification (your instructor) understands what they want, then tests can be written to document how the code is going to be used. Then the developer (you, the student) can develop your software and know that it is correct(-ish) if it passes the tests.

We can never really know if the code is correct because the tests could be flawed or wrong. Regardless, test-driven development is an effective way to communicate how we would like our programs to behave.

In this exercise, [unit tests](https://en.wikipedia.org/wiki/Unit_testing) have been included which test the functions you write. To run the unit tests, use the command `make unittest`.

If any of the tests fail, use the output to go back and revise your code and re-run the unit tests. Once you have all your tests passing, then you likely have all the parts working correctly.

Remember, verifying a unit (a part) does not mean that the entire program (the system that uses the parts) is working correctly. That part is still up to the developer to verify through rigorous testing. As a starting point, you can use the instructor's partial tests with `make test`.

## Requirements

Write a program that takes one string as a command line argument which represent name of a California county.

Using the name of the county, search through the predefined 2D vector to find the population and print a message to the terminal summarizing the information.

You shall use [cout](https://en.cppreference.com/w/cpp/io/cout) to print messages to the terminal.

_Do not use_ [cin](https://en.cppreference.com/w/cpp/io/cin) to read in values from the keyboard. This program is not interactive and an interactive program will be marked with a zero score.

The program reads in one value from the command line (`argv`), stores them in a vector named `args`. Use the examples provided to process command line arguments.

Make certain that the error messages your program generates matches the examples given below in Example Output section.

The starting code defines a series of `TODO` comments which you can use to formulate your plan and develop your program.

Write your program progressively. Compile your program often and check that you're making progress. Make sure your program behaves the way you expect. Start with the functions and use the unit tests to verify they work correctly. Then move on to writing the main function once all you functions pass their unit tests.

The output of your program must match the output given in the section Example Output below.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.

## Testing Your Code

Computers only ever do exactly what they are told, exactly the way they are told it, and never anything else. Testing is an important process to writing a program. You need to test for the program to behave correctly and test that the program behaves incorrectly in a predictable way.

As programmers we have to remember that there are a lot of ways that we can write the wrong program and only one to a few ways to write the correct program. We have to be aware of [cognitive biases](https://en.wikipedia.org/wiki/List_of_cognitive_biases) that we may exercise that lead us to believe we have correctly completed our program. That belief may be incorrect and our software may have errors. [Errors in software](https://www.wired.com/2005/11/historys-worst-software-bugs/) may lead to loss of [life](https://www.nytimes.com/2019/03/14/business/boeing-737-software-update.html), [property](https://en.wikipedia.org/wiki/Mariner_1), [reputation](https://en.wikipedia.org/wiki/Pentium_FDIV_bug), or [all of the above](https://en.wikipedia.org/wiki/2009%E2%80%9311_Toyota_vehicle_recalls).

### Test strategy

Start simple, and work your way up. Good tests are specific, cover a broad range of fundamentally different possibilities, can identify issues quickly, easily, and directly, without need for much set up, and can almost be diagnosed by inspection if the code fails to execute the test correctly.

## Example Output

Please ensure your program's output is identical to the example below.

```
$ make unittest
set -e; clang++ -MM -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 counties_functions.cc \
| sed 's/\(counties_functions\)\.o[ :]*/\1.o counties_functions.d : /g' > counties_functions.d; \
[ -s counties_functions.d ] || rm -f counties_functions.d
set -e; clang++ -MM -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 counties.cc \
| sed 's/\(counties\)\.o[ :]*/\1.o counties.d : /g' > counties.d; \
[ -s counties.d ] || rm -f counties.d
rm: cannot remove 'unittest': No such file or directory
rm: cannot remove 'test_detail.json': No such file or directory
make: [Makefile:142: cleanunittest] Error 1 (ignored)
clang++ -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 -c counties_functions.cc
Running main() from /build/googletest-j5yxiC/googletest-1.10.0/googletest/src/gtest_main.cc
[==========] Running 3 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from AllCountiesString
[ RUN      ] AllCountiesString.String
[       OK ] AllCountiesString.String (0 ms)
[----------] 1 test from AllCountiesString (0 ms total)

[----------] 2 tests from CountyIndex
[ RUN      ] CountyIndex.Found
[       OK ] CountyIndex.Found (1 ms)
[ RUN      ] CountyIndex.NotFound
[       OK ] CountyIndex.NotFound (0 ms)
[----------] 2 tests from CountyIndex (1 ms total)

[----------] Global test environment tear-down
[==========] 3 tests from 2 test suites ran. (1 ms total)
[  PASSED  ] 3 tests.
$ make 
clang++ -g -O3 -Wall -pipe -std=c++17 -D LINUX -D AMD64 -c counties.cc
clang++ -g -O3 -Wall -pipe -std=c++17 -o counties counties.o counties_functions.o 
$ ./counties 
Please specify a county name on the command line. Exiting.
For example: ./counties "Los Angeles"
The counties in California are: Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama Trinity Tulare Tuolumne Ventura Yolo Yuba 
$ ./counties Oregon
Error: Oregon is not in the vector. Please check your spelling.
The counties in California are: Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama Trinity Tulare Tuolumne Ventura Yolo Yuba 
$ ./counties "San Mateo"
The population of San Mateo County is 737888. That represents 1.88% of the entire state's population.
$ ./counties Orange
The population of Orange County is 3167809. That represents 8.07% of the entire state's population.
$ ./counties "Los angeles"
Error: Los angeles is not in the vector. Please check your spelling.
The counties in California are: Alameda Alpine Amador Butte Calaveras Colusa Contra Costa Del Norte El Dorado Fresno Glenn Humboldt Imperial Inyo Kern Kings Lake Lassen Los Angeles Madera Marin Mariposa Mendocino Merced Modoc Mono Monterey Napa Nevada Orange Placer Plumas Riverside Sacramento San Benito San Bernardino San Diego San Francisco San Joaquin San Luis Obispo San Mateo Santa Barbara Santa Clara Santa Cruz Shasta Sierra Siskiyou Solano Sonoma Stanislaus Sutter Tehama Trinity Tulare Tuolumne Ventura Yolo Yuba 
$ ./counties "Los Angeles"
The population of Los Angeles County is 9829544. That represents 25.05% of the entire state's population.
```

## Next Steps

After you have pushed your code, you are done with this lab. 