#ifndef _DGGT_COLL_DEQUEUE_H_

#include "dggt_coll_stack.h"
#include "dggt_coll_queue.h"
#include "dggt_coll_deque_iter.h"

namespace
{

	template <typename T>
	struct dequeue
	{
		deque_mem table;
		u32 head;
		u32 tail;
		u32 count;
	};

	template <typename T,typename A>
	deque<T> create_deque(A* a) {
		deque<T> result=deque<T>();
		deque_mem<T> table=deque_mem<T>(alloc<T>(a),2);
		result.table=table;
		return result;
	}
}

#include "dggt_coll_deque_iter.inl"

#define _DGGT_COLL_DEQUEUE_H_
#endif
