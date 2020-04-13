#ifndef _DGGT_COLL_STARRAY_H_

#include "dggt_coll_starray_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T,msize S>
	using starray_settings=
	coll_settings<T,starray_mem<T,S>,starray<T,S>,starray_iter<T,S>>;

	template <typename T,msize S>
	struct starray:
		collection<starray_settings<T,S>>
	{
		u32 count;

		T& operator[](msize index) { return this->mem[index]; }
		const T& operator[](msize index) const { return this->mem[index]; }
	};

	template <typename T,msize S>
	starray<T,S> create_starray()
	{
		starray<T,S> result=starray<T,S>{};
		result.mem=starray_mem<T,S>();
		return result;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter push(starray<T,S>& starr);

	template <typename T,msize S>
	typename starray<T,S>::iter push(starray<T,S>& starr,const T& val);

	template <typename T,msize S>
	typename starray<T,S>::iter peek(starray<T,S>& starr);

	template <typename T,msize S>
	typename starray<T,S>::iter pop(starray<T,S>& starr);

	template <typename T,msize S>
	typename starray<T,S>::iter get(starray<T,S>& starr,msize offset);

	template <typename T,msize S>
	typename starray<T,S>::iter get_iter(starray<T,S>& starr);

	template <typename T,msize S>
	msize get_count(starray<T,S>& starr);
}

#include "dggt_coll_starray.inl"

#define _DGGT_COLL_STARRAY_H_
#endif
