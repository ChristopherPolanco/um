typedef struct Instruct {
    unsigned opCode;
    unsigned a;
    unsigned b;
    unsigned c;
} Instruct;

static void conditionalMove(uint32_t * registers, unsigned a, unsigned b, unsigned c){
    if(registers[c] != 0){
        registers[a] = registers[b];
    }
    return;
}

static void segmentedLoad(uint32_t * registers, unsigned a, unsigned b, unsigned c, Segment_T program){
    registers[a] = Segment_get(program, registers[b], registers[c]);
    return;
}

static void segmentedStore(uint32_t * registers, unsigned a, unsigned b, unsigned c, Segment_T program){
    Segment_set(program, registers[a], registers[b], registers[c]);
    return;
}

static void addition(uint32_t * registers, unsigned a, unsigned b, unsigned c){
    registers[a] = registers[b] + registers[c];
    return;
}

static void multiplication(uint32_t * registers, unsigned a, unsigned b, unsigned c){
    registers[a] = registers[b] * registers[c];
    return;
}

static void division(uint32_t * registers, unsigned a, unsigned b, unsigned c){
    registers[a] = registers[b]/registers[c];
    return;
}

static void bitwiseNand(uint32_t * registers, unsigned a, unsigned b, unsigned c){
    registers[a] = ~(registers[b] & registers[c]);
    return;
}

static void halt(Segment_T program){
    Segment_free(program);
    exit(0);
}

static void mapSegment(uint32_t * registers, unsigned b, unsigned c, Segment_T program){
    unsigned ad = Segment_map(program, registers[c]);
    registers[b] = ad;
    return;
}

static void unmapSegment(uint32_t * registers, unsigned c, Segment_T program){
    Segment_unmap(program, registers[c]);
    return;
}

static void output(uint32_t * registers, unsigned c){
    printf("%c", registers[c]);
    return;
}

static void input(uint32_t * registers, unsigned c){
    registers[c] = fgetc(stdin);
    return;
}

static void loadProgram(uint32_t * registers, unsigned b, unsigned c, Segment_T program, unsigned * count){
    if(registers[b] != 0){
        Segment_load(program, registers[b]);
    }

    *count = registers[c] - 1;
    return;
}

static void loadValue(uint32_t * registers unsigned a, uint32_t val){
    registers[a] = val;
    return;
}
