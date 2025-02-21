#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "processor.h"
#include "../common/LogError/Log.h"

int main(const int argc, const char *argv[])
{
    FILE *InputFile = fopen(argv[1], "rb");
    
    SpuErrors error = RunProcessor(InputFile);

    return (int) error;
}