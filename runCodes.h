#ifndef RUNCODES_INCLUDED
#define RUNCODES_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bitpack.h"
#include "manageMemory.h"

extern void run_program(Segment_T segs, unsigned *registers)