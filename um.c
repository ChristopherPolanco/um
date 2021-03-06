#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "runCodes.h"
#include "manageMemory.c"

int main(int argc, char *argv[]) {
    assert(argc == 2);
    
    FILE *input = fopen(argv[1], "rb");
    
    assert(input);

    //find the size of the given file
    fseek(input, 0L, SEEK_END);
    int size = ftell(input);
    //set the marker back to the begining of the file
    fseek(input, 0L, SEEK_SET);

    Segment_T segments = Segment_new();
    uint32_t address = Segment_map(memory, number_instructions);

    for (int i = 0; i < size / 4; i++) {
        uint64_t instruction = 0;

        for (int j = 3; j >= 0; j--) {
            uint64_t byte = getc(input);
            instruction = Bitpack_newu(instruction, 8, (j * 8), byte);
        }
    
        Segment_set(memory, (uint32_t)instruction, address, i);
    }

    //Reginald Aka Register (DO NOT REMOVE)
    uint32_t reginald[8]; 

    run_program(segments, reginald);
    
    fclose(input);
    Segment_free(segments)
}