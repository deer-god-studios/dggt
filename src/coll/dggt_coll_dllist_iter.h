#ifndef _DGGT_COLL_DLLIST_ITER_H_

#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T>
	struct dlnode;

	template <typename T>
	struct dlchain;

	template <typename T>
	struct dllist;

	template <typename T>
	using dllist_mem=dlchain<T>;

	template <typename T>
	struct dllist_iter:
		iterator<T,dllist_mem<T>,dllist<T>>
	{
		dlnode<T>* current;
		dlnode<T>* prev;

		b32 is_end() const { return dggt::is_end(*this); }
		b32 is_begin() const { return dggt::is_begin(*this); }
		T& operator*() { return get(*this); }
		const T& operator*() const { return get(*this); }
		dllist_iter<T>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				advance(*this);
			}
			return *this;
		}
		dllist_iter<T> operator++(int)
		{
			dllist_iter<T> result=*this;
			this->operator++();
			return result;
		}
		dllist_iter<T>& operator--()
		{
			if (!dggt::is_begin(*this))
			{
				decrement(*this);
			}
			return *this;
		}
		dllist_iter<T> operator--(int)
		{
			dllist_iter<T> result=*this;
			this->operator--();
			return result;
		}
	};

	template <typename T>
	b32 is_end(const dllist_iter<T>& it);

	template <typename T>
	b32 is_begin(const dllist_iter<T>& it);

	template <typename T>
	b32 advance(dllist_iter<T>& it);

	template <typename T>
	b32 decrement(dllist_iter<T>& it);

	template <typename T>
	T& get(dllist_iter<T>& it);

	template <typename T>
	const T& get(const dllist_iter<T>& it);

	template <typename T>
	T* get_ptr(dllist_iter<T>& it);

	template <typename T>
	const T* get_ptr(const dllist_iter<T>& it);
	
	template <typename T>
	dllist_iter<T>::mem_type get_mem(dllist_iter<T>& it);

	template <typename T>
	const dllist_iter<T>::mem_type get_mem(const dllist_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const dllist_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(dllist_iter<T>& it);
}


#define _DGGT_COLL_DLLIST_ITER_H_
#endif
