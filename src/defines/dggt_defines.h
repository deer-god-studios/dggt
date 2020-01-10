#ifndef _DGGT_DEFINES_H_

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

#define _DGGT_DEFINES_H_
#endif
