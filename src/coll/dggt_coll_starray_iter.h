#ifndef _DGGT_COLL_STARRAY_ITER_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T,msize S>
	struct starray;

	template <typename T,msize S>
	using starray_mem=T[S];

	template <typename T,msize S>
	struct starray_iter
	{
		starray_mem<T,S> starrayMem;
		msize currentOffset;
		starray<T,S>* starr;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		starray_iter<T>& operator++();
		starray_iter<T> operator++(int);
	};

	template <typename T,msize S>
	b32 is_end(const starray_iter<T,S>& it);

	template <typename T,msize S>
	b32 advance(starray_iter<T,S>& it);

	template <typename T,msize S>
	T& get(starray_iter<T,S>& it);

	template <typename T,msize S>
	const T& get(const starray_iter<T,S>& it);

	template <typename T,msize S>
	T* get_ptr(starray_iter<T,S>& it);

	template <typename T,msize S>
	const T* get_ptr(const starray_iter<T,S>& it);
	
	template <typename T,msize S>
	starray_mem<T,S> get_mem(starray_iter<T,S>& it);

	template <typename T,msize S>
	const starray_mem<T,S> get_mem(const starray_iter<T,S>& it);

	template <typename T,msize S>
	b32 is_coll_valid(const starray_iter<T,S>& it);

	template <typename T,msize S>
	b32 is_mem_valid(const starray_iter<T,S>& it);

	template <typename T,msize S>
	b32 vindicate_mem(starray_iter<T,S>& it);
}

#define _DGGT_COLL_STARRAY_ITER_H_
#endif
