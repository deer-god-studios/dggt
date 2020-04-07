#ifndef _DGGT_COLL_IDX_ITER_H_

#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	struct idx_table;

	template <typename T>
	using idx_table_mem=array<T>

	typedef array<flag32> idx_table_flag_mem;

	template <typename T>
	struct idx_table_iter
	{
		idx_table_mem<T> tableMem;
		idx_table_flag_mem<T> flagMem;
		u32 currentHandle;
		fl32 currentFlag;
		idx_table_iter* table;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		idx_table_iter<T>& operator++();
		idx_table_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const idx_table_iter<T>& it);

	template <typename T>
	b32 advance(idx_table_iter<T>& it);

	template <typename T>
	T& get(idx_table_iter<T>& it);

	template <typename T>
	const T& get(const idx_table_iter<T>& it);

	template <typename T>
	T* get_ptr(idx_table_iter<T>& it);

	template <typename T>
	const T* get_ptr(const idx_table_iter<T>& it);
	
	template <typename T>
	idx_table_mem<T> get_mem(idx_table_iter<T>& it);

	template <typename T>
	const idx_table_mem<T> get_mem(const idx_table_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const idx_table_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const idx_table_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(idx_table_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,idx_table_iter<T>& it);

	template <typename T>
	u32 get_current(const idx_table_iter<T>& it);
}

#define _DGGT_COLL_IDX_ITER_H_
#endif
