#include <stdio.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_goto1(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/GOTO1.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    step(m);
    assert(tos(m) == 0x31);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 0x33);
    step(m);
    destroy_ijvm(m);
    fclose(o);
}

void test_goto2(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/GOTO2.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    step(m);
    assert(tos(m) == 0x31);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 0x33);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 0x32);
    step(m);
    destroy_ijvm(m);
    fclose(o);
}

void test_ifeq1(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/IFEQ1.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    int startpc = 0;

    // L1
    step(m);
    assert(tos(m) == 0x5);

    // L2 iteration 1
    steps(m, 6);
    assert(tos(m) == 0x4);
    steps(m, 3);
    startpc = get_program_counter(m);

    // L2 iteration 2
    steps(m, 6);
    assert(tos(m) == 0x3);
    steps(m, 3);
    assert(startpc == get_program_counter(m));

    // L2 iteration 3
    steps(m, 6);
    assert(tos(m) == 0x2);
    steps(m, 3);
    assert(startpc == get_program_counter(m));

    // L2 iteration 4
    steps(m, 6);
    assert(tos(m) == 0x1);
    steps(m, 3);
    assert(startpc == get_program_counter(m));

    // L2 iteration 5
    steps(m, 6);
    assert(tos(m) == 0x0);
    steps(m, 2);

    // Should have branched to L3
    assert(startpc + 15 == get_program_counter(m));

    destroy_ijvm(m);
    fclose(o);
}

void test_iflt1(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/IFLT1.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    int oldpc = get_program_counter(m);

    // L1
    steps(m, 2);
    assert(oldpc + 5 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L2
    steps(m, 2);
    assert(oldpc + 5 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L3
    steps(m, 2);
    assert(oldpc + 5 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L4
    steps(m, 4);
    assert(oldpc + 19 == get_program_counter(m));
    steps(m, 1);
    assert(tos(m) == 0x37);
    destroy_ijvm(m);
    fclose(o);
}

void test_ificmpeq1(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/IFICMPEQ1.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    int oldpc = get_program_counter(m);

    // L1
    steps(m, 3);
    assert(oldpc + 7 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L2
    steps(m, 5);
    assert(oldpc + 10 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L3
    steps(m, 4);
    assert(oldpc + 8 == get_program_counter(m));
    oldpc = get_program_counter(m);

    // L4
    for (int i = 0; i < 3; i++) {
        steps(m, 3);
        assert(oldpc == get_program_counter(m));
        oldpc = get_program_counter(m);
    }

    // L6
    steps(m, 2);
    assert(oldpc + 9 == get_program_counter(m));
    steps(m, 2);
    assert(tos(m) == 0x13);
    destroy_ijvm(m);
    fclose(o);
}

void test_collatz(void)
{
    FILE *o = get_null_output();
    ijvm* m = init_ijvm("files/task3/Collatz.ijvm",stdin,o);
    assert(m != NULL);
    assert(m->out == o);

    while(get_instruction(m)!=OP_IOR){
        step(m);
    }
    assert(tos(m) == 19);
    destroy_ijvm(m);
    fclose(o);
}

int main(void)
{
    fprintf(stderr, "RUN test3: FLOW ..............\n");
    RUN_TEST(test_goto1);
    RUN_TEST(test_goto2);
    RUN_TEST(test_ifeq1);
    RUN_TEST(test_iflt1);
    RUN_TEST(test_ificmpeq1);
    RUN_TEST(test_collatz);
    return END_TEST();
}
