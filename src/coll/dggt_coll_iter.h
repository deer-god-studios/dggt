#ifndef _DGGT_COLL_ITER_H_
// TODO: iterator increment and dereference operator overloads

#include "types/dggt_types.h"
namespace dggt
{
	// T is the underlying type that the collection holds
	// C is the collection type.
	// M is the 'memory type' or what the container allocates (nodes for linked_list, blk's for stack, etc.)
	// TODO: This is bad.  It's confusing and superfluous.  
	// 		I'll fix it.  Sometime.  Probably.
	template <typename T,typename C,typename M>
	struct iter;
}

#define _DGGT_COLL_ITER_H_
#endif
