# 0 - Introduction to the IJVM

> “However, as every parent of a small child knows, converting a large object into small fragments is considerably easier than the reverse process.”

<p style="text-align:right">Andrew S. Tanenbaum</p>

---
Like x86, ARM and RISC-V which were discussed in the course Computer Organization, the Java Virtual Machine (JVM) is an Instruction Set Architecture (ISA). In contrast to x86, ARM and RISC-V, the JVM ISA is not commonly implemented in hardware (but such implementations do exist), but in software. The benefit of this setup is portability: in contrast to say x86 binaries, JVM binaries can be run on any machine with an JVM implementation.

In this course you will implement a variant of the JVM called the Integer Java Virtual Machine (IJVM), as presented in the book  *Structured Computer Organization* by Andrew S. Tanenbaum. The IJVM instruction set is a subset of the Java Virtual Machine instruction set, containing only operations on integers. This eliminates much of the complexity added by different types. 

The IJVM is a stack-based architecture, meaning that (almost) all operations are performed on a stack. This is in contrast to architectures such as Intel x86 which mainly performs its operations on registers. One main benefit of a stack-based architecture is that the instruction set is simpler, since the operations do not need a source and destination operands.

Please make sure you read the [chapter on the IJVM](https://github.com/VU-Programming/pad-skeleton-c/raw/master/SCO-IJVM.pdf) from the book *Structured Computer Organization* and [C - Introduction](introduction_to_c.md) before continuing.


## Tasks

By the end of the course you will have a fully functional IJVM emulator that can execute IJVM bytecode. To achieve this we split the project into five tasks:

1. Parsing the binary.
2. Implementing basic stack manipulation.
3. Implementing control flow.
4. Implementing operations on local variables.
5. Implementing method calls.

By implementing each task and thoroughly testing it, you will avoid common pitfalls that become hard to debug at a later stage. 

Note that our tests are pretty comprehensive, but they do not guarantee that you did not do anything wrong. Hence, it may be possible that a test in, say, task 5 fails because you made an error in the functionality of task 3.

## The IJVM instruction set

The IJVM architecture has the following instructions:
(in general, all arguments are signed, unless they are indices of local variables or constants.)

| OpCode | Instruction   | Args      | Description |
| ------ | ------------- | --------- | ----------- |
| 0x10   | BIPUSH        | byte      | Push a (signed) byte onto the stack |
| 0x59   | DUP           | N/A       | Push a copy of the top word onto the stack |
| 0xFE   | ERR           | N/A       | Print an error message to the machine output and halt the emulator |
| 0xA7   | GOTO          | short     | Increment the program counter by a (signed) short |
| 0xFF   | HALT          | N/A       | Halt the emulator |
| 0x60   | IADD          | N/A       | Pop two words from the stack and push their sum |
| 0x7E   | IAND          | N/A       | Pop two words from the stack and push their bitwise AND |
| 0x99   | IFEQ          | short     | Pop a word from the stack and branch if it equals zero |
| 0x9B   | IFLT          | short     | Pop a word from the stack and branch if it is less than zero |
| 0x9F   | IF_ICMPEQ     | short     | Pop two words from the stack and branch if they are equal |
| 0x84   | IINC          | byte byte | Increment a local variable by a value. The first byte is the (unsigned) index of the local variable. The second byte is the (signed) value. |
| 0x15   | ILOAD         | byte      | Push the local variable with (unsigned) index byte onto the stack |
| 0xFC   | IN            | N/A       | Read a character from the machine input and push it onto the stack. If no character is available, push 0 instead. |
| 0xB6   | INVOKEVIRTUAL | short     | Invoke a method |
| 0xB0   | IOR           | N/A       | Pop two words from the stack and push their bitwise OR |
| 0xAC   | IRETURN       | N/A       | Return from the current method |
| 0x36   | ISTORE        | byte      | Pop a word from the stack and store it in the local variable with (unsigned) index byte |
| 0x64   | ISUB          | N/A       | Pop two words from the stack and push their difference **Note:** subtract the top word from the second to top word |
| 0x13   | LDC_W         | short     | Push the constant with index (unsigned) short from the constant pool onto the stack |
| 0x00   | NOP           | N/A       | Do nothing |
| 0xFD   | OUT           | N/A       | Pop a word from the stack and print it to the machine output **Note:** print a character |
| 0x57   | POP           | N/A       | Pop a word from the stack |
| 0x5F   | SWAP          | N/A       | Swap the two top words on the stack |
| 0xC4   | WIDE          | N/A       | Prefix instruction; the next instruction has a 16-bit (unsigned) index. This can be prefixed to ILOAD, ISTORE and IINC. This only changes the size of the index to 16 bits, the constant of IINC remains 8 bits. |

# Example

An IJVM program is specified in JAS (iJvm Assembly Language), for example:

```assembly
.constant
  a -1
  b 2
  c 3
.end-constant

.main
             // state of the stack
  BIPUSH 112 // 112,
  DUP        // 112, 112
  BIPUSH -1  // 112, 112, -1
  IADD       // 112, 111
  DUP        // 112, 111, 111
  DUP        // 112, 111, 111, 111
  BIPUSH  1  // 112, 111, 111, 111, 1
  ISUB       // 112, 111, 111, 110
  OUT        // 112, 111, 111
  OUT        // 112, 111
  OUT        // 112
  OUT        // 
.end-main
```
This program will print "noop": the ASCII characters for (110, 111, 111, 112). This program also features 3 constants a,b and c, which are currently not used but could be loaded on to the stack using **LDC_W**.

The assembler (we use [goJASM](https://github.com/BlackNovaTech/goJASM) for this course) translates such JAS files into IJVM binaries. In this binary, the textual instructions are replaced by their opcodes, textual representations of numbers are replaced by binary numbers and names are replaced by numbers (for example, the constant "a" becomes the first constant 0, "b" becomes 1 etc.). (This is not required, but if you ever want to compile your own JAS files to IJVM binaries, you can install goJASM with `make tools`, which will install the `goJASM` binary in the `tools` directory. ) Your task now is to load in such an IJVM file and run the program by implementing the instructions.


## Web-based implementations

To try out IJVM files, understand how they work and to verify that your implementation works correctly, there are two web-based reference implementations of the IJVM, both made by former students.
*  [WebJVM](https://vu-oofp.gitlab.io/website/webijvm/) by Jur van der Berg, which provides a fast implementation, shows the disassembled jas file and where you are in it and has breakpoints.
* [IJVMore](https://ijvmore.ljz.software/) by Elias Groot provides and implementation that shows the binary instead of the disassembled JAS file, provided snapshots and scripting abilites.

Try them out using the [example.ijvm](https://github.com/VU-Programming/sypp-skeleton/raw/master/files/examples/example.ijvm) of the JAS above.

## More examples

As an example with a loop consider the following ([ijvm file](https://github.com/VU-Programming/sypp-skeleton/raw/master/files/examples/ones.ijvm)):
```assembly
.main
   // prints '1' 9 times
L1:
   BIPUSH 0xA // stack: [10]
L2:
   BIPUSH 0x1 // stack: [i,1]
   ISUB       // stack: [i-1]
   DUP        // stack: [i-1,i-1]
   IFEQ END   // stack: [i-1], Jump to end if zero
   BIPUSH 0x31 // stack: [i-1,0x31]
   OUT         // prints '1' (ascii: 0x31)
   GOTO L2     // // Repeat loop
END:
   HALT
.end-main
```

As a more elaborate example, consider the following C program:
```c
int n = 3;
int c = 0;
while (n != 1) {
    c = c + 1;
    if (n % 2 == 0) {
        int divcounter = 0; // compute n / 2 without division instruction
        while (n != 0) {
            n = n - 2;  
            divcounter= divcounter + 1;
        }
    } else {
        n = n + n + n + 1; // n * 3 + 1 without multiplication
    }
}
printf("%c",c); // prints 'h' the letter with index 7 (length of collatz sequence)
```
This program computes the length of the Collatz sequence for 9 (= 19). (In case you are wondering what this means, it does not matter for this example, but you can read  [Wikipedia](https://en.wikipedia.org/wiki/Collatz_conjecture) or watch the [first couple minutes of this video](https://www.youtube.com/watch?v=094y1Z2wpJg).) This program does not use the division operator `/` as it not available in the IJVM instruction set. Instead it computes `n / 2` by counting how often 2 can be subtracted from `n`.

The following JAS code is equivalent to the above C program. This JAS code is used for task 3, so there are no methods or local variables yet. You can try it out in the web-implementations using the [ijvm file](https://github.com/VU-Programming/sypp-skeleton/raw/master/files/examples/collatz.ijvm).
```assembly
.main
BIPUSH 0x00 // counter, c 
BIPUSH 3  /// c, n
LOOP: // c, n 
    // check if == 1
        DUP         // c, n, n
        BIPUSH 0x01 // c, n, n, 1
        IF_ICMPEQ DONE // c, n
    // add 1 to counter
        SWAP        // n, c
        BIPUSH 0x01 // n, c, 1
        IADD        // n, c=c+1
        SWAP        // c, n
    // check if even or odd         
        DUP         // c, n, n
        BIPUSH 0x01 // c, n, n, 1
        IAND        // c, n, n & 1
        IFEQ EVEN   // c, n
ODD:    
    // 3n+1
        DUP 
        DUP 
        IADD 
        IADD 
        BIPUSH 0x01
        IADD 
        GOTO LOOP
EVEN: // n / 2
      // No division or shift instruction. Instead count how
      // of we can subtract subtract 2
      BIPUSH 1 // divcounter, d . Stack : c,n, d
DIV2: SWAP         // c, d, n 
      BIPUSH 0x02  // c, d, n, 2
      ISUB         // c, d, n=n - 2
      DUP          // c, d, n, n 
      IFEQ DIVDONE // c, d, n
      SWAP         // c, n, d 
      BIPUSH 0x01  // c, n, d, 1
      IADD         // c, n, d=d+1
      GOTO DIV2 
DIVDONE:           // c , d ,n 
      POP          // c, d  
      GOTO LOOP 
DONE: POP // c 
      BIPUSH 97
      IADD
      OUT // prints 'h' the letter with index 7 (length of collatz sequence)
      HALT 
.end-main
```
As an example which also uses local variables and methods, consider the following C program, which computes the sum of n,n-1,...0 recursively.
```c
int sumem(int n) {
    if (n == 0) return 0;
    return n + sumem(n-1);
}
sumem(100)
```
The following JAS code is equivalent to the above C code ([IJVM file for web implementations]( https://github.com/VU-Programming/sypp-skeleton/raw/master/files/examples/recursive_sum.ijvm))
```assembly
.constant
    objref  0xCAFE  // may be any value.  Needed by invokevirtual.
    COUNT 100
    .end-constant
    
.main

    LDC_W objref
    LDC_W COUNT
    INVOKEVIRTUAL sumem
    DUP 
    IAND 
    HALT
.end-main
    
.method sumem(var)
    ILOAD var
    IFEQ ZERO
    ILOAD var
    LDC_W objref
    ILOAD var
    BIPUSH 0x1
    ISUB
    INVOKEVIRTUAL sumem
    IADD
    IRETURN
    ZERO:
        BIPUSH 0x0
        IRETURN
.end-method
```

If you can understand these examples, and have done the installation and read the introduction to C, you are in good shape to start on [task 1](binaries_dreaded_binaries.md).

The [files directory](https://github.com/VU-Programming/sypp-skeleton/tree/master/files) in the skeleton contains all the IJVM file we test with, you can always load them in the web-based implementations to see the correct behavior.

