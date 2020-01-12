#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_common.h"

// TODO: Could the stack use something like a 'heap allocator' or
// 		'heap free_store'?  Where every entry is double the size of the
// 		previous....?
namespace dggt
{
	template <typename T>
	struct stack_iter
	{
		blk<T> mem;
		u32 current;
		u32 count;

		stack_iter();
		stack_iter(blk<T> mem,u32 begin,u32 count);

		b32 is_end() const;
		void advance();
		T& get();
		const T& get();

		T* node();
		const T* node() const;
	};

	template <typename T>
	struct stack
	{
		blk<T> mem;
		u32 count;
		u32 capacity;
	};

	template <typename T>
	stack<T> create_stack(blk<T> mem);
	template <typename T,alloc_t A>
	stack<T> create_stack(allocator<A>* alloc,u32=2);

	template <typename T,alloc_t A>
	stack_iter<T> push(stack<T>* stk,allocator<A>* alloc=0);
	template <typename T,alloc_t A>
	stack_iter<T> push(stack<T>* stk,const T& val,allocator<T>* alloc=0);

	template <typename T,alloc_t A>
	stack_iter<T> pop(stack<T>* stk,allocator<T>* alloc=0);

	template <typename T>
	stack_iter<T> peek(stack<T>* stk);

	template <typename T>
	stack_iter<T> get(stack<T>* stk,u32 index);

	template <typename T>
	stack_iter<T> begin_iter(stack<T>* stk);

	template <typename T>
	b32 is_begin_iter(stack<T>* stk,list_iter<T> iter);
	template <typename T>
	b32 is_end_iter(stack<T>* stk,list_iter<T> iter);
}

#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
