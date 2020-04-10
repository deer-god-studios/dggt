#ifndef _DGGT_COLL_IDX_ITER_H_

#include "dggt_coll_array.h"
#include "dggt_coll_stack.h"
#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T>
	struct idxtable;

	template <typename T>
	using idxmem=stack_mem<T>;

	template <typename T>
	struct idxtable_mem;

	template <typename T>
	struct idxtable_iter:
		iterator<T,idxtable_mem<T>,idxtable<T>>
	{
		msize current;

		b32 is_end() const { return dggt::is_end(*this); }
		T& operator*() { return get(*this); }
		const T& operator*() const { return get(*this); }
		idxtable_iter<T>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				advance(*this);
			}
			return *this;
		}
		idxtable_iter<T> operator++(int)
		{
			idxtable_iter<T> result=*this;
			this->operator++();
			return result;
		}
		idxtable_iter<T>& operator--()
		{
			if (!dggt::is_end(*this))
			{
				decrement(*this);
			}
			return *this;
		}
		idxtable_iter<T> operator--(int)
		{
			idxtable_iter<T> result=*this;
			this->operator--();
			return result;
		}
	};

	template <typename T>
	b32 is_end(const idxtable_iter<T>& it);

	template <typename T>
	b32 advance(idxtable_iter<T>& it);

	template <typename T>
	b32 decrement(idxtable_iter<T>& it);

	template <typename T>
	T& get(idxtable_iter<T>& it);

	template <typename T>
	const T& get(const idxtable_iter<T>& it);

	template <typename T>
	T* get_ptr(idxtable_iter<T>& it);

	template <typename T>
	const T* get_ptr(const idxtable_iter<T>& it);
}

#define _DGGT_COLL_IDX_ITER_H_
#endif
