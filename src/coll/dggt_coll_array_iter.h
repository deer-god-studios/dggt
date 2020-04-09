#ifndef _DGGT_COLL_ARRAY_ITER_H_

#include "types/dggt_types.h"
#include "mem/dggt_mem_blk.h"
#include "dggt_coll_iter.h"

namespace dggt
{
	template <typename T>
	struct array;

	template <typename T>
	using array_mem=blk<T>;

	template <typename T>
	struct array_iter:iter<T,array_mem<T>,array<T>>
	{
		u32 current;

		array_iter(MemType mem,CollType* coll);

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		array_iter<T>& operator++();
		array_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const array_iter<T>& it);

	template <typename T>
	b32 advance(array_iter<T>& it);

	template <typename T>
	T& get(array_iter<T>& it);

	template <typename T>
	const T& get(const array_iter<T>& it);

	template <typename T>
	T* get_ptr(array_iter<T>& it);

	template <typename T>
	const T* get_ptr(const array_iter<T>& it);
	
	template <typename T>
	array_mem<T> get_mem(array_iter<T>& it);

	template <typename T>
	const array_mem<T> get_mem(const array_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const array_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const array_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(array_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,array_iter<T>& it);
}

#define _DGGT_COLL_ARRAY_ITER_H_
#endif
