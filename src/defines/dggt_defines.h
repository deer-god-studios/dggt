#ifndef _DGGT_DEFINES_H_

#include <climits>
#include <cfloat>

#ifdef DGGT_DEBUG
#ifdef ASSERT
#undef ASSERT(P)
#endif
#define ASSERT(P) { if(!(P)) { int oops=*((int*)0); } } 
#else
#ifdef ASSERT
#undef ASSERT(P)
#endif
#define ASSERT(P)
#endif

#define MAX_UINT32 UINT_MAX
#define MAX_MSIZE ULLONG_MAX
#define MAX_FLOAT32 FLT_MAX
#define MIN_FLOAT32 FLT_MIN
#define MAX_REAL32 MAX_FLOAT32
#define MIN_REAL32 MIN_REAL32

#define _DGGT_DEFINES_H_
#endif
