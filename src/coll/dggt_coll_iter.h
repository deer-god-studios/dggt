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

	// TODO: these aren't technically necessary and might just pollute
	// 		the namespace.  But it does sort of ensure there's a common
	// 		interface across iterators so I dunno.
	template <typename T,typename C,typename M>
	b32 is_end(const iter<T,C,M> iter) { return iter.is_end(); }
	template <typename T,typename C,typename M>
	b32 next(iter<T,C,M> iter) { return iter.next(); }
	template <typename T,typename C,typename M>
	T& get(iter<T,C,M> iter) { return iter.get(); }
	template <typename T,typename C,typename M>
	const T& get(const iter<T,C,M> iter) { return iter.get(); }
	template <typename T,typename C,typename M>
	T* get_ptr(iter<T,C,M> iter) { return iter.get_ptr(); }
	template <typename T,typename C,typename M>
	const T* get_ptr(const iter<T,C,M> iter) { return iter.get_ptr(); }
	template <typename T,typename C,typename M>
	M get_mem(iter<T,C,M> iter) { return iter.get_mem(); }
	template <typename T,typename C,typename M>
	const M get_mem(const iter<T,C,M> iter) { return iter.get_mem(); } 
	// NOTE: returns true if the iterator is assiciated with a collection.
	// 		If this fails it usually means you have a bad problem.
	template <typename T,typename C,typename M>
	b32 is_coll_valid(const iter<T,C,M> iter) { return iter.is_coll_valid(); }
	// NOTE: returns true if the memory type the iterator has matches the collection's
	// 		current memory state.  If this fails it usually means the memory may still
	// 		need to be freed.
	template <typename T,typename C,typename M>
	b32 is_mem_valid(const iter<T,C,M> iter) { return iter.is_mem_valid(); }
	// NOTE: Will ensure, if possible, that the memory in the iterator matches
	// 		the collection.  Used if you've previously corrected invalid mem by
	// 		freeing it in an appropriate allocator or if you can't be fucked with it.
	template <typename T,typename C,typename M>
	b32 vindicate_mem(iter<T,C,M> iter) { return iter.vindicate_mem(); }
}

#define _DGGT_COLL_ITER_H_
#endif
