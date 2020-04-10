#ifndef _DGGT_COLL_STARRAY_H_

#include "dggt_coll_starray_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T,msize S>
	struct starray:
		collection<T,starray_mem<T,S>,starray<T>,starray_iter<T,S>>
	{
		stblk<T,S> mem;
		u32 count;
	};

	template <typename T,msize S>
	starray<T,S> create_starray()
	{
		return starray<T,S>{};
	}

	template <typename T,msize S>
	starray<T,S>::iter push(starray<T,S>* starr);

	template <typename T,msize S>
	starray<T,S>::iter push(starray<T,S>* starr,const T& val);

	template <typename T,msize S>
	starray<T,S>::iter peek(starray<T,S>* starr);

	template <typename T,msize S>
	starray<T,S>::iter pop(starray<T,S>* starr);

	template <typename T,msize S>
	starray<T,S>::iter get(starray<T,S>* starr,msize offset);

	template <typename T,msize S>
	starray<T,S>::iter get_iter(starray<T,S>* starr);

	template <typename T,msize S>
	msize get_count(starray<T,S>* starr);
}

#include "dggt_coll_starray_iter.inl"
#include "dggt_coll_starray.inl"

#define _DGGT_COLL_STARRAY_H_
#endif
