#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/ijvm.h"

// Declaration of test framework functions
void run_test(bool test, char *message) {
  if (test) {
    printf("   [Ok] %s\n", message);
  } else {
    printf("   [Failed] %s\n", message);
    exit(1);
  }
}

void do_stacktrace_test(char *ijvm_path, char *test_name, int32_t expected_tos, char *expected_output) {
  printf("RUN %s: Validating STACKTRACE instruction ..............\n", test_name);

  FILE *out_file = tmpfile();
  ijvm *m = init_ijvm(ijvm_path, stdin, out_file);
  run_test(m != NULL, "VM initialized successfully");

  // Run the VM until it halts.
  while (!finished(m)) {
    step(m);
  }

  run_test(tos(m) == expected_tos, "VM successfully completed execution and returned expected value to main");

  // Verify the STACKTRACE output
  char buf[256];
  memset(buf, '\0', 256);
  rewind(out_file);
  fread(buf, 1, 255, out_file);

  if (strncmp(buf, expected_output, strlen(expected_output)) == 0) {
    run_test(true, "STACKTRACE output exactly matches the expected format and values");
  } else {
    printf("Expected STACKTRACE output:\n%s\n", expected_output);
    printf("Actual STACKTRACE output:\n%s\n", buf);
    run_test(false, "STACKTRACE output did not match expected values");
  }

  destroy_ijvm(m);
}

int main() {
  printf("========================================\n");
  do_stacktrace_test(
      "files/exam/test_stacktrace.ijvm", 
      "test_stacktrace1", 
      42, 
      "Frame: Locals=3, CallerPC=15\nFrame: Locals=5, CallerPC=9\nFrame: Main\n"
  );

  printf("========================================\n");
  do_stacktrace_test(
      "files/exam/test_stacktrace2.ijvm", 
      "test_stacktrace2 (zero locals)", 
      99, 
      "Frame: Locals=1, CallerPC=5\nFrame: Main\n"
  );

  printf("========================================\n");
  do_stacktrace_test(
      "files/exam/test_stacktrace3.ijvm", 
      "test_stacktrace3 (deep recursion)", 
      1, 
      "Frame: Locals=2, CallerPC=1b\nFrame: Locals=2, CallerPC=1b\nFrame: Locals=2, CallerPC=1b\nFrame: Locals=2, CallerPC=7\nFrame: Main\n"
  );

  printf("========================================\n");
  printf("## [Ok] passed all tests in test_stacktrace.c ##\n");
  return 0;
}
