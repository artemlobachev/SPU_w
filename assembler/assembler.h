#ifndef ASM_H
#define ASM_H

#include <stdint.h>

const ssize_t LABEL_SIZE  = 64;
const ssize_t LABEL_COUNT = 64;

enum class AsmErrors
{
    NO_ERR,
    WRITE_BIN_ERR,
    LABELS_ERR

};

struct BinCode
{  
    int *binCode;
    ssize_t binCodeSize;
};

struct LabelStruct
{
    char label[LABEL_SIZE];
    int32_t labelAdress;
};

#endif