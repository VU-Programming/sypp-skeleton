# Exam Task: Implementing STACKTRACE

In this exam assignment, you will extend the IJVM to include a new debugging instruction that prints a detailed trace of the current method call stack.

## The Task
Implement the new instruction `STACKTRACE`. This instruction does not take any bytecode arguments.

* **`STACKTRACE`** (Opcode: `OP_STACKTRACE` / `0x38`): Iterates through the linked list of stack frames starting from the **current frame**, tracing all the way down to (and including) the `main` method. For each normal method frame, it uses `fprintf(m->out, ...)` to output:
  1. The total number of local variables in the frame (including all method arguments and the `OBJREF`).
  2. The saved Program Counter (`Prev_PC`) that points back to the caller method.

For the `main` method frame (which has a base pointer of 0), it simply prints a special indicator since it has no caller to inspect.

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

## Implementation

Implement the new instruction `OP_STACKTRACE`. Add the following line to `include\ijvm.h`

```c
#define OP_STACKTRACE     (0x38)
```

## Testing your implementation

Pressing Run to run `test_stacktrace` as well as the original basic tests. 
Your implementation must pass both the new as well as the original basic tests.
We do not test the advanced tests here, and it is not required your implementation 
still passes them.
