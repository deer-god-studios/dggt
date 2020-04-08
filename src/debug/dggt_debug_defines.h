#ifndef _DGGT_DEBUG_DEFINES_H_

/*!
 * @def ASSERT(P)
 * @brief Halts (ie. crashes) the program if the given predicate evaluates to false.
 * */


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

#define _DGGT_DEBUG_DEFINES_H_
#endif
