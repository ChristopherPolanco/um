#ifndef MANAGEMEMORY_INCLUDED
#define MANAGEMEMORY_NCLUDED

#include <stdint.h>

#define T Segment_T


extern Segment_T Segment_new();
extern void Segment_free(T segs);

extern uint32_t Segment_get(T segs, unsigned id, unsigned takeoff);
extern void Segment_set(T segs, uint32_t var, unsigned id, unsigned takeoff);


extern uint32_t Segment_map(T segs, int size);
extern void Segment_unmap(T segs, unsigned id);

extern void Segment_load(T segs, unsigned id);

#undef T 
#endif