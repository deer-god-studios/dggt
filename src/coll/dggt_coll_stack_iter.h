#ifndef _DGGT_COLL_STACK_ITER_H_

namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	struct stack_iter
	{
		blk<T> table;
		u32 current;
		stack<T>* stk;

		T& operator*();
		const T& operator*() const;
		stack_iter<T>& operator++();
		stack_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const stack_iter<T>& it);

	template <typename T>
	b32 advance(stack_iter<T>& it);

	template <typename T>
	T& get(stack_iter<T>& it);

	template <typename T>
	const T& get(const stack_iter<T>& it);

	template <typename T>
	T* get_ptr(stack_iter<T>& it);

	template <typename T>
	const T* get_ptr(const stack_iter<T>& it);
	
	template <typename T>
	T* get_mem(stack_iter<T>& it);

	template <typename T>
	const slnode<T>* get_mem(const stack_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const stack_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const stack_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(stack_iter<T>& it);
}

#define _DGGT_COLL_STACK_ITER_H_
#endif
