#ifndef _DGGT_COLL_IDX_ITER_H_

#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	struct idxtable;

	template <typename T>
	using idxtable_mem=array<T>

	typedef array<flag32> idxtable_flag_mem;

	template <typename T>
	struct idxtable_iter
	{
		idxtable_mem<T> tableMem;
		idxtable_flag_mem<T> flagMem;
		u32 currentHandle;
		fl32 currentFlag;
		idxtable_iter* table;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		idxtable_iter<T>& operator++();
		idxtable_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const idxtable_iter<T>& it);

	template <typename T>
	b32 advance(idxtable_iter<T>& it);

	template <typename T>
	T& get(idxtable_iter<T>& it);

	template <typename T>
	const T& get(const idxtable_iter<T>& it);

	template <typename T>
	T* get_ptr(idxtable_iter<T>& it);

	template <typename T>
	const T* get_ptr(const idxtable_iter<T>& it);
	
	template <typename T>
	idxtable_mem<T> get_mem(idxtable_iter<T>& it);

	template <typename T>
	const idxtable_mem<T> get_mem(const idxtable_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const idxtable_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const idxtable_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(idxtable_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,idxtable_iter<T>& it);

	template <typename T>
	u32 get_current(const idxtable_iter<T>& it);
}

#define _DGGT_COLL_IDX_ITER_H_
#endif
