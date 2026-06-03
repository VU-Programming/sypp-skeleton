# C - Style guidelines

While it is important that your program produces the correct output, it is just as important that it is made easily readable for others (or your future self). As such, we've provided you with several criteria you can follow to help you write better code. We will use these criteria when grading your program on style (0.5 points).

## Messiness

The most important thing is that the code looks cleaned up, and not messy, such that it is easy to read and navigate. It should not contain random commented out code, unreachable code, non-descriptive naming (`monkey1`, `monkey2` etc), code in places that do not make sense, etc.

## Consistency

Your choice of naming convention (e.g., `snake_case` or `camelCase`) and style (e.g., K&R or Allman) does not matter, as long as you stick to one or the other. In other words, **avoid** doing the following:

```c
int *my_ptr, *anotherPtr;

void do_something(void)
{
    // Do something
}

void doSomethingElse(void) {
    // Do something else
}
```

## Naming

The names of your variables and functions should be clear and provide just enough, that is, not too much or too little, context for the reader. In other words, **avoid** doing the following:

```c
// Too little context
int num1, num2;

int num_magic(int num1, int num2);

// Too much context
double temperature_as_a_double_precision_floating_point_number;

double convert_temperature_from_celsius_to_fahrenheit(double temperature);
```

**Note:** the example above assumes there is no further context behind the variables and functions. It is perfectly acceptable to name variables `num1` and `num2` within the right context (e.g., `int sum(int num1, int num2);`), however the same cannot be said for `num_magic`. 


## Magic numbers

A magic number is a number which has a specific value but of which the meaning is not explained. (A related, but different usage of the term magic number is for the constant to identify a file format). This should be avoided by giving the number a name explaining its meaning. For example:

```c 
sp = 4096
```

Should be converted to:

```c
const int MAX_MAIN_LOCALS = 256;
...
sp = MAX_MAIN_LOCALS;
```


## Functions

It is quite likely that you will have to apply the same operation several times throughout your program. Avoid repeating the same few lines of code by replacing them with function calls. For example, make a function for reading in a short from the program text instead of repeating this each time you need to read a short.

## Structs

[Structs](./introduction_to_c.md#structs) provide much needed structure to variables that otherwise appear scattered. It is a good idea to group related variables together using a struct.

## Multiple files

In a way similar to structs, files help group together related code. It is thus a good idea to utilise [header files](./introduction_to_c.md#header-files) and directories (**src** and **include**) to organise your code. Make sure **not** to include any source code in your header files, as they are meant to store declarations and function prototypes.

## Opcodes

The **ijvm.h** header file includes macro definitions of constants that correspond to each opcode (e.g., `OP_BIPUSH` is assigned the constant value `0x10`). As such, you should avoid using opcodes in your switch statement, and instead use constants defined in the **ijvm.h** header file.

## Character limit

You should try to avoid writing lines of code longer than 80 characters. While this practice is at least as old as [IBM punched cards](https://en.wikipedia.org/wiki/Punched_card#IBM_80-column_format_and_character_codes), it remains a widely accepted standard to this day.

## Comments

In a way similar to naming variables and functions, your comments should provide just enough context for the reader. They should not state the obvious and should instead provide insight into the methodology. In other words, **avoid** doing the following:

```c
// Declare number 1 and number 2
int num1, num2;

// Calculate the sum of 2 integers
int sum(int num1, int num2);
```

**Note:** this only applies to comments meant to be seen by others.

## Memory management

All the memory allocated during the runtime of your program should be freed by the end of it, otherwise your program will leak memory. While it is not necessary to debug obscure memory leaks, all of your obvious memory allocations should be freed.
