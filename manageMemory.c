#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <seq.h>
#include <uarray.h>
#include <stack.h>


#include "manageMemroy.h"

#define T Segment_T

struct T{
    Stack_T trace;
    Seq_T segments;
};


extern T Segment_new(){
    T segs = malloc(sizeof(*segs));

    segs->segments = Seq_new(5);

    segs->trace = Stack_new();

    return segs;
}


extern void Segment_free(T segs){
    UArray_T list;

    for(int i = 0; i < Seq_length(segs->segments); i++){
        list = Seq_remlo(segs->segments);

        //frees individual parts of the segment sequence 
        if(list != NULL) UArray_free(&list);
    }

    //free everything in the struct
    Stack_free(&segs->trace));
    Seq_free(&(segs->segments));

    //free the struct
    free(segs);

    return;
}

extern uint32_t Segment_get(T segs, unsigned id, unsigned takeoff){
    UArray_T s = Seq_get(segs->segments, id);
    return *(uint32_t *)Uarray_at(s, takeoff);
}


extern void Segment_set(T segs, uint32_t var, unsigned id, unsigned takeoff){
    UArray_T s = Seq_get(segs->segments, id);
    *(uint32_t *)UArray_at(s, takeoff) = var;

    return;
}


extern uint32_t Segment_map(T segs, int size){
    unsigned i;

    UArray_T new = UArray_new(size, sizeof(uint32_t));

    if(!Stack_empty(seg->trace)){
        i = (unsigned)(uintptr_t)Stack_pop(segs->trace);
        Seq_put(segs->segments, i, (void*)new);
    }

    else{
        Seq_addhi(segs->segments, (void*) new);
        i = Seq_length(seg->segments) - 1;
    }

    return (uint32_t) i;
}



extern void Segment_unmap(T segs, unsigned id){
    UArray_T s = Seq_put(segs->segments, id, NULL);
    UArray_free(&s);
    Stack_push(segs->trace, (void *)(uintptr_t)id);

    return;
}


extern void Segment_load(T segs, unsigned id){
    UArray_T s = Seq_get(segs->segments, id);

    int size = Uarray_length(s);
    UArray_T new = UArray_copy(s, size);
    UArray_T first = Seq_put(segs->segments, 0, new);
    UArray_free(&first);

    return;
}