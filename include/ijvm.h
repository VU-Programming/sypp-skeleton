#ifndef IJVM_H
#define IJVM_H

#include <stdio.h>  /* contains type FILE * */
#include <stdint.h>  /* contains exact integer types int32_t, uint8_t */
#include <stdbool.h> /* contains the boolean */

#include "ijvm_struct.h"

#define MAGIC_NUMBER 0x1DEADFAD

#define OP_BIPUSH         (0x10)
#define OP_DUP            (0x59)
#define OP_ERR            (0xFE)
#define OP_GOTO           (0xA7)
#define OP_HALT           (0xFF)
#define OP_IADD           (0x60)
#define OP_IAND           (0x7E)
#define OP_IFEQ           (0x99)
#define OP_IFLT           (0x9B)
#define OP_IF_ICMPEQ      (0x9F)
#define OP_IINC           (0x84)
#define OP_ILOAD          (0x15)
#define OP_IN             (0xFC)
#define OP_INVOKEVIRTUAL  (0xB6)
#define OP_IOR            (0xB0)
#define OP_IRETURN        (0xAC)
#define OP_ISTORE         (0x36)
#define OP_ISUB           (0x64)
#define OP_LDC_W          (0x13)
#define OP_NOP            (0x00)
#define OP_OUT            (0xFD)
#define OP_POP            (0x57)
#define OP_SWAP           (0x5F)
#define OP_WIDE           (0xC4)

// Bonus assignment instructions
#define OP_TAILCALL       (0xCB)

#define OP_NEWARRAY       (0xD1)
#define OP_IALOAD         (0xD2)
#define OP_IASTORE        (0xD3)

#define OP_ANEWARRAY      (0xBD)
#define OP_AIALOAD        (0x32)
#define OP_AIASTORE       (0x53)

#define OP_GC             (0xD4)

#define OP_NETBIND        (0xE1)
#define OP_NETCONNECT     (0xE2)
#define OP_NETIN          (0xE3)
#define OP_NETOUT         (0xE4)
#define OP_NETCLOSE       (0xE5)
/**
 * DO NOT MODIFY THIS FILE.
 **/



/**
 * Initializes the IJVM with the binary file found at the provided argument.
 * input gives the file where the ijvm reads from for the IN command
 * output gives the file where the ijvm writes to for the OUT command
 *
 * Returns  - A pointer to an ijvm struct on success
 *          - NULL on failure
 **/
ijvm* init_ijvm(char *binary_path, FILE* input, FILE* output);


/**
 * Destroys a vm, that is to say, free all memory associated with the machine
 * and allow for a new call to init_ijvm().
 */
void destroy_ijvm(ijvm* m);

/**
 * Returns the currently loaded program text as a byte array.
 **/
uint8_t *get_text(ijvm* m);


/**
 * Returns the size of the currently loaded program text.
 **/
uint32_t get_text_size(ijvm* m);

/**
 * @param i index of the constant to obtain
 * @return The constant at location i in the constant pool.
 **/
int32_t get_constant(ijvm* m, uint32_t i);


/**
 * Returns the value of the program counter (as an offset from the first instruction).
 **/
uint32_t get_program_counter(ijvm* m);

/**
 * This function should return the word at the top of the stack of the current
 * frame, interpreted as a signed integer.
 **/
int32_t tos(ijvm* m);

/**
 * Step (perform) one instruction and return.
 * In the case of WIDE, perform the whole WIDE_ISTORE, WIDE_ILOAD or WIDE IINC.
 * If machine has halted or encountered an error, finished() should report
 * true afterward. 
 **/
void step(ijvm* m);


/**
 * Check whether the machine has any more instructions to execute.
 *
 * A machine will stop running after:
 * - reaching the end of the text section
 * - encountering either the HALT/ERR instructions
 * - encountering an invalid instruction
 */
bool finished(ijvm* m);



/**
 * @param i index of variable to obtain.
 * @return Returns the i:th local variable of the current frame.
 **/
int32_t get_local_variable(ijvm* m, uint32_t i);

/**
 * @return The value of the current instruction represented as a byte.
 *
 * This should NOT increase the program counter.
 **/
uint8_t get_instruction(ijvm* m);

/**
 * Initializes the IJVM with the binary file found at the provided argument using 
 * stdin as input and stdout as output 

 * Returns  - A pointer to an ijvm struct on success
 *          - NULL on failure
 **/
ijvm* init_ijvm_std(char *binary_path);

/**
 * Run the vm with the current state until the machine halts.
 **/
void run(ijvm* m);


// Below: methods needed for bonus assignments

// Only needed for Tailcall assignment: 
//
// Get some measure indicative of the (call)stack size
// If you have a single continous stack this can be
// the number of elements on the stack
// Or it can be for example be the number of frames on the stack
// We use this only to test stack depth when using tailcall is less
// then when using regular calls. 
uint32_t get_call_stack_size(ijvm* m);


// Only needed for garbage collection assignment
// Checks if reference is a freed heap cell
// If a heap cell is garbage, then after a garbage collection run
// this method must return true on a reference to that cell
//  *until* the next NEWARRAY instruction (which may reuse the reference)
//
bool is_heap_freed(ijvm* m, int32_t reference);

// Only needed for precise garbage collection bonus
// using ANEWARRAY, AIALOAD and AIASTORE
bool is_tos_reference(ijvm* m);

#endif
