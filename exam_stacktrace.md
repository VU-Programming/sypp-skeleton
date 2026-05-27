# Exam Task: Implementing STACKTRACE

In this exam assignment, you will extend the IJVM to include a new debugging instruction that prints a detailed trace of the current method call stack.

## The Task
Implement the new instruction `STACKTRACE`. This instruction does not take any bytecode arguments.

* **`STACKTRACE`** (Opcode: `OP_STACKTRACE` / `0x38`): Iterates through the linked list of stack frames starting from the **current frame**, tracing all the way down to (and including) the `main` method. For each normal method frame, it uses `fprintf(m->out, ...)` to output:
  1. The total number of local variables in the frame (including all method arguments and the `OBJREF`).
  2. The saved Program Counter (`Prev_PC`) that points back to the caller method.

For the `main` method frame (which has a base pointer of 0), it simply prints a special indicator since it has no caller to inspect.

*(Note: The macro `OP_STACKTRACE` has already been defined for you in `include/ijvm.h`.)*

### Expected Output Format
For each normal method frame, you must print the following exact string using `fprintf`:
```c
fprintf(m->out, "Frame: Locals=%u, CallerPC=%x\n", num_locals, prev_pc);
```
For the `main` method frame, you must print exactly:
```c
fprintf(m->out, "Frame: Main\n");
```

Number of locals = number arguments + objref + local variables

### How to achieve this:
To print a stacktrace, you must trace back through the frame structure by jumping from Base Pointer (LV) to Base Pointer, evaluating the state of each frame along the way.

1. Start at your current `m->lv`.
2. The value at `m->stack[m->lv]` is the **Link Pointer**.
3. The value at the Link Pointer (`m->stack[Link Pointer]`) is the saved program counter (`Prev_PC`).
4. The value right after the Link Pointer (`m->stack[Link Pointer + 1]`) is the saved base pointer of the caller (`Prev_LV`).
5. **Finding the number of locals**: Because the frame is placed directly on the stack, the distance between the start of the frame (`m->lv`) and the end of the frame's local variables (which is exactly where the `Link Pointer` sits) represents the total number of arguments and local variables. Therefore: `Number of Locals = Link Pointer - m->lv`.
6. Once you have printed the information for the current frame, update your pointer to `Prev_LV` and repeat the process.
7. Stop your loop when you process the frame with a base pointer of `0` (which indicates the `main` method). Remember to print the special `Main` output for it!

This mechanism deeply tests your understanding of the IJVM stack structure, pointer arithmetic, and how frames form a linked list.

## Testing your implementation
We have provided an updated `goJASM` configuration file and a test suite.

2. **JAS file:** We have provided `files/exam/test_stacktrace.jas`, which performs nested method calls and executes `STACKTRACE`. 
3. **C Test Suite:** We have provided `tests/test_stacktrace.c` and integrated it into your `Makefile`.

You can compile and run the exam tests by simply running:

```bash
make test_stacktrace
```
