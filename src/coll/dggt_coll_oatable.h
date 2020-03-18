#ifndef _DGGT_COLL_CHNTABLE_H_

#include "dggt_coll_oatable_iter.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	global const fl32 TABLE_EMPTY=0;
	global const fl32 TABLE_OCCUPIED=1;
	global const fl32 TABLE_DELETED=2;

	template <typename K,typename V>
	struct oatable
	{
		flag_mem flagTable;
		oatable_mem<K,V> table;
		u32 count;

		oatable_iter<K,V>& operator[](const K& index);
		const oatable_iter<K,V>& operator[](const K& index) const;
	};

	template <typename K,typename V,typename A>
	oatable<K,V> create_oatable(A* allocator);

	template <typename K,typename V,typename A>
	oatable_iter<K,V> insert(oatable<K,V>* table,const K& key,A* allocator);

	template <typename K,typename V,typename A>
	oatable_iter<K,V> insert(oatable<K,V>* table,const K& key,const V& val,A* allocator);

	template <typename K,typename V,typename A>
	oatable_iter<K,V> clear(oatable<K,V>* table,A* allocator);

	template <typename K,typename V>
	oatable_iter<K,V> search(oatable<K,V>* table,const K& key);

	template <typename K,typename V>
	const oatable_iter<K,V> search(const oatable<K,V>* table,const K& key);

	template <typename K,typename V,typename A>
	oatable_iter<K,V> remove(oatable<K,V>* table,const K& key,A* allocator);

	template <typename F,typename K,typename V>
	F get_load_factor(const oatable<K,V>* table);

	template <typename K,typename V>
	u32 get_count(const oatable<K,V>* table);

	template <typename K,typename V>
	u32 get_capacity(const oatable<K,V>* table);

	template <typename K,typename V,typename A>
	oatable_iter<K,V> resize(oatable<K,V>* table,u32 newSize,A* allocator);

	template <typename K,typename V>
	oatable_iter<K,V> get_iter(oatable<K,V>* table);
}

#include "dggt_coll_oatable_iter.inl"
#include "dggt_coll_oatable.inl"

#define _DGGT_COLL_CHNTABLE_H_
#endif
