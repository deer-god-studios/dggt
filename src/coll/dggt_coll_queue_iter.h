#ifndef _DGGT_COLL_QUEUE_ITER_H_

#include "mem/dggt_mem_blk.h"

namespace dggt
{
	template <typename T>
	struct queue;

	template <typename T>
	struct queue_iter
	{
		blk<T> table;
		queue<T>* q;
		u32 current;
		u32 head;
		u32 tail;

		T& operator*();
		const T& operator*() const;
		queue_iter<T>& operator++();
		queue_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const queue_iter<T>* it);

	template <typename T>
	b32 advance(queue_iter<T>* it);

	template <typename T>
	T& get(queue_iter<T>* it);

	template <typename T>
	const T& get(const queue_iter<T>* it);

	template <typename T>
	T* get_ptr(queue_iter<T>* it);

	template <typename T>
	const T* get_ptr(const queue_iter<T>* it);
	
	template <typename T>
	blk<T> get_mem(queue_iter<T>* it);

	template <typename T>
	const blk<T> get_mem(const queue_iter<T>* it);

	template <typename T>
	b32 is_coll_valid(const queue_iter<T>* it);

	template <typename T>
	b32 is_mem_valid(const queue_iter<T>* it);

	template <typename T>
	b32 vindicate_mem(queue_iter<T>* it);
}

#define _DGGT_COLL_QUEUE_ITER_H_
#endif
