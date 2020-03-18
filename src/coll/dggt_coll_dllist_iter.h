#ifndef _DGGT_COLL_DLLIST_ITER_H_

namespace dggt
{
	template <typename T>
	struct dlnode;

	template <typename T>
	struct dllist;

	template <typename T>
	struct dllist_iter
	{
		dlnode<T>* current;
		dllist<T>* list;
		b32 memIsValid;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		dllist_iter<T>& operator++();
		dllist_iter<T> operator++(int);
		dllist_iter<T>& operator--();
		dllist_iter<T> operator--(int);
	};

	template <typename T>
	b32 is_end(const dllist_iter<T>& it);

	template <typename T>
	b32 advance(dllist_iter<T>& it);

	template <typename T>
	T& get(dllist_iter<T>& it);

	template <typename T>
	const T& get(const dllist_iter<T>& it);

	template <typename T>
	T* get_ptr(dllist_iter<T>& it);

	template <typename T>
	const T* get_ptr(const dllist_iter<T>& it);
	
	template <typename T>
	slnode<T>* get_mem(dllist_iter<T>& it);

	template <typename T>
	const slnode<T>* get_mem(const dllist_iter<T>& it);

	template <typename T>
	b32 is_coll_valid(const dllist_iter<T>& it);

	template <typename T>
	b32 is_mem_valid(const dllist_iter<T>& it);

	template <typename T>
	b32 vindicate_mem(dllist_iter<T>& it);

	template <typename T,typename A>
	b32 free(A* a,dllist_iter<T>& it);
}


#define _DGGT_COLL_DLLIST_ITER_H_
#endif
