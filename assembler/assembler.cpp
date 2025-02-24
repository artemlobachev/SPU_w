#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>
#include <sys\types.h>
#include <string.h>

#include "assembler.h"
#include "../common/InOutFunc/InputOutput.h"
#include "../common/commands.h"
#include "../common/LogError/Log.h"

AsmErrors assembly(FILE *asmFile, FILE *binFile)
{
    assert(asmFile && binFile);

    const char *inCode = readFile(asmFile);
    
    LabelStruct labels[LABEL_COUNT] = {};
    if (defineLabels(labels, inCode) != AsmErrors::NO_ERR)
    {
        LogError("huevo build");
        return AsmErrors::LABELS_ERR;
    }

    BinCode outCode = {};
    GenerateBinCode(labels, inCode, &outCode);

    if (fwrite(outCode.binCode, sizeof(int), outCode.binCodeSize, binFile))
    {
        LogError("vibeeeeeee");
        return AsmErrors::WRITE_BIN_ERR;
    }

    return AsmErrors::NO_ERR;
}

static AsmErrors defineLabels(LabelStruct *labels, const char *asmCode)
{
    assert(labels && asmCode);

    static const ssize_t MAX_COMMAND_SIZE = 64;
    static char commandBuffer[MAX_COMMAND_SIZE] = "";

    assert(MAX_COMMAND_SIZE > 0);

    ssize_t codeIndex = 0; // mean which symbol
    ssize_t LabelsCounter = 0;

    while (asmCode[codeIndex])
    {   
        codeIndex = NewStringAdr(&asmCode[codeIndex]) - asmCode;

        assert(codeIndex >= 0);

        ssize_t commandSize = -1;
        sscanf(&asmCode[codeIndex], "%63s%n", commandBuffer, &commandSize);

        assert(commandSize <= MAX_COMMAND_SIZE && commandSize > 0);
        codeIndex += commandSize;

        if (IsLabel(commandBuffer, commandSize))
        {
            addLabel(labels, commandBuffer, codeIndex, commandSize, LabelsCounter);
            LabelsCounter++;
            continue;
        }

        parseCommand(commandBuffer);
    }
}

static AsmErrors parseCommand(const char *commandBuffer)
{
    assert(commandBuffer);

}

static AsmErrors addLabel(LabelStruct *labels, const char *commandBuffer, const ssize_t codeIndex, 
                          const ssize_t commandSize, ssize_t LabelsCounter)
{
    assert(labels && commandBuffer && LabelsCounter && LabelsCounter >= 0);
        
    if (LabelsCounter > LABEL_COUNT)
    {
        LogError("wtf");
        return AsmErrors::LABELS_ERR;
    }

    strncpy(labels[LabelsCounter].label, commandBuffer, commandSize);
    labels[LabelsCounter].labelAdress = codeIndex;

    return AsmErrors::NO_ERR;
}

static bool IsLabel(const char *commandBuffer, const ssize_t commandSize)
{
    assert(commandBuffer);

    const char *endBufferPtr = commandBuffer + commandSize - 1; 

    while (endBufferPtr > commandBuffer)
    {
        if (*commandBuffer == ':')
            return true;
    
        if (!isspace(*commandBuffer))
            return false; 

        commandBuffer++;
    }

    return false;
}

static AsmErrors GenerateBinCode(LabelStruct *labels, const char *inCode, BinCode *outCode)
{
    assert(labels && inCode && outCode);

    if ()
}