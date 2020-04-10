#ifndef _DGGT_COLL_ARRAY_ITER_H_

#include "types/dggt_types.h"
#include "mem/dggt_mem_page.h"
#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T>
	struct array;

	template <typename T>
	using array_mem=page<T>;

	template <typename T>
	struct array_iter:iterator<T,array_mem<T>,array<T>>
	{
		msize current;

		array_iter(coll_type* coll)
			: iterator(coll) { }
		array_iter(const mem_type& mem, coll_type* coll,msize current=0)
			: iterator(mem,coll),this->current(current) { }
		array_iter() : iterator(),this->current(0) { }

		T* operator->() { return (T*)mem; }
		const T* operator->() const { return (T*)mem; }

		b32 is_end() const { return dggt::is_end(*this); }
		T& operator*() { return get(*this); }
		const T& operator*() const { return get(*this); }

		array_iter<T>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				advance(*this);
			}
			return *this;
		}

		array_iter<T> operator++(int)
		{
			array_iter<T> result=*this;
			this->operator++();
			return result;
		}

		explicit operator array_mem<T>() { return mem; }
	};

	template <typename T>
	b32 is_end(const array_iter<T>& it);

	template <typename T>
	b32 advance(array_iter<T>& it);

	template <typename T>
	T& get(array_iter<T>& it);

	template <typename T>
	const T& get(const array_iter<T>& it);

	template <typename T>
	T* get_ptr(array_iter<T>& it);

	template <typename T>
	const T* get_ptr(const array_iter<T>& it);
}

#define _DGGT_COLL_ARRAY_ITER_H_
#endif
