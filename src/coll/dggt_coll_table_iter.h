#ifndef _DGGT_COLL_TABLE_ITER_H_

#include "dggt_coll_table_pair.h"
#include "dggt_coll_linked_list.h"

namespace dggt
{
	template <typename K,typename V>
	struct hash_table;

	template <typename K,typename V>
	using table_bucket=linked_list<table_pair<K,V>>;

	template <typename K,typename V>
	using bucket_iter=list_iter<table_pair<K,V>>;

	template <typename K,typename V>
	using table_mem=blk<table_bucket<K,V>>;

	template <typename K,typename V>
	using table_node=slnode<table_pair<K,V>>;

	template <typename K,typename V>
	struct table_iter
	{
		u32 currentIndex;
		table_bucket<K,V>* currentBucket;
		table_node<K,V>* currentNode;
		table_mem<K,V> table;
		hash_table<K,V>* hashTable;

		b32 is_end() const;
		table_pair<K,V>& operator*();
		const table_pair<K,V>& operator*() const;
		table_iter<K,V>& operator++();
		table_iter<K,V> operator++(int);
	};

	template <typename K,typename V>
	b32 is_end(const table_iter<K,V>& it);

	template <typename K,typename V>
	b32 advance(table_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>& get(table_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>& get(const table_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>* get_ptr(table_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>* get_ptr(const table_iter<K,V>& it);
	
	template <typename K,typename V>
	table_mem<K,V> get_mem(table_iter<K,V>& it);

	template <typename K,typename V>
	const table_mem<K,V> get_mem(const table_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_coll_valid(const table_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_mem_valid(const table_iter<K,V>& it);

	template <typename K,typename V>
	b32 vindicate_mem(table_iter<K,V>& it);

	template <typename K,typename V,typename A>
	b32 free(A* a,table_iter<K,V>& it);
}

#define _DGGT_COLL_TABLE_ITER_H_
#endif
