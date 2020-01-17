#ifndef _DGGT_COLL_STACK_H_

#include "dggt_coll_iter.h"
namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	using stack_iter=iter<T,stack<T>>;

	template <typename T>
	struct stack_iter<T>
	{
		u32 current;
		u32 capacity;
		stack<T>* stk;

		b32 is_end() const;
		b32 next();
		T& get();
		const T& get() const;
		T* get_ptr();
		const T* get_ptr() const;
		blk<T> get_table();
		const blk<T> get_table() const;
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
	stack_iter<T> push(stack<T>* stk,A* alloc);
	
	template <typename T,typename A>
	stack_iter<T> push(stack<T>* stk,const T& val,A* alloc);

	template <typename T>
	stack_iter<T> get(stack<T>* stk,u32 index);

	template <typename T>
	stack_iter<T> get_iter(stack<T>* stk);

	template <typename T>
	u32 get_count(const stack<T>* stk);

	template <typename T>
	u32 get_capacity(const stack<T>* stk);

	template <typename T,typename F=float32>
	F get_load_factor(const stack<T>* stk);

	template <typename T,typename A>
	b32 resize(const stack<T>* stk,u32 newCapacity,A* alloc);
}

#include "dggt_coll_stack.inl"

#define _DGGT_COLL_STACK_H_
#endif
