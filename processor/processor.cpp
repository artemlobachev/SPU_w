#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "processor.h"

#include "../common/InOutFunc/InputOutput.h"
#include "../common/LogError/Log.h"

static const int POISON = 0XDEAD;

static SpuErrors ExecuteCommands(SpuStruct *spu)
{
    assert(spu);

    int command = POISON;
    while (true)
    {
        command = spu->commands[spu->ip];
        spu->ip++;
        
        switch(command)
        {
            case push:

            case pop:

            case jmp:

            case ja:

            case jae:

            case jb:
            
            case jbe:

            case jne:

            case call:

            case ret:

            case sub:

            case mul:

            case div:

            case sqrt:

            case sin:

            case cos:

            case hlt:

            default:
                puts("Undefined")
        }
    }

    return SpuErrors::NO_ERR;
}

static void SpuDtor(SpuStruct *spu)
{
    assert(spu);

    free(spu->commands);
    spu->commands = nullptr;
    spu->ip = POISON;

    StackDtor(&spu->stk);
}

SpuErrors RunProcessor(FILE *InputFile)
{
    assert(InputFile);

    SpuStruct spu = {};
    SpuErrors error = SpuCtor(&spu, InputFile);
    if (error != SpuErrors::NO_ERR)
    {
        SpuDtor(&spu);
        return error;
    }

    error = ExecuteCommands(&spu);

    SpuDtor(&spu);

    return error;
}

static SpuErrors SpuCtor(SpuStruct *spu, FILE *InputFile)
{
    assert(InputFile);

    spu->commands = BinRead(InputFile);
    spu->ip       = 0;

    for (int i = 0; i < RAM_SIZE; i++)
        spu->ram[i] = 0;

    spu->stk = {};
    ErrorCode StackError = StackCtor(&spu->stk, 321);
    
    SpuErrors error = (StackError ? SpuErrors::STACK_ERROR : SpuErrors::NO_ERR);
    if (error != SpuErrors::NO_ERR)
    {
        //LogError(error);
        return SpuErrors::STACK_ERROR;
    }

    return SpuErrors::NO_ERR;
}

static int *BinRead(FILE *InputFile)
{
    assert(InputFile);

    ssize_t CommandsCount = (GetFileSize(InputFile) / sizeof(int)) + 1;
    
    int *CommandsBuffer = (int *) calloc(CommandsCount, sizeof(int));
    if (CommandsBuffer == nullptr)
    {
        LogError("alloc error");
        
        return nullptr;
    }

    if (fread(CommandsBuffer, sizeof(int), CommandsCount, InputFile))
        LogError("read file error");

    return CommandsBuffer;
}