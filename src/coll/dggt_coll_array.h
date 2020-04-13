#ifndef _DGGT_COLL_ARRAY_H_

#include "dggt_coll_array_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	using array_settings=coll_settings<T,array_mem<T>,array<T>,array_iter<T>>;

	template <typename T>
	struct array:
		collection<array_settings<T>>
	{
		u32 count;

		array() : collection<array_settings<T>>() { }

		T& operator[](msize index) { return this->mem[index]; }
		const T& operator[](msize index) const { return this->mem[index]; }
	};

	template <typename T,typename A>
	array<T> create_array(A* allocator,msize capacity=2);

	template <typename T,typename A>
	typename array<T>::iter destroy_array(array<T>& arr,A* allocator);

	template <typename T,typename A>
	typename array<T>::iter push(array<T>& arr,A* allocator);

	template <typename T,typename A>
	typename array<T>::iter push(array<T>& arr,const T& val,A* allocator);

	template <typename T,typename A>
	typename array<T>::iter pop(array<T>& arr,A* allocator);

	template <typename T>
	typename array<T>::iter peek(array<T>& arr);

	template <typename T>
	typename array<T>::iter get(array<T>& arr,u32 index);

	template <typename T,typename A>
	typename array<T>::iter clear(array<T>& arr,A* allocator);

	template <typename T>
	u32 get_count(const array<T>& arr);

	template <typename T>
	typename array<T>::iter get_iter(array<T>& arr);

	template <typename T>
	b32 contains(array<T>& arr,const T& item);

	template <typename T>
	u32 get_capacity(array<T>& arr);

	template <typename T,typename F=float32>
	F get_load_factor(array<T>& arr);

	template <typename T,typename A>
	typename array<T>::iter resize(array<T>& arr,u32 newCapacity,A* allocator);
}

#include "dggt_coll_array.inl"

#define _DGGT_COLL_ARRAY_H_
#endif
