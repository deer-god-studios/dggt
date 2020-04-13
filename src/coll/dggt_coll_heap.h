#ifndef _DGGT_COLL_HEAP_H_

#include "dggt_coll_array.h"
#include "dggt_coll_collection.h"
#include "dggt_coll_heap_iter.h"

namespace dggt
{
	template <typename T>
	struct heap:
		collection<T,heap_mem<T>,heap<T>,heap_iter<T>>
	{
		u32 count;
	};

	template <typename T,typename A>
	heap<T> create_heap(A* allocator,msize capacity);

	template <typename T,typename A>
	heap<T> create_heap(A* allocator,array<T>& arr);

	template <typename T,typename A>
	heap<T> create_max_heap(A* allocator,array<T>& arr);

	template <typename T,typename A>
	heap<T> create_min_heap(A* allocator,array<T>& arr);

	template <typename T,typename A>
	heap<T>::iter destroy_heap(heap<T>& hp,A* allocator);

	template <typename T,typename A>
	heap<T>::iter push(heap<T>& hp,A* allocator);

	template <typename T,typename A>
	heap<T>::iter push(heap<T>& hp,const T& val,A* allocator);

	template <typename T,typename A>
	heap<T>::iter pop(heap<T>& hp,A* allocator);

	template <typename T>
	heap<T>::iter peek(heap<T>& hp);

	template <typename T>
	heap<T>::iter get(heap<T>& hp,u32 index);

	template <typename T,typename A>
	heap<T>::iter clear(heap<T>& hp,A* allocator);

	template <typename T>
	u32 get_count(const heap<T>& hp);

	template <typename T>
	heap<T>::iter get_iter(heap<T>& hp);

	template <typename T>
	b32 contains(heap<T>& hp,const T& item);

	template <typename T>
	u32 get_capacity(heap<T>& hp);

	template <typename T,typename F=float32>
	F get_load_factor(heap<T>& hp);

	template <typename T>
	heap<T>::iter get_parent(heap<T>& hp,heap<T>::iter& node);

	template <typename T>
	heap<T>::iter get_left_child(heap<T>& hp,heap<T>::iter& node);

	template <typename T>
	heap<T>::iter get_right_child(heap<T>& hp,heap<T>::iter& node);

	template <typename T,typename A>
	heap<T>::iter resize(heap<T>& hp,u32 newCapacity,A* allocator);

	template <typename T,typename A>
	heap<T>::iter insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter max_heap_insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter min_heap_insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter heapify(heap<T>& hp,heap<T>::iter& node);
	
	template <typename T,typename A>
	heap<T>::iter max_heapify(heap<T>& hp,heap<T>::iter& node);

	template <typename T,typename A>
	heap<T>::iter min_heapify(heap<T>& hp,heap<T>::iter& node);
}

#include "dggt_coll_heap.inl"

#define _DGGT_COLL_HEAP_H_
#endif
