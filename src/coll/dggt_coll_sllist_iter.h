#ifndef _DGGT_COLL_SLLIST_ITER_H_

namespace dggt
{
	template <typename T>
	struct slnode;

	template <typename T>
	struct sllist;

	template <typename T>
	struct sllist_iter
	{
		slnode<T>* current;
		sllist<T>* list;
		b32 memIsValid;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		sllist_iter<T>& operator++();
		sllist_iter<T> operator++(int);
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
	slnode<T>* get_mem(sllist_iter<T>& it);

	template <typename T>
	const slnode<T>* get_mem(const sllist_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const sllist_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const sllist_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(sllist_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,sllist_iter<T>& it);
}

#define _DGGT_COLL_SLLIST_ITER_H_
#endif
