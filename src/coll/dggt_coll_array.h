#ifndef _DGGT_COLL_ARRAY_H_

#include "dggt_coll_array_iter.h"

namespace dggt
{
	template <typename T>
	struct array
	{
		blk<T> table;
		u32 count;

		array() : table(blk<T>()) { }
		T& operator[](u32 index) { return table[index]; }
		const T& operator[](u32 index) const { return table[index]; }
	};

	template <typename T,typename A>
	array<T> create_array(u32 capacity,A* allocator);

	template <typename T,typename A>
	array_iter<T> push(array<T>* arr,A* allocator);

	template <typename T,typename A>
	array_iter<T> push(array<T>* arr,const T& val,A* allocator);

	template <typename T,typename A>
	array_iter<T> pop(array<T>* arr,A* allocator);

	template <typename T>
	array_iter<T> peek(array<T>* arr);

	template <typename T>
	array_iter<T> get(array<T>* arr,u32 index);

	template <typename T,typename A>
	array_iter<T> clear(array<T>* arr,A* allocator);

	template <typename T>
	u32 get_count(const array<T>* arr);

	template <typename T>
	array_iter<T> get_iter(array<T>* arr);

	template <typename T>
	b32 contains(array<T>* arr,const T& item);

	template <typename T>
	u32 get_capacity(array<T>* arr);

	template <typename F,typename T>
	F get_load_factor(array<T>* arr);

	template <typename T,typename A>
	array_iter<T> resize(array<T>* arr,u32 newCapacity,A* allocator);
}

#include "dggt_coll_array_iter.inl"
#include "dggt_coll_array.inl"

#define _DGGT_COLL_ARRAY_H_
#endif
