#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_stack_iter.h"

namespace dggt
{
	template <typename T>
	struct stack
	{
		T* table;
		u32 count;

		T& operator[](u32 index);
		const T& operator[](u32 index) const;
	};

	template <typename T,typename A>
	stack<T> create_stack(A* a) { return stack<T>{alloc<T>(a,2),0}; }

	template <typename T,typename A>
	stack_iter<T> destroy_stack(stack<T>* stk,A* allocator);

	// NOTE: To see if the push succeeded use, is_coll_valid(iter).
	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,A* alloc);
	
	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,const T& val,A* alloc);

	// NOTE: To see if there is a possible memory leak use,
	// 		is_mem_valid(iter).  If it fails, free the memory (or not)
	// 		and call vindicate_mem(iter).
	template <typename T,typename A>
	stack_iter<T> pop(stack<T>* stk,A* alloc);

	template <typename T>
	stack_iter<T> peek(stack<T>* stk);

	template <typename T>
	stack_iter<T> get(stack<T>* stk,u32 index);

	template <typename T>
	stack_iter<T> get_iter(stack<T>* stk,u32 index=0);

	template <typename T>
	u32 get_count(const stack<T>* stk);

	template <typename T>
	u32 get_capacity(const stack<T>* stk);

	template <typename T,typename A>
	stack_iter<T> clear(stack<T>* stk,A* alloc);

	template <typename T,typename F=float32>
	F get_load_factor(const stack<T>* stk);

	// NOTE: If the allocator fails to free the stack's old table, resize
	// 		returns an iterator pointing to the old table which may still
	// 		need to be freed but still points to the stack.  Otherwise, the 
	// 		iterator it returns points to the head of the stack and points 
	// 		to the newly resized table.  Please note in either case the 
	// 		stack's table is resized as long as the allocator succeeds in 
	// 		allocating the new table.
	template <typename T,typename A>
	stack_iter<T> resize(stack<T>* stk,u32 newCapacity,A* alloc);

	template <typename T>
	u32 get_head(const stack<T>* stk);
}

#include "dggt_coll_stack_iter.inl"
#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
