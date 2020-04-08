#ifndef _DGGT_COLL_QUEUE_H_

#include "dggt_coll_queue_iter.h"

namespace dggt
{
	template <typename T>
	struct queue
	{
		blk<T> table;
		u32 count;
		u32 head;
		u32 tail;

		T& operator[](u32 index);
		const T& operator[](u32 index) const;
	};
	
	template <typename T,typename A>
	queue<T> create_queue(A* allocator)
	{
		return queue<T>{alloc<T>(allocator,2),0,0,0};
	}

	template <typename T,typename A>
	queue_iter<T> destroy_queue(queue<T>* q,A* allocator);

	template <typename T,typename A>
	queue_iter<T> enqueue(queue<T>* q,A* alloc);

	template <typename T,typename A>
	queue_iter<T> enqueue(queue<T>* q,const T& val,A* alloc);

	template <typename T,typename A>
	queue_iter<T> dequeue(queue<T>* q,A* alloc);

	template <typename T,typename A>
	queue_iter<T> clear(queue<T>* q,A* alloc);

	template <typename T>
	queue_iter<T> get(queue<T>* q,u32 index=0);

	template <typename T>
	u32 get_count(const queue<T>* q);

	template <typename T>
	u32 get_capacity(const queue<T>* q);

	template <typename T>
	queue_iter<T> get_iter(queue<T>* q,u32 index=0);

	template <typename T,typename F=float32>
	F get_load_factor(const queue<T>* q);

	template <typename T>
	u32 get_head(const queue<T>* q);

	template <typename T>
	u32 get_tail(const queue<T>* q);

	// NOTE: If the allocator fails to free the queue's old table, resize
	// 		returns an iterator pointing to the old table which may still
	// 		need to be freed but still points to the queue.  Otherwise, the 
	// 		iterator it returns points to the head of the queue and points 
	// 		to the newly resized table.  Please note in either case the 
	// 		queue's table is resized as long as the allocator succeeds in 
	// 		allocating the new table.
	template <typename T,typename A>
	queue_iter<T> resize(queue<T>* q,u32 newCapacity,A* alloc);

	template <typename T>
	b32 is_index_valid(queue<T>* q,u32 index);
}

#include "dggt_coll_queue_iter.inl"
#include "dggt_coll_queue.inl"

#define _DGGT_COLL_QUEUE_H_
#endif
