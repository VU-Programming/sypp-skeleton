
# Project skeleton

To automate testing the functionality of each submission, we have provided a skeleton layout for the project. You already downloaded the skeleton in the [Installation instructions](framework.md).

To test your installation & open VSCode/XCode:

1. Open any UNIX shell (Ubuntu on Windows)
2. Navigate to the `sypp-skeleton` directory where you downloaded the framework.
3. Type `pwd` (which gives the current working directory) and check that it ends with `sypp-skeleton`. If not, navigate to the correct folder. (Please refer to [this guide](https://mally.stanford.edu/~sr/computing/basic-unix.html) if you're unfamiliar with UNIX commands.)
4. * On Windows/Linux: Type `code .`. This should open up VSCode and you should be able to explore the framework via the explorer (top left icon on the left side-plane).
   * On macOS : Type `open 'Systems Programming Project.xcodeproj'` This should open up XCode and you should be able to explore the framework via the explorer 
5. Type `make testall`. This should output the following:
```
clang -MMD -Iinclude -g -Wall -Wpedantic  -std=c11 -Wformat-extra-args -c -o obj/ijvm.o src/ijvm.c
clang -MMD -Iinclude -g -Wall -Wpedantic  -std=c11 -Wformat-extra-args -c -o obj/util.o src/util.c
clang -Iinclude -g -Wall -Wpedantic  -std=c11 -Wformat-extra-args -lm -ldl -o test1 obj/ijvm.o obj/util.o tests/test1.c
./test1
*** test1: BINARIES ..........
Assertion error 'get_text_size(m) == 7' in tests/test1.c:22
make: *** [Makefile:95: run_test1] Aborted (core dumped)
```


The first two lines are the compilation `ijvm.c` and `util.c`. The third line is the compilation of the first test. Both compilations are successful which is indicated by the lack of error messages beneath the compilation commands. The fourth line `./test1` indicates that we are going to run `test1`. The fifth line is the output of `test1` indicating its name: `BINARIES`. The test fails on the 6th line, which is what we expect because you have not implemented the first task yet.



## Workflow

When working on the assignment, we suggest the following setup:
* Keep a terminal open to run test commands (`make testall`)
* Keep an instance of VSCode/XCode open to adjust your code 

## Folder Structure

In the provided template we include a number of folders. 
* `include` contains header (`.h`) files
* `src` contains source (`.c`) files
* `files` contains JAS and `.ijvm` files (these are used in the tests)
* `tests` contains the tests
* `tools` contain tools : a grading script and the `gojasm` assembler (if installed)
* `obj` contains temporary compiled (object) files


All your source code (.c files) should be placed in the **src** folder and all your header files (.h files) should be placed in the **include** folder. **Please do not alter this folder structure!**

You need to implement all the functions defined in **ijvm.h** in the file **ijvm.c**, as we use these functions to test your program. To add variables to your ijvm interpreter, modify **ijvm-struct.h**.  Both the **ijvm.h** and **ijvm-struct.h** header files can be found in the **include** folder.

## Running the tests

We have provided a set of test cases for you to test your program with. By passing all basic tests and at least 5 advanced tests, **you will be able to pass the course**.

---
You can run build and run these tests using `make testall`.

---

You can also build and run the basic and advanced tests separately using `make testbasic` and `make testadvanced` respectively.

---

If you ever get the situation where a test fails on codegrade but succeeds on your system, run `make testsanitizers`. This will use the Clang sanitizers, which instrument your code to detect behaviour which is not defined in the C standard such as array indexing out of bounds, use of uninitialized variables or reliance on an undefined order.  We recommend you always use the sanitizers before submitting to codegrade.

---
Additionally, you can build and run individual tests. For example, you can build and run the tests for task 1 using `make run_test1`. If you pass the tests, the binary will print a message, if not it will print an error message or – in the worst case – crash.

You can also build, but not run, all the tests using `make build_tests`. Similarly, you can build, but not run, individual tests. For example, you can build, but not run, the tests for task 1 using `make test1`. This will create a binary called **test1** in your top-level directory. You can then run the test using `./test1`. 

## Running IJVM binaries

Internally, the provided tests run IJVM binaries using your implementation of the emulator to ensure it behaves as expected. However, it is also possible to run these IJVM binaries separately. To do so, compile the `ijvm` binary using `make ijvm` and run the desired IJVM binary using `./ijvm /path/to/binary.ijvm`.

## Using gojasm

To convert an Java Assembly(JAS) program to an `ijvm` binary, you can use the [goJASM](https://github.com/BlackNovaTech/goJASM) assembler. 

In order to install this, open a terminal and navigate to the directory where you installed the framework.
```
cd tools
make gojasm
```
This will download the `gojasm` program and place in the tools directory. 

You can put your `.jas` files in the `files/jas_assignments/` directory. 

In order to assemble your for example `stack.jas` file to a `stack.ijvm` file, run this command from the root of the project (i.e. the `sypp-skeleton` folder): 
```
./tools/gojasm files/jas_assignments/stack.jas -o files/jas_assignments/stack.ijvm
```
Alternatively, you can put `gojasm` in your `PATH` (the environment variable that has a list of directories where commands are looked up). From the root of the project:
```
export PATH=$PATH:`pwd`/tools 
```
You can now navigate to the `jas_assignments` directory and do
```
gojasm stack.jas -o stack.ijvm
```

