#ifndef MANAGEMEMORY_INCLUDED
#define MANAGEMEMORY_NCLUDED

#include <stdint.h>


extern segment newSeg();
extern void freeSeg();

extern void unmapSeg();
extern