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


extern void runInstruct(Segment_T segs, unsigned* registers, Instruct ion, int &count){
    if(ion.opCode > 13) exit(1);

    if(ion.opCode == 0) conditionalMove(registers, ion.a, ion.b, ion.c);

    if(ion.opCode == 1) segmentedLoad(registers, ion.a, ion.b, ion.c, segs);
        
    if(ion.opCode == 2) segmentedStore(registers, ion.a, ion.b, ion.c, segs);

    if(ion.opCode == 3) addition(registers, ion.a, ion.b, ion.c);

    if(ion.opCode == 4) multiplication(registers, ion.a, ion.b, ion.c);
        
    if(ion.opCode == 5) division(registers, ion.a, ion.b, ion.c);

    if(ion.opCode == 6) bitwiseNand(registers, ion.a, ion.b, ion.c);

    if(ion.opCode == 7) halt(segs);

    if(ion.opCode == 8) mapSegment(registers, ion.b, ion.c, segs);

    if(ion.opCode == 9) unmapSegment(registers, ion.c, segs);

    if(ion.opCode == 10) output(registers, ion.c);

    if(ion.opCode == 11) input(registers, ion.c);

    if(ion.opCode == 12) loadProgram(registers, ion.b, ion.c, segs, count);

    if(ion.opCode == 13) loadValue(registers, ion.a, (uint32_t)ion.b);

    return;
}


Instruct getInstruct(Instruct ion, uint32_t var){
    ion.opCode = Bitpack_getu(var, 4, 28);
    
    if(ion.opCode != 13){
        ion.a = Bitpack_getu(var, 3, 6);
        ion.b = Bitpack_getu(var, 3, 3);
        ion.c = Bitpack_getu(var, 3, 0);    
    }

    else{
        ion.a = Bitpack_getu(var, 3, 25);
        ion.b = Bitpack_getu(var, 25, 0);
    }

    return ion;
}


extern void run_program(Segment_T segs, unsigned *registers){
    uint32_t var;
    Instruct ion;

    unsigned count = 0;

    /*
    The reason why this while loop runs indefinitely is because 
    the halt will terminate the program once reached.
    */ 
    while(true){
        var = Segment_get(segs, 0, count);
        ion = getInstruct(ion, var);
        runInstruct(segs, registers, ion, &count);
        count += 1;
    }
}