#include <stdio.h>
#include <time.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_set_in_out(void) 
{
    FILE* in = fopen("files/task1/aninput", "r");
    FILE *out = fopen("files/task1/anoutput", "wb");
    ijvm* m = init_ijvm("files/task1/program1.ijvm",in,out);
    assert(m != NULL);
    assert(in == m->in);
    assert(out == m-> out);
    destroy_ijvm(m);
    fclose(in);
    fclose(out);
}

void test_program_1(void)
{
    ijvm* m = init_ijvm_std("files/task1/program1.ijvm");
    assert(m != NULL);
    assert(get_text_size(m) == 7);
    uint8_t *ip = get_text(m);

    // If it fails here you haven't implemented get_text()
    assert(ip != NULL);
    // Instructions in binary
    assert(ip[0] == 0x10); // BIPUSH
    assert(ip[2] == 0x10); // BIPUSH
    assert(ip[4] == 0x60); // IADD
    assert(ip[5] == (uint8_t)0xFD); // OUT
    destroy_ijvm(m);
}

void test_program_2(void)
{
    ijvm* m = init_ijvm_std("files/task1/program2.ijvm");
    assert(m != NULL);
    assert(get_text_size(m) == 16);
    uint8_t *ip = get_text(m);

    // Instructions in binary
    assert(ip[0] == 0x00);
    assert(ip[1] == (uint8_t)0x13);
    assert(ip[4] == (uint8_t)0x59);
    assert(ip[5] == (uint8_t)0x13);
    assert(ip[8] == (uint8_t)0x60);
    assert(ip[9] == (uint8_t)0x13);
    assert(ip[12] == (uint8_t)0x60);
    assert(ip[13] == (uint8_t)0xFD);
    assert(ip[14] == (uint8_t)0x00);
    destroy_ijvm(m);
}

void test_constants_1(void)
{
    ijvm* m = init_ijvm_std("files/task1/program2.ijvm");
    assert(m != NULL);

    assert(get_constant(m,0) == 3);
    assert(get_constant(m,1) == 2);
    assert(get_constant(m,2) == 1);
    destroy_ijvm(m);
}

void test_constants_2(void)
{
    ijvm* m = init_ijvm_std("files/task1/program1.ijvm");
    assert(m != NULL);

    assert(get_constant(m,0) == 65537);
    assert(get_constant(m,1) == 5);
    assert(get_constant(m,2) == -2147483648);
    assert(get_constant(m,3) == -65536);
    assert(get_constant(m,4) == 2);
    assert(get_constant(m,5) == 2147483647);

    destroy_ijvm(m);
}

// test correct swap
void test_magicnum_swap(void)
{
    ijvm* res = init_ijvm_std("files/task1/bad-magicnum-addfea1d.ijvm");
    assert(res == NULL);
}

// this test checks that init_ijvm return NULL when the magicnum is incorrect
void test_magicnum(void)
{
    srand((unsigned int)time(NULL));
    uint8_t x = rand() % 255;
    FILE *fp = fopen("files/task1/badfile.ijvm", "wb");
    int random_num = 5 + rand() % 15;
    for (int i = 0; i < random_num; i++)
    {
        fputc(x, fp);
        do x = rand() % 255; while (x == 0xEA);  // Ensure 
    }
    fclose(fp);
    ijvm* res = init_ijvm_std("files/task1/badfile.ijvm");
    assert(res == NULL);
}


int main(void)
{
    fprintf(stderr, "*** test1: BINARIES ..........\n");
    RUN_TEST(test_set_in_out)
    RUN_TEST(test_program_1);
    RUN_TEST(test_program_2);
    RUN_TEST(test_constants_1);
    RUN_TEST(test_constants_2);
    RUN_TEST(test_magicnum_swap);
    RUN_TEST(test_magicnum);
    return END_TEST();
}
