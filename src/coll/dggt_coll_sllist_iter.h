#ifndef _DGGT_COLL_SLLIST_ITER_H_

#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T>
	struct slnode;

	template <typename T>
	struct sllist;

	template <typename T>
	struct slchain;

	template <typename T>
	using sllist_mem=slchain<T>;

	template <typename T>
	struct sllist_iter:
		iterator<T,sllist_mem<T>,sllist<T>>
	{
		slnode<T>* current;

		sllist_iter():iterator() { }
		sllist_iter(coll_type* coll):iterator(coll) { }
		sllist_iter(const mem_type& mem,coll_type* coll):iterator(mem,coll) { }
		sllist_iter(const mem_type& mem,coll_type* coll,slnode<T>* current)
			: sllist_iter(mem,coll),this->current(current) { }

		b32 is_end() const { return dggt::is_end(*this); }
		T& operator*() { return get(*this); }
		const T& operator*() const { return get(*this); }
		sllist_iter<T>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				advance(*this);
			}
			return *this;
		}
		sllist_iter<T> operator++(int)
		{
			sllist_iter<T>& result=*this;
			if (!is_end(*this))
			{
				advance(*this);
			}
			return result;
		}
	};

	template <typename T>
	b32 is_end(const sllist_iter<T>& it);

	template <typename T>
	b32 advance(sllist_iter<T>& it);

	template <typename T>
	T& get(sllist_iter<T>& it);

	template <typename T>
	const T& get(const sllist_iter<T>& it);

	template <typename T>
	T* get_ptr(sllist_iter<T>& it);

	template <typename T>
	const T* get_ptr(const sllist_iter<T>& it);
	
	template <typename T>
	b32 is_mem_valid(const sllist_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(sllist_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,sllist_iter<T>& it);
}

#define _DGGT_COLL_SLLIST_ITER_H_
#endif
