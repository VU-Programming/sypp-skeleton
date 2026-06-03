# C - Introduction

In this section we will explain some key features of the C programming language. We assume you already know a C-like language like C++ or Java.

<iframe width="560" height="315" src="https://www.youtube.com/embed/tas0O586t80" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

The information below is pretty concise, if you need more, check out the following resources (in increasing order of extensiveness)

* [A brief website on C for C++ Programmers](https://uva-cs.github.io/pdr/tutorials/09-c/index.html)
* [Some example C programs](https://gitlab.com/vu-programming/pad/website/-/raw/master/files/code.zip?inline=false)
* [A Crash Course in C on youtube](https://www.youtube.com/playlist?list=PLggLP4f-rq02gmlePH-vQJ8PF6hyf08CN)
* [A pdf of the book "Modern C"](https://hal.inria.fr/hal-02383654v1/document)


## Data types and type casting

C has a number of basic data types. The most commonly used data types are `int` and `char`. You can preface most types with `unsigned` to create an unsigned version of that type (e.g., `unsigned int a = 5;`).

**Note:** uninitialised data is undefined behavior. For example when creating a variable as follows: `int a;`, the value of the integer is undefined.

You can also cast one type of data into another by using the cast operator:
```c
double d = 5.0;
int a = (int) d;
```
Conversion into a bigger type is automatic and does not need a cast:
```c
int a = 5;
double d = a; // look ma, no cast
```

Like in C++, arithmetic operations like division produce the type of the largest input type (for example if one input is `double` and the other is `int` then the output is `double`, but if inputs are `int` then the output is `int`):
```c
int a = 5, b = 2;
double d;

d = a / b;          // 2
d = (double) a / b; // 2.5
```

Sometimes automatic conversion can lead to unexpected behaviour when converting from unsigned to signed or vice versa.
```c
unsigned char uc = 255;
char c = uc; // -1
```
Another example:
```c
unsigned char uc = 255;
int a;

a = uc;        // 255
a = (char) uc; // -1
```

Even though `a` is of type `int`, which is also signed, `uc` is not implicitly cast into its signed counterpart before being assigned to `a`. This is because an `int` is big enough to accommodate all values of an `unsigned char`. This is, however, not the case for a `char`, which has a maximum value of 127. As a result, `uc` must first be reinterpreted as a `char` before being cast into an `int` to preserve its signed representation.

The standard libary `<stdint.h>` defines several types where the bit-size is exactly specified, the following of which might be useful in your IJVM implementation:
* *uint8_t* Unsigned 8-bit integer
* *int8_t* Signed 8-bit integer 
* *uint16_t* Unsigned 16-bit integer
* *int16_t* Signed 16-bit integer
* *int32_t* Signed 32-bit integer (type of a IJVM constant/stack element, aliased as *word_t* in *ijvm.h*)

## Type aliases and typedefs

A new type alias can be defined by using the `typedef` keyword (e.g., `typedef int mynumber_t`). The name of defined types typically end with the suffix `_t`.

## Printing

Printing to `stdout` in C is done via the function `printf` found in the standard library (see **stdio.h**). The variable format can contain a string and, optionally, embedded format tags that are replaced by the values specified in the subsequent arguments.

> An example usage of `printf`:

```c
char c = 'a';

printf("As a character: %c\nAs a decimal number: %d\nAs a hexadecimal number: %hhx\n", c, c, c);
```

When ran, the program above will generate the following output:

```console
As a character: a
As a decimal number: 97
As a hexadecimal number: 61
```

You can also print to other file descriptors, such `stderr` by using `fprintf`. Like `stdout`, `stderr` is also printed when you run a file. The difference is that `stderr` has less buffering, so you cannot lose some print if your program crashes right after the print (which can happen with `stdout`). The method `fprintf` works like `printf`, but the first argument is a file descriptor (which can be `stdout`,`stderr` or any other file). For example: 
```c
fprintf(stderr, "This is debug message %d\n", 5);
```

## Debug prints

In the IJVM skeleton, we provide several macros for debug prints, 
namely `dprintf`, `d2printf`, `d3printf`, `d4printf` and `d5printf`.

Which debug prints give outputs and which do not depends on the debug level, which can be controlled by adjust the value at the top of `machine.c`. If the debug level is 0, no debug prints will be printed. If the debug level is `n`, all prints with a debug level less than or equal to `n` will be printed.

Debug prints which are disabled are not compiled into the program, so they
do not affect performance.

This gives you a method to log all kinds of things for debugging, and control
the granularity with a single variable. 

Example: `d2printf("Current program text %02x %02x\n", text[pc] , text[pc+1]);`.

We recommend you use this to log various things, such as which instruction is currently being handled, what the current stack looks like etc.

## Arrays

As in other languages, C provides the user with a linear data structure to store many elements of the same data type: **arrays**. Arrays can be created in a number of ways:

* By specifying their contents but not their size:

  `int my_array[] = {1, 2, 3};`

* By specifying their size and their contents:

  `int my_array[3] = {1, 2, 3};`

  or:
  
  ```c
  int my_array[3];

  my_array[0] = 1;
  my_array[1] = 2;
  my_array[2] = 3;
  ```

**Note**: the above examples will, depending on the scope, allocate the required memory either on the stack, or as a global variable. If allocated on the stack, the object is only valid within that function’s scope (we will discuss this pitfall further when talking about pointers).

## Strings

Unlike C++, C does not have an exclusive `string` data type. A string in C is a `char` array that is null-terminated, i.e., the last element in the array is a character with the value `’\0’`. Strings can be created in a number of ways:

* By specifying their contents but not their size:

  `char my_string[] = "CoPP";`

  or:

  `char my_string[] = {'C', 'o', 'P', 'P', '\0'};`

  or:

  `char *my_string = "CoPP";`

* By specifying their size and their contents:

  `char my_string[5] = "CoPP";`

  or:

  `char my_string[5] = {'C', 'o', 'P', 'P', '\0'};`

  or:

  ```c
  char my_string[5];

  my_string[0] = 'C';
  my_string[1] = 'o';
  my_string[2] = 'P';
  my_string[3] = 'P';
  my_string[4] = '\0';
  ```

The C standard library provides you with some useful helper functions for strings (see **string.h**). **Note:** many of the string functions can be dangerous if the string is not null-terminated, and can thus cause segmentation faults if used on an improper memory object.

## Pointers

In C, unlike in many other languages, memory management is left entirely up to the programmer. This means that the use of explicit pointers is allowed and even encouraged. To create a pointer to a variable and later dereference it:

```c
int a = 5, b;
int *a_ptr = &a; // &a means address-of a.

b = *a_ptr;   // 5, *a_ptr means read value where a points to
b = a_ptr[0]; // 5, the same as (*a_ptr)
```

As seen in the example above, there are 2 possible ways to dereference a pointer. To further illustrate those:

```c
int my_array[3] = {1, 2, 3};
int *my_ptr = my_array;
int a, b, c;

a = *my_ptr;       // 1
a = my_ptr[0];     // 1

b = *(my_ptr + 1); // 2
b = my_ptr[1];     // 2

c = *(my_ptr + 2); // 3
c = my_ptr[2];     // 3
```

It is important to note that even though arrays and pointers can behave similarly under certain circumstances, they are **not** the same. To highlight some major differences:

* An array created this way:

  ```c
  int my_array[3];

  my_array[0] = 1;
  my_array[1] = 2;
  my_array[2] = 3;
  ```

  is not equal to:

  ```c
  int *my_ptr;

  my_ptr[0] = 1;
  my_ptr[1] = 2;
  my_ptr[2] = 3;
  ```
  In fact, the latter example is memory unsafe, as the memory to store the integers is never allocated. This can result in memory corruption or a segmentation fault.

* When using the `sizeof` operator:

  ```c
  int my_array[5];
  int *my_ptr;
  size_t s;

  s = sizeof(my_array); // 20
  s = sizeof(my_ptr);   // 8
  ```

  **Note:** the size of a pointer is dependent on the word size of the system. It is 8 bytes on a 64-bit machine and 4 bytes on a 32-bit machine.

* It is not possible to reassign an array:
  
  ```c
  int my_array[3] = {1, 2, 3}, some_array[5] = {4, 5, 6, 7, 8};
  int a = 5;

  my_array = some_array; // compiler error
  my_array = &a;         // compiler error
  ```

* It is also not possible for functions to return arrays:

  ```c
  int *get_ptr(void)
  {
    int my_array[5] = {1, 2, 3, 4, 5};

    return my_array;
  }

  int *my_ptr = get_ptr(); // compiler warning
  ```

  As mentioned previously, the memory required for the array will be allocated on the stack and, consequently, the array will only be valid within the scope of the function `get_ptr`. As a result, dereferencing `my_ptr`, which is outside the scope of `get_ptr`, results in undefined behaviour. This undefined behaviour is compiler-dependent, however, most, if not all, modern compilers will produce a warning message. Compiling the program with **gcc** and running it yields a segmentation fault, whereas compiling the program with **clang** and running it results in memory corruption. 

## Dynamic memory allocation

To dynamically allocate memory on the heap, as opposed to allocating a static amount of memory on the stack, the C standard library provides some useful functions (see **stdlib.h**):

* `malloc(size_t size)`: allocates `size` bytes and returns a pointer to the allocated memory.
**Note:** memory allocated via `malloc` is not initialised.

* `free(void *ptr)`: frees the memory space pointed to by `ptr`.
**Note:** the pointer passed to `free` must have been previously returned by a call to `malloc`, `calloc` or `realloc`.

* `calloc(size_t nmemb, size_t size)`: allocates memory for an array of `nmemb` elements of `size` bytes each and returns a pointer to the allocated memory.
**Note:** the memory is initialised to zero.

* `realloc(void *ptr, size_t size)`: changes the size of the memory block pointed to by `ptr` to `size` bytes and returns a pointer to the reallocated memory.
**Note:** if the new size is larger than the old size, the added memory will not be initialised.

We can now recreate some of the previous examples using dynamic memory allocation:

* Allocating a memory block on the heap:

  ```c
  int *my_ptr = (int *) malloc(sizeof(int) * 3);

  my_ptr[0] = 1;
  my_ptr[1] = 2;
  my_ptr[2] = 3;
  ```

  or:

  ```c
  int *my_ptr = (int *) calloc(3, sizeof(int));

  my_ptr[0] = 1;
  my_ptr[1] = 2;
  my_ptr[2] = 3;
  ```

  **Note:** it is important to note that it is not possible to obtain the size of a memory block on the heap using `sizeof`, and, as such, it is best to keep track of size using variables instead. 

* Using `realloc` to change the size of a memory block on the heap:

  ```c
  int *my_ptr = (int *) malloc(sizeof(int) * 3);

  my_ptr[0] = 1;
  my_ptr[1] = 2;
  my_ptr[2] = 3;

  my_ptr = (int *) realloc(my_ptr, sizeof(int) * 5);

  my_ptr[3] = 4;
  my_ptr[4] = 5;
  ```

* Returning a pointer to a memory block on the heap:

  ```c
  int *get_ptr(void)
  {
    int *some_ptr = (int *) malloc(sizeof(int) * 5);

    some_ptr[0] = 1;
    some_ptr[1] = 2;
    some_ptr[2] = 3;
    some_ptr[3] = 4;
    some_ptr[4] = 5;

    return some_ptr;
  }

  int *my_ptr = get_ptr();
  ```

It is important to note that all allocated memory must be freed via `free` at some point during the execution of a program. Not doing so will result in **memory leaks**.

## Structs

C, unlike C++ and Java, is not an object-oriented programming language. However, it is still possible to semantically bind multiple values together with a single data type, using **structs**. Structs can be created in a number of ways:

* Without defining a new type alias:

  ```c
  struct BankAccount {
    int balance;
    char id[32];
  }
  ```

  To then define a struct object, type: `struct BankAccount my_account;`.
  
* By defining a new type alias:

  ```c
  typedef struct BankAccount {
    int balance;
    char id[32];
  } bank_account_t;
  ``` 
  or:
  
  ```c
  typedef struct {
    int balance;
    char id[32];
  } bank_account_t;
  ```

  To then define a struct object, type: `bank_account_t my_account;`.

Structs can also be initialised in a number of ways:

* Upon declaration:

  ```c
  bank_account_t my_account = {
    .balance = 100,
    .id = "NL88INGB1234567890"
  };
  ```
  
* After declaration:

  ```c
  bank_account_t my_account;

  my_account.balance = 100;
  strncpy(my_account.id, "NL88INGB1234567890", 32);
  ```

It is also possible to have pointers to struct objects. However, you must first allocate memory for the struct object itself:

```c
bank_account_t *my_account = (bank_account_t *) malloc(sizeof(bank_account_t));
```

To then dereference it later:

```c
int my_balance = my_account->balance;
```

## File I/O

The C standard library provides you with some useful functions for reading and writing to files (see **stdlib.h**):

* `fopen(const char *pathname, const char *mode)`: opens the file whose name is the string pointed to by `pathname` and returns a `FILE` pointer. The argument `mode` points to a string beginning with one of the following sequences:

  * `rb`: open binary file for reading

  * `wb`: truncate file to zero length or create binary file for writing 

  * `ab`: open binary file for appending or create binary file for writing

  Please visit the [IBM manual page](https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-fopen-open-file) on `fopen` for a complete list of file modes.

* `fclose(FILE *stream)`: flushes the stream pointed to by `stream` and closes the underlying file descriptor

* `fread(void *ptr, size_t size, size_t nmemb, FILE *stream)`: reads `nmemb` items of data, each `size` bytes long, from the stream pointed to by `stream`, storing them at the location given by `ptr`

* `fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)`: writes `nmemb` items of data, each `size` bytes long, to the stream pointed to by `stream`, obtaining them from the location given by `ptr`

* `fseek(FILE *stream, long offset, int whence)`: sets the file pointer for the stream pointed to by `stream` to a new position, which is obtained by adding `offset` bytes to the position specified by `whence`. The argument `whence` can have one of the following values:

  * `SEEK_SET`: beginning of the file

  * `SEEK_CUR`: current file position

  * `SEEK_END`: end of the file

* `ftell(FILE *stream)`: obtains the current value of the file position indicator for the stream pointed to by `stream`

* `rewind(FILE *stream)`: sets the file position indicator for the stream pointed to by `stream` to the beginning of the file

> An example of reading an entire file into a buffer:

```c
char *buf = (char *) malloc(sizeof(char) * fsize);

fread(buf, sizeof(char), fsize, fp);
```

It is also possible to read other data types from a file, however the obtained value depends on the **endianness** of the system (we will discuss this concept later in the manual):

```c
int a;

fread(&a, sizeof(int), 1, fp);
```

## Switch statements

In C, switch statements allow a variable to be tested for equality against a number of cases: 

```c
switch(instruction)
{
    case OP_BIPUSH:
        // Do something
        break;
    case OP_DUP:
        // Do something
        break;
    default:
        // DO something
        break;
}
```

## Header files

In C, it is possible to insert the contents of a header file (**.h**) into the source code using the `#include` preprocessing directive. To insert a header file, type:

```c
#include <file.h>
```

or:

```c
#include "file.h"
```

The difference between using `<>` and `""` is subtle, but important. When using `<>` to include a header file, the preprocessor will search a predetermined directory on your system to locate the header file. However, when using `""` to include a header file, the preprocessor will search the same directory as the source file to locate the header file. As such, use `""` to insert header files located in the **include** directory.

### Header guards

As a program grows, so does the number of source and header files it's comprised of. More often than not, newer functionality is built upon already existing functionality, which creates complex relationships between files. A common issue that arises as a result of complex relationships between header files is the declaration of a variable or function multiple times. **Header guards** are preprocessing directives used to ensure that each header file is included in the compilation unit only once:

```h
#ifndef MY_HEADER_H
#define MY_HEADER_H

// Declarations and function prototypes

#endif
```

or:

```h
#pragma once

// Declarations and function prototypes
```

### Global variables

It is possible to declare global variables in header files using the `extern` keyword. The `extern` keyword allows multiple files to refer to the same global variable, as long as it is defined in a source file.

**Note:** one, and only one, header file should declare the variable. Similarly, one, and only one, source file should define the variable.

> An example header file **log.h**:

```h
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

extern FILE *log_file;

void log_to_file(const char *str, FILE *fp);

#endif
```

> An example source file **log.c** corresponding to the header file **log.h**:

```c
#include "log.h"

FILE *log_file = NULL;

void log_to_file(const char *str, FILE *fp)
{
    if (log_file == NULL)
        log_file = fopen("log.txt", "w");

    if (fp == NULL)
        fprintf(log_file, str);
    else
        fprintf(fp, str);
}
```


### Function prototypes

The main purpose of header files is to provide an interface that can be later used by the programmer. As such, header files should only include typedefs, structs, global variables and **function prototypes**. The prototype of a function is simply its declaration:

```h
double pow(double x, double y);
```

### Static functions

It is possible to limit the scope of a function to the file it's defined in using the `static` keyword. Static functions are a good way to indicate that a function is not a part of any interface, much like `private` in other languages. 
```c
static int example_helper_function(int a) {
  return a * 2;
}
```


## Command-line arguments

In C, command line arguments are passed as an array of strings to the `main` function of your program:

```c
int main(int argc,char **argv)
{
  printf("%s: Hello %s, you were born in %s.\n", argv[0], argv[1], argv[2]);
}
```

Running the program above using `./main myname 1991` would produce the following output:

```console
./main: Hello myname, you were born in 1991.
```

## Assertions

Assertions in C check that a program satisfies certain conditions at particular points in its execution. If a condition is not satisfied, the program is aborted and an error message is generated. This is helpful, because otherwise the program would continue and probably crash later, at which point it is significantly harder to figure out what is wrong.

### Usage

To use assertions, include the **assert.h** header file and call `assert` throughout your program. The `assert` function takes an expression that evaluates to either true or false as an argument: `assert(sp > -1)`.

# Tools

When programming in C for this project, several other tools may be useful:

## xxd

Since you will be working with binary files, there are some tools that come in handy when debugging and or creating test inputs. One such tool, **xxd**, creates a hex dump of a given file. You should read up on the [hexadecimal numeral system](https://en.wikipedia.org/wiki/Hexadecimal) if you are unfamiliar with it. Modifying binary files can be done using an editor such as **hexedit**.

> An example of an IJVM binary hex dump obtained via **xxd**:

```console
bash$ xxd -g 1 -c 8 test.ijvm
00000000: 1d ea df ad 00 01 00 00  ........
00000008: 00 00 00 00 00 00 00 00  ........
00000010: 00 00 00 0d 10 31 fd a7  .....1..
00000018: 00 06 10 32 fd 10 33 fd  ...2..3.
00000020: ff                       .
```


## Git

Using version control is a must for larger projects. During this course you will, incrementally, build a final application. Sometimes you might make a design decision that at a later stage seems detrimental. In such cases it is really useful to be able to revert back to a certain earlier stage. This is where version control systems, such as SVN, Mercurial, and Git come in handy. While useful, it is not required to use Git.

One of the TAs made a video demonstration of basic Git commands:

<iframe width="560" height="315" src="https://www.youtube.com/embed/fZ13fe7LKg4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

The commands illustrated above are:

* `git init`: creates a new local Git repository
* `git add <pathspec>`: add one or more files to staging
* `git commit -m <message>`: commit changes to HEAD
* `git log`: show the commit logs

Please refer to [this guide](http://rogerdudler.github.io/git-guide/) and the [Git manual](https://git-scm.com/docs) for a more comprehensive list of Git commands.

Furthermore, it might be a good idea to use a service like [GitHub](https://github.com/) as a backup for your code (but note that it is **not** allowed in any course at the VU to make your code public!).

## goJASM

To write and compile your own JAS files you need an assembles, for which we are using [goJASM](https://github.com/BlackNovaTech/goJASM). See [Project skeleton](skeleton.md#using-gojasm) for how to use `goJASM`.



## Valgrind

Valgrind's Memcheck is a memory error detector. It can detect and track common memory errors such as:

* Accessing unallocated memory (e.g., going out of bounds) or memory that has been previously freed
* Using uninitialized values
* Incorrect usage of `free`, such as double-freeing memory allocated on the heap
* Memory leaks

### Usage

To use Memcheck, prepend `valgrind` to the command you use to run your program (e.g., `valgrind ./test1`). It is also important to make use of flags such as `--leak-check=full` and `--track-origins=yes`, as they provide additional context when debugging memory errors. 

Please refer to [this guide](https://students.cs.byu.edu/~cs235ta/labs/valgrind/valgrind.php) to understand the output of `valgrind`.

---
You can check your implementation for memory errors using `make testleaks` and `make testsanitizers`.

---

**Note:** `valgrind`, and, consequently, `make testleaks` is no longer supported on macOS. Please use `make testsanitizers` to detect memory errors.


## LLDB

LLDB is the LLVM project debugger, which is a popular debugger for UNIX systems to debug C and C++ programs.

LLDB works similarly to many other debugging tools. You can insert breakpoints in your code where LLDB will stop execution and let you control the execution. You can add many breakpoints, step through your program line by line and at any time print out the values of your variables. LLDB can be a handy tool to figure out what and where something goes wrong when you receive an error during execution.

You can also use LLDB (or the alternative GDB) from VSCode.

### Installation

See the installation guide

### Usage

In order to use **lldb**, compile your code with the flag `-g` to include debugging information (when using the project skeleton this is already set). Start your program with the lldb debugger by typing `lldb <executable>`. To start with a textual user interface (in GDB) type `gdb -tui <executable>`. Run your program with `run <arguments>`. When inside the debugger you can always type `help` for a list of instructions.

In **lldb** you can set breakpoints on a certain line of your file by typing `break <line_number>` or at a certain function by typing `break <function_name>`. The execution will stop at every breakpoint, allowing you to perform actions, such as checking values, viewing the stack, performing operations and much more. It also allows you to step through the program line by line or continue to the next breakpoint.  Some of many handy commands to use are:

* `n`: Execute 1 line
* `finish`: Continue to the end of the function
* `c`: Continue to the next breakpoint
* `enable`/`disable <breakpoint>`: Enable or disable 1 or more breakpoints. Leave breakpoint blank for selecting all.
* `explore`: View the contents and type of a variable or other data structure
* `backtrace` or `bt`: View the backtrace (handy after an error)
* `list`: View source code
* `up`: Go up one context level on stack
* `down`: Go down one context level on stack (after calling up)
* `p <variable_name>`: Print out the chosen variable
* `disp <variable_name>`: Print out the chosen variable every time the program halts
* `set variable <variable_name> = <new_value>`: Set the value of a variable
* `call function_name(args)`: Call a function with args, typically a function created for debugging purposes


It is possible to set **conditions** on breakpoints. For example, to set a condition on breakpoint 1 to only break if the variable `x` equals `0`, type `condition 1 x==0`.

**Convenience variables** can be used to store values internally inside **gdb**. All convenience variables start with a `$` and can be used, for example, as follows: `set $foo = *obj_pointer`. This will save in `foo` the value contained in the object pointed to by `obj_pointer`.

**Watchpoints** can be used to stop execution whenever the value of an expression changes, without having to predict a particular place where this may happen. Also sometimes referred to as a data breakpoint. The most common way to use watchpoints are to set them on a single variable. The execution will then stop whenever the value of that variable is changed. To set a watchpoint, type `watch <variable>`.
