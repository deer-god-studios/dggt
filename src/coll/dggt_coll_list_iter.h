#ifndef _DGGT_COLL_LIST_ITER_H_

namespace dggt
{
	template <typename T>
	struct slnode;

	template <typename T>
	struct linked_list;

	template <typename T>
	struct list_iter
	{
		slnode<T>* current;
		linked_list<T>* list;
		b32 memIsValid;

		T& operator*();
		const T& operator*() const;
		list_iter<T>& operator++();
		list_iter<T> operator++(int);
	};

	template <typename T>
	b32 is_end(const list_iter<T>* it);

	template <typename T>
	b32 advance(list_iter<T>* it);

	template <typename T>
	T& get(list_iter<T>* it);

	template <typename T>
	const T& get(const list_iter<T>* it);

	template <typename T>
	T* get_ptr(list_iter<T>* it);

	template <typename T>
	const T* get_ptr(const list_iter<T>* it);
	
	template <typename T>
	slnode<T>* get_mem(list_iter<T>* it);

	template <typename T>
	const slnode<T>* get_mem(const list_iter<T>* it);

	template <typename T>
	b32 is_coll_valid(const list_iter<T>* it);

	template <typename T>
	b32 is_mem_valid(const list_iter<T>* it);

	template <typename T>
	b32 vindicate_mem(list_iter<T>* it);
}

#define _DGGT_COLL_LIST_ITER_H_
#endif
