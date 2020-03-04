#ifndef _DGGT_COLL_ARRAY_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T>
	struct array;

	template <typename T>
	array_iter
	{
		T* table;
		u32 count;
		u32 current;
		array<T>* arr;

		T& operator*();
		const T& operator*() const;
		stack_iter<T>& operator++();
		stack_iter<T>& operator++(int);
	};

	template <typename T>
	b32 is_end(const array_iter<T>* it);

	template <typename T>
	b32 advance(array_iter<T>* it);

	template <typename T>
	T& get(array_iter<T>* it);

	template <typename T>
	const T& get(const array_iter<T>* it);

	template <typename T>
	T* get_ptr(array_iter<T>* it);

	template <typename T>
	const T* get_ptr(const array_iter<T>* it);
	
	template <typename T>
	T* get_mem(array_iter<T>* it);

	template <typename T>
	const slnode<T>* get_mem(const array_iter<T>* it);

	template <typename T>
	b32 is_coll_valid(const array_iter<T>* it);

	template <typename T>
	b32 is_mem_valid(const array_iter<T>* it);

	template <typename T>
	b32 vindicate_mem(array_iter<T>* it);


	template <typename T>
	struct array
	{
		T* table;
		u32 count;

		T& operator[](u32 index) { return table[index]; }
		const T& operator[](u32 index) const { return table[index]; }
	};
}

#define _DGGT_COLL_ARRAY_H_
#endif
