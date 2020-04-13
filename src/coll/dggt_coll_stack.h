#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_stack_iter.h"
#include "dggt_coll_collection.h"

namespace dggt
{
	template <typename T>
	struct stack:
		collection<T,stack_mem<T>,stack<T>,stack_iter<T>>
	{
		u32 count;
	};

	template <typename T,typename A>
	stack<T> create_stack(A* a,u32 capacity)
	{
		stack<T> result=stack<T>{};
		result.mem=malloc_stack_mem(a,capacity);
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	stack<T>::iter destroy_stack(stack<T>& stk,A* allocator);

	// NOTE: To see if the push succeeded use, is_coll_valid(iter).
	template <typename T,typename A>
	stack<T>::iter push(stack<T>& stk,A* alloc);
	
	template <typename T,typename A>
	stack<T>::iter push(stack<T>& stk,const T& val,A* alloc);

	// NOTE: To see if there is a possible memory leak use,
	// 		is_mem_valid(iter).  If it fails, free the memory (or not)
	// 		and call vindicate_mem(iter).
	template <typename T,typename A>
	stack<T>::iter pop(stack<T>& stk,A* alloc);

	template <typename T>
	stack<T>::iter peek(stack<T>& stk);

	template <typename T>
	stack<T>::iter get(stack<T>& stk,u32 index);

	template <typename T>
	stack<T>::iter get_iter(stack<T>& stk);

	template <typename T>
	u32 get_count(const stack<T>& stk);

	template <typename T>
	u32 get_capacity(const stack<T>& stk);

	template <typename T,typename A>
	stack<T>::iter clear(stack<T>& stk,A* alloc);

	template <typename T,typename F=float32>
	F get_load_factor(const stack<T>& stk);

	// NOTE: If the allocator fails to free the stack's old table, resize
	// 		returns an iterator pointing to the old table which may still
	// 		need to be freed but still points to the stack.  Otherwise, the 
	// 		iterator it returns points to the head of the stack and points 
	// 		to the newly resized table.  Please note in either case the 
	// 		stack's table is resized as long as the allocator succeeds in 
	// 		allocating the new table.
	template <typename T,typename A>
	stack<T>::iter resize(stack<T>& stk,u32 newCapacity,A* alloc);

	template <typename T>
	u32 get_head(const stack<T>& stk);
}

#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
