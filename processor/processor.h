#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>

#include "../stack/stack.h"

const ssize_t REGISTERS_SIZE = 64;
const ssize_t RAM_SIZE       = 1000;

struct SpuStruct
{
    Stack *stk;
    int *commands;
    ssize_t ip;

    int registers[REGISTERS_SIZE];
    int ram[RAM_SIZE]
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
    hlt,

    jmp,
    ja,
    jae,
    jb,
    jbe,
    jne,
    call,
    ret,

    sub,
    mul,
    div,
    sqrt,
    sin,
    cos
};

SpuErrors runProcessor(FILE *InputFile);

#endif