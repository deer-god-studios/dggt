/// @cond IncludeGuard
#ifndef _DGGT_H_
/// @endcond



// TODO: errors!
// 		* error logging.
// 		* warnings
// 		* get_error()
// 		* error messages.
// 		* etc.
// TODO: template metaprogramming:
// 		* typelist
// 		* enable_if
// 		* tuples!
// TODO: composite allocator!!
// TODO: collections
// 		* iterators
// 		* nodes
// 		* search
// 		* sort
// TODO: math:
// 		* perlin/simplex noise
// 		* geometry
// TODO: physics:
// 		* collision detection!!
// TODO: IO
// 		* loading images
// 		* 3d models
// TODO: audio (?)
// TODO: input (?)
// TODO: X.org!!!!
// TODO: memory
//		* add set_block/free_block(?) functions to allocators.
// TODO: comments and docs!
// TODO: AI
// 		* state machine
// 		* 'goal-oriented' AI
// 		* path-finding (A*)

/*!
 * @brief The main namespace for the dggt library.
 * */
namespace dggt { }

#include "defines/dggt_defines.h"
#include "math/dggt_math.h"
#include "types/dggt_types.h"
#include "mem/dggt_mem.h"
#include "coll/dggt_coll.h"

/// @cond IncludeGuard
#define _DGGT_H_
#endif
/// @endcond
