#ifndef _DGGT_COLL_STARRAY_H_

#include "dggt_coll_starray_iter.h"

namespace dggt
{
	template <typename T,msize S>
	struct starray
	{
		T[S] mem;
		u32 count;
	};

	template <typename T,msize S>
	starray<T,S> create_starray()
	{
		return starray<T,S>{};
	}

	template <typename T,msize S>
	starray_iter<T,S> push(starray<T,S>* starr);

	template <typename T,msize S>
	starray_iter<T,S> push(starray<T,S>* starr,const T& val);

	template <typename T,msize S>
	starray_iter<T,S> peek(starray<T,S>* starr);

	template <typename T,msize S>
	starray_iter<T,S> pop(starray<T,S>* starr);

	template <typename T,msize S>
	starray_iter<T,S> get(starray<T,S>* starr,msize offset);

	template <typename T,msize S>
	starray_iter<T,S> get_iter(starray<T,S>* starr);

	template <typename T,msize S>
	msize get_count(starray<T,S>* starr);
}

#include "dggt_coll_starray_iter.inl"
#include "dggt_coll_starray.inl"

#define _DGGT_COLL_STARRAY_H_
#endif
