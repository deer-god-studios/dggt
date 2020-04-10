#ifndef _DGGT_COLL_STACK_ITER_H_

#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	struct stack;

	template <typename T>
	using stack_mem=array<T>;

	template <typename T>
	struct stack_iter:
		iterator<T,stack_mem<T>,stack<T>>
	{
		msize current;

		stack_iter(coll_type* coll)
			: iterator(coll) { }
		stack_iter(const mem_type<T>& mem,coll_type* coll,
				msize current=mem.size-1)
			: iterator(mem,coll,current) { }
		T* operator->() { return (T*)mem; }
		const T* operator->() const { return (T*)mem; }

		b32 is_end() const { return dggt::is_end(*this); }
		T& operator*() { return get(*this); }
		const T& operator*() const { return get(*this); }

		stack_iter<T>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				advance(*this);
			}
			return *this;
		}

		stack_iter<T> operator++(int)
		{
			stack_iter<T> result=*this;
			this->operator++();
			return result;
		}

		explicit operator array_mem<T>() { return mem; }
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
}

#define _DGGT_COLL_STACK_ITER_H_
#endif
