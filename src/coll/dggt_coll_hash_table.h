#ifndef _DGGT_COLL_HASH_TABLE_H_

#include "dggt_coll_table_iter.h"

namespace dggt
{
	template <typename K>
	u32 prehash(const K& key);

	template <>
	u32 prehash(const u32& key);

	template <typename K,typename V>
	struct hash_table
	{
		table_mem<K,V> table;
		u32 count;

		table_iter<K,V> operator[](const K& key);
		const table_iter<K,V> operator[](const K& key) const;
	};

	template <typename K,typename V,typename A>
	hash_table<K,V> create_hash_table(A* allocator);

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key,A* allocator);

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key,const V& val,A* allocator);

	template <typename K,typename V,typename A>
	table_iter<K,V> clear(hash_table<K,V>* table,A* allocator);

	template <typename K,typename V>
	table_iter<K,V> search(hash_table<K,V>* table,const K& key);

	template <typename K,typename V>
	const table_iter<K,V> search(const hash_table<K,V>* table,const K& key);

	template <typename K,typename V,typename A>
	table_iter<K,V> remove(hash_table<K,V>* table,const K& key,A* allocator);

	template <typename F,typename K,typename V>
	F get_load_factor(const hash_table<K,V>* table);

	template <typename K,typename V>
	u32 get_count(const hash_table<K,V>* table);

	template <typename K,typename V>
	u32 get_capacity(const hash_table<K,V>* table);

	template <typename K,typename V,typename A>
	table_iter<K,V> resize(hash_table<K,V>* table,u32 newSize,A* allocator);

	template <typename K,typename V>
	table_iter<K,V> get_iter(hash_table<K,V>* table);
}

#include "dggt_coll_table_iter.inl"
#include "dggt_coll_hash_table.inl"

#define _DGGT_COLL_HASH_TABLE_H_
#endif
