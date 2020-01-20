#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_iter.h"

namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	using stack_iter=iter<T,stack<T>,blk<T>>;

	template <typename T>
	struct iter<T,stack<T>,blk<T>>
	{
		u32 current;
		blk<T> table;
		stack<T>* stk;

		b32 is_end() const;
		b32 next();
		T& get();
		const T& get() const;
		T* get_ptr();
		const T* get_ptr() const;
		blk<T> get_mem();
		const blk<T> get_mem() const;
		b32 is_coll_valid() const;
		b32 is_mem_valid() const;
		b32 vindicate_mem();
	};

	template <typename T>
	struct stack
	{
		blk<T> table;
		u32 count;

		T& operator[](u32 index);
		const T& operator[](u32 index) const;
	};

	template <typename T,typename A>
	stack<T> create_stack(A* alloc) { return stack<T>{alloc->template alloc<T>(2),0}; }

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
	u32 get_head(stack<T>* stk);
}

#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
