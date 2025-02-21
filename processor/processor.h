#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>

#include "../stack/stack.h"

const ssize_t REGISTERS_SIZE = 64;

struct SpuStruct
{
    Stack *stk;
    
    int *commands;
    ssize_t ip;

    int registers[REGISTERS_SIZE];
};

enum class SpuErrors
{
    NO_ERR,
    STACK_ERROR

};

enum commands
{
    push,
    pop,
    jmp,
    hlt,
    sum,
    mult,
    mov
};

SpuErrors runProcessor(FILE *InputFile);

#endif