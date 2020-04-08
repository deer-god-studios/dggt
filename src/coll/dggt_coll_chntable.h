#ifndef _DGGT_COLL_HASH_TABLE_H_

#include "dggt_coll_chntable_iter.h"

namespace dggt
{
	template <typename K,typename V>
	struct chntable
	{
		chntable_mem<K,V> table;
		u32 count;

		chntable_iter<K,V> operator[](const K& key);
		const chntable_iter<K,V> operator[](const K& key) const;
	};

	template <typename K,typename V,typename A>
	chntable<K,V> create_chntable(A* allocator);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> destroy_chntable(chntable<K,V>* table,A* allocator);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> insert(chntable<K,V>* table,const K& key,A* allocator);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> insert(chntable<K,V>* table,const K& key,const V& val,A* allocator);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> clear(chntable<K,V>* table,A* allocator);

	template <typename K,typename V>
	chntable_iter<K,V> search(chntable<K,V>* table,const K& key);

	template <typename K,typename V>
	const chntable_iter<K,V> search(const chntable<K,V>* table,const K& key);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> remove(chntable<K,V>* table,const K& key,A* allocator);

	template <typename F,typename K,typename V>
	F get_load_factor(const chntable<K,V>* table);

	template <typename K,typename V>
	u32 get_count(const chntable<K,V>* table);

	template <typename K,typename V>
	u32 get_capacity(const chntable<K,V>* table);

	template <typename K,typename V,typename A>
	chntable_iter<K,V> resize(chntable<K,V>* table,u32 newSize,A* allocator);

	template <typename K,typename V>
	chntable_iter<K,V> get_iter(chntable<K,V>* table);
}

#include "dggt_coll_chntable_iter.inl"
#include "dggt_coll_chntable.inl"

#define _DGGT_COLL_HASH_TABLE_H_
#endif
