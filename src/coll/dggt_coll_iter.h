#ifndef _DGGT_COLL_ITER_H_

#include "types/dggt_types.h"
namespace dggt
{
	template <typename T,typename C>
	struct iter;

	// TODO: these aren't technically necessary and might just pollute
	// 		the namespace.
	template <typename T,typename C>
	b32 is_end(const iter<T,C> iter) { return iter.is_end(); }
	template <typename T,typename C>
	b32 next(iter<T,C> iter) { return iter.next(); }
	template <typename T,typename C>
	T& get(iter<T,C> iter) { return iter.get(); }
	template <typename T,typename C>
	const T& get(const iter<T,C> iter) { return iter.get(); }
	template <typename T,typename C>
	T* get_ptr(iter<T,C> iter) { return iter.get_ptr(); }
	template <typename T,typename C>
	const T* get_ptr(const iter<T,C> iter) { return iter.get_ptr(); }
}

#define _DGGT_COLL_ITER_H_
#endif
