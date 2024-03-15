# Introduction
Created by John Conway, the [Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) is a cellular automaton, simulating the world of cells.

The simulation is conducted on a board consisting of infinitely many rows and infinitely many columns. Rows and columns of the board are numbered with integers.

Each field on the board contains a cell in one of two states: *alive* or *dead*.

The collective state of all cells is called a *generation*.

We assume that a cell in row `w` and column `k` neighbors eight other cells on the board, with row numbers from `w - 1` to `w + 1` and column numbers from `k - 1` to `k + 1`.

The simulation begins with a certain initial generation, based on which we calculate the next generations.

In the next generation, a cell will be alive if and only if:
- in the current generation, it is alive and has exactly two or three live neighbors, or
- in the current generation, it is dead and has exactly three live neighbors.

# Task
Write a program that simulates the Game of Life.

The program reads the description of the initial generation from the input. Then, in a loop, it displays a portion of the board, then reads and executes a user command.

Commands control the calculation of subsequent generations. They also specify a portion of the board, further called a window, whose contents are displayed to the user.

The program is parameterized by two positive integers:
- `ROWS` is the number of rows in the window;
- `COLUMNS` is the number of columns in the window.

The values of these parameters are defined using symbolic constants, which can be defined using the `-D` option of the compiler.
Default values are provided in the program code:
- `ROWS` has a value of `22`;
- `COLUMNS` has a value of `80`.

The position of the window on the board is determined by the position of its top-left corner. If the top-left corner of the window is in row `w` and column `k`, then the window includes cells whose row numbers range from `w` to `w + ROWS - 1` and column numbers range from `k` to `k + COLUMNS - 1`.

Initially, the top-left corner of the window is in row number `1` and column number `1`.

# Data Format
The input of the program consists of the description of the initial generation and a sequence of commands.

The description of the generation indicates the live cells. It has the form of a sequence of lines starting with the character `'/'` (slash).

In the last line of the generation description, there is only the character `'/'`. In all other lines after the `'/'` character, there is an integer, which is the row number of the board. After that, there is an ordered, ascending non-empty sequence of integers, which are column numbers. Each of these numbers is preceded by a space.

A line of the form:

`/w k1 .. kn`

indicates that in row number `w` of the board, cells are alive in columns `k1`, .., `kn`.

In the generation description, the sequence of row numbers, i.e., numbers preceded by `'/'`, is sorted in ascending order.

After the description of the initial generation, there is a sequence of single-line commands.

The program recognizes commands:
- to end the work,

  It has the form of a line with the character `'.'` (period).
  
  It interrupts the loop reading commands and terminates the program.
  
- to calculate the `N`-th subsequent generation,

  It has the form of a line with a positive integer `N`.
  
  It calculates the N-th subsequent generation, starting from the current one. In particular, the command `1` calculates the next generation.
  
- to calculate the next generation,

  It has the form of an empty line. It is equivalent to the command `1`.
  
- to dump the state of the current generation,

  It has the form of a line with the number `0`.
  
  It generates a complete description of the current generation in the same format as it was loaded by the program description of the initial generation.
  
- to shift the window.

  It has the form of a line with two integers, `w` and `k`, separated by a space.
  
  It changes the coordinates of the top-left corner of the window, placing it in row `w` and column `k`.

# Result Format
Before reading each command, the program displays the contents of the window, starting from the top-left corner.

The contents of the window are presented with `ROWS` rows, each having a length of `COLUMNS`. After the last row, there is a line containing a sequence of `'='` (equals) characters of length `COLUMNS`.

The character in the window content line indicates the state of the cell. A live cell is represented by the character `'0'` (zero), and a dead cell is represented by the character `'.'` (period).

# Examples
The following examples are the result of running the program compiled with the command:

`gcc @options -DROWS=22 -DCOLUMNS=80 task3.c -o task3`

Included with the task are `.in` files with sample data and `.out` files with expected results.
- For the data in `example1.in`, the correct result is `example1.out`.
- For the data in `example2.in`, the correct result is `example2.out`.
- For the data in `example3.in`, the correct result is `example3.out`.

# Validation and Tests
- Solutions undergo validation, which initially checks compliance with the specification.
  
  Validation tests the program's operation against examples included with the task.
  
  Successfully passing validation is a prerequisite for the correctness tests. A program that fails validation receives a zero correctness score.
  
- Validation and tests are conducted on the students' computer.
- Programs are compiled with the command:
  
  `gcc @options ... name.c -o name`
  
  where the ellipsis (...) can be replaced with options -D defining constants ROWS and COLUMNS, name.c is the name of the source code file, and the options file contains:
  
  `-std=c17`
  
  `-pedantic`
  
  `-Wall`
  
  `-Wextra`
  
  `-Wformat-security`
  
  `-Wduplicated-cond`
  
  `-Wfloat-equal`
  
  `-Wshadow`
  
  `-Wconversion`
  
  `-Wjump-misses-init`
  
  `-Wlogical-not-parentheses`
  
  `-Wnull-dereference`
  
  `-Wvla`

  `-Werror`
  
  `-fstack-protector-strong`
  
  `-fsanitize=undefined`
  
  `-fno-sanitize-recover`
  
  `-g`
  
  `-fno-omit-frame-pointer`
  
  `-O1`

    The `-std=c17`, `-pedantic` options indicate that the compiler should ensure compliance with the current C language standard.
  
    With `-Wall`, `-Wextra` options, the compiler will report any observed defects.
  
    Options `-Wformat-security`, `-Wduplicated-cond`, `-Wfloat-equal`, `-Wshadow`, `-Wconversion`, `-Wjump-misses-init`, `-Wlogical-not-parentheses`, `-Wnull-dereference`, `-Wvla` enable detecting additional defects.
  
    Option `-Werror` indicates that the compiler should treat defects as errors.
  
    With `-fstack-protector-strong`, certain erroneous stack references will be detected during program execution.
  
    Options `-fsanitize=undefined`, `-fno-sanitize-recover` enable detecting operations that have an undefined effect.
  
    Options `-g`, `-fno-omit-frame-pointer` improve error runtime messages.
  
    Option `-O1` enables optimizations, increasing the likelihood of detecting errors.
  
    All mentioned compiler options are required. No other options will be added.
  
    Please note that different versions of the `gcc` compiler may handle the same options differently. Therefore, before submitting a solution, it is advisable to compile and test it on `students` as described above.
  
- During validation and testing, the program name is executed under the control of the Valgrind program with the command:
  
  `valgrind --leak-check=full -q --error-exitcode=1 ./name arguments`
  
  If Valgrind detects an error, even if the result is correct, we consider the test program as failed.
  
  The `-q` option ensures that only error messages are displayed by the Valgrind program.
  
  The `--leak-check=full` option instructs Valgrind to search for memory leaks, among other things.
  
  The `--error-exitcode=1` option specifies the exit code of the program in case Valgrind detects an error.
  
- A nonzero result of the `main()` function indicates a runtime error.
- The correctness of the result is verified by redirecting the contents of the `.in` file to the program's input and comparing the output using the `diff` program with the `.out` file, e.g.:
  
  `< example.in ./name | diff - example.out`
  
  The correctness assessment is binary. The result is considered correct if the `diff` program does not indicate any differences compared to the expected result.

# Notes
- As a solution, a `.c` text file with the source code in the C language should be submitted.
- It is assumed that the data is correct.
- It is assumed that each data line, including the last one, ends with a representation of the end of line `'\n'`.
  Care should be taken to ensure that this condition is also met by the program's output.
- It is assumed that the values of constants `ROWS` and `COLUMNS`, if specified during compilation, are positive integers.
- The solution should have a memory cost linear with respect to the number of live cells.
- It is assumed that the coordinates of the window and the coordinates of the live cells fit within the range of the `int` type and even that they are larger than `INT_MIN` and smaller than `INT_MAX`.
- The number of live cells should not be limited. It is only assumed that it will be within the range of the `int` type and that the representation of live cells will fit into the dynamic memory of the program.
- During validation and correctness tests, the time limit will be set to 30 seconds.
  
  A solution in which the time cost of calculating the next generation is linear with respect to the number of live cells will definitely fit within the time limit in all tests. A less efficient program may have a problem with this in some tests. However, we guarantee that there will be at least 6 correctness tests that algorithms with a quadratic cost of calculating the next generation should be able to handle.
  
  Solutions with a worse than quadratic complexity may not even pass validation tests.

# Tips
- If the description of the initial generation is in a file `generation.txt`, then the program executed with the command:
  
  `cat generation.txt - | ./task3`
  
  will read the generation and then will read user commands from the keyboard.
  
- The `tee` command can help in preparing test data. It sends data from input to output while simultaneously saving a copy of it in a file whose name is the argument of the command.
  
  Executing the command:
  
  `cat generation.txt - | tee test.in | ./task3`
  
  will run the `task3` program, passing the contents of the `generation.txt` file and then what the user enters as input. At the same time, all data that goes to the program's input will also be saved in the `test.in` file.
  
  The test can be repeated on the same data with the command:
  
  `< test.in ./task3 > test.out`
  
- Command `0` allows continuing the simulation in the next session, starting from where it ended in the previous session. If initially the file `generation.txt` contains the description of the first generation and if we end working with the program by issuing the commands:
  
  `0`
  
  `.`
  
  then each time the commands are executed:
  
  `cat generation.txt - | ./task3 | tee log.txt`
  
  `grep / log.txt > generation.txt`
  
  will start the simulation in the state where we left it previously.
