// TODO: module namespaces.

/*!
 * @file dggt.h
 * @brief The public interface of the @ref dggt.
 * */
/// @cond IncludeGuard
#ifndef _DGGT_H_
/// @endcond

/*!
@defgroup dggt DGGT Library
@defgroup math Math Library
@defgroup lin Linear Algebra Library
@defgroup mem Memory Management Library
@defgroup ex Example Code Source Files
@defgroup coll Collections Library
@defgroup str String Library
@defgroup tmpl Template Library
@defgroup phy Physics Library
@defgroup phycoll Collisions Library
@defgroup debug Debug Library
@defgroup log Logging Library
*/



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
// TODO: collections
// 		* trees
// 		* graphs
// 		* heap/priority queues
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
// TODO: function timing/clocks.

/*!
 * @brief The main namespace for the dggt library.
 * */
namespace dggt { }

#include "defines/dggt_defines.h"
#include "math/dggt_math.h"
#include "types/dggt_types.h"
//#include "tmpl/dggt_tmpl.h"
#include "mem/dggt_mem.h"
//#include "coll/dggt_coll.h"

/// @cond IncludeGuard
#define _DGGT_H_
#endif
/// @endcond
