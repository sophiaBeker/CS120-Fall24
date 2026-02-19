
# Patterns With Loops

## What to Do

1. Read the entire README with your partner before doing anything else.
1. If you haven't already, write `AUTHORS.md` in the parent directory. Follow the guidelines in the lab's root directory README.
1. With your partner, edit the `pattern.cc` source file using VS Code. Replace all the TODO comments with working code.
1. Compile your program with the `$ make` shell command. Use the **debug compile error** procedure to debug any compile errors.
1. Run your program with the `$ ./pattern` shell command.
1. Test that your program passes all of the test cases in the test suite above. If your program suffers a runtime error, use the **debug runtime error** procedure to debug the error. If your program does not produce the expected output, use the **debug logic error** procedure to debug the error.
1. Test your program against automated test with the `$ make test` command. Debug any runtime errors or logic errors using the same procedures.
1. Check your `AUTHORS.md` with the `make authors` shell command. Correct any errors.
1. Check for format errors with the `$ make format` shell command. Correct any errors.
1. Check for lint errors with the `$ make lint` shell command. Correct any errors.
1. After your program passes all of these tests and checks, push your code to GitHub. Use the usual trio of commands: `git add`, `git commit`, and `git push`.

## Introduction

Perhaps you know how to knit or perhaps [you've watched someone knit](https://youtu.be/LBDJ_h-9WfE?t=58). Watching someone knit, you can see that there is a small number of operations yet the operations repeat over and over again. Repeat the operations in one fashion and you get a beautiful [cable knit](https://en.wikipedia.org/wiki/Cable_knitting) sweater. Repeat the operations in a different fashion and you'll have a sweater with a rib stitch pattern.

Many people enjoy knitting as a hobby. There are [knitting machines](https://en.wikipedia.org/wiki/Knitting_machine) to mass produce garments such as scarves, sweaters, gloves, and hats. Many of them are programmable using paper punch cards similar to how computers were programmed before magnetic storage became inexpensive and reliable.

In this exercise, we'll use the knowledge we gained about loops to fit together three loops to make a pattern. It isn't quite a pattern we can use for knitting yet you can imagine what you could do with a few loops. Feel free to experiment while developing this exercise however please make sure your final commit & push to your repository has the following pattern. The pattern below is annotated with text which should not appear in your programs output (see Example Output below).

```
*||||||||||||||||||||||  (line number: 0, dash count: 0, bar count: 22)
-*|||||||||||||||||||||  (line number: 1, dash count: 1, bar count: 21)
--*||||||||||||||||||||  (line number: 2, dash count: 2, bar count: 20)
---*|||||||||||||||||||  (line number: 3, dash count: 3, bar count: 19)
----*||||||||||||||||||  (line number: 4, dash count: 4, bar count: 18)
-----*|||||||||||||||||  (line number: 5, dash count: 5, bar count: 17)
------*||||||||||||||||  (line number: 6, dash count: 6, bar count: 16)
-------*|||||||||||||||  (line number: 7, dash count: 7, bar count: 15)
--------*||||||||||||||  (line number: 8, dash count: 8, bar count: 14)
---------*|||||||||||||  (line number: 9, dash count: 9, bar count: 13)
----------*||||||||||||  (line number: 10, dash count: 10, bar count: 12)
-----------*|||||||||||  (line number: 11, dash count: 11, bar count: 11)
------------*||||||||||  (line number: 12, dash count: 12, bar count: 10)
-------------*|||||||||  (line number: 13, dash count: 13, bar count: 9)
--------------*||||||||  (line number: 14, dash count: 14, bar count: 8)
---------------*|||||||  (line number: 15, dash count: 15, bar count: 7)
----------------*||||||  (line number: 16, dash count: 16, bar count: 6)
-----------------*|||||  (line number: 17, dash count: 17, bar count: 5)
------------------*||||  (line number: 18, dash count: 18, bar count: 4)
-------------------*|||  (line number: 19, dash count: 19, bar count: 3)
--------------------*||  (line number: 20, dash count: 20, bar count: 2)
---------------------*|  (line number: 21, dash count: 21, bar count: 1)
```

Notice that there are a total of 22 lines (lines 0 through 21). On each line there is always a sum of 22 bar (`|`) and dash (`-`) characters. For example, let's select line 16. There are 16 dashes and 6 bars which sums to 22. In addition to 22 bars and dashes, each line has one asterisk (`*`) which always appears between the dash and bar characters and a new line character (`\n`) at the end of each line. Thus there are always 24 characters per line.

Another relationship is that the count of dashes increases on each subsequent line by 1 while the bar count decreases by one on each subsequent line. For example, on line 8 there are 8 dashes and 14 bars and then on line 9 there are 9 dashes and 13 bars.

The way the program works is that there is one outer loop and two inner loops. The outer loop repeats once per line so that loop starts counting from 0 and stops when the line count reaches 21. Inside this loop, there is the loop for the dashes, which starts at the value of the line number and then counts down towards 0, stopping before it reaches 0. Then an asterisk is printed. Next another inner loop starts for the number of bars. This loop starts from the line number and counts up to the maximum number of characters in a line.

## Requirements

Write a program that recreates the pattern shown below in the Example Output section. There shall be precisely 22 lines. You must use loops to programmatically create the pattern. There must be at least one loop in your program. You may use any combination of for loops, while loops, and do-while loops.

You shall use [cout](https://en.cppreference.com/w/cpp/io/cout) to print messages to the terminal.

The starting code defines a series of `TODO` comments which you can use to formulate your plan and develop your program.

Write your program progressively. Compile your program often and check that you're making progress. Make sure your program behaves the way you expect.

The output of your program must match the output given in the section Example Output below.

To compile your program, you use the `make` command. A Makefile is provided for this exercise.


## Example Input and Output

Please ensure your program's output is identical to the example below.

```
$ make
set -e; clang++ -MM -g -O3 -Wall -pedantic -pipe -std=c++17 -D LINUX -D AMD64 pattern.cc \
| sed 's/\(pattern\)\.o[ :]*/\1.o pattern.d : /g' > pattern.d; \
[ -s pattern.d ] || rm -f pattern.d
clang++ -g -O3 -Wall -pedantic -pipe -std=c++17 -D LINUX -D AMD64 -c pattern.cc
clang++ -g -O3 -Wall -pedantic -pipe -std=c++17 -o pattern pattern.o 
$ ./pattern 
*||||||||||||||||||||||
-*|||||||||||||||||||||
--*||||||||||||||||||||
---*|||||||||||||||||||
----*||||||||||||||||||
-----*|||||||||||||||||
------*||||||||||||||||
-------*|||||||||||||||
--------*||||||||||||||
---------*|||||||||||||
----------*||||||||||||
-----------*|||||||||||
------------*||||||||||
-------------*|||||||||
--------------*||||||||
---------------*|||||||
----------------*||||||
-----------------*|||||
------------------*||||
-------------------*|||
--------------------*||
---------------------*|
```

## Next Steps

After you have pushed your code, you are done with this lab. You may ask your TA for permission to sign out and leave.

