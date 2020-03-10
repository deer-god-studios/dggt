#ifndef _DGGT_COLL_TABLE_ITER_H_

#include "dggt_coll_table_pair.h"
#include "dggt_coll_sllist.h"

namespace dggt
{
	template <typename K,typename V>
	struct chntable;

	template <typename K,typename V>
	using table_bucket=sllist<table_pair<K,V>>;

	template <typename K,typename V>
	using bucket_iter=sllist_iter<table_pair<K,V>>;

	template <typename K,typename V>
	using table_mem=blk<table_bucket<K,V>>;

	template <typename K,typename V>
	using table_node=slnode<table_pair<K,V>>;

	template <typename K,typename V>
	struct chntable_iter
	{
		u32 currentIndex;
		table_bucket<K,V>* currentBucket;
		table_node<K,V>* currentNode;
		table_mem<K,V> table;
		chntable<K,V>* chnTable;

		b32 is_end() const;
		table_pair<K,V>& operator*();
		const table_pair<K,V>& operator*() const;
		chntable_iter<K,V>& operator++();
		chntable_iter<K,V> operator++(int);
	};

	template <typename K,typename V>
	b32 is_end(const chntable_iter<K,V>& it);

	template <typename K,typename V>
	b32 advance(chntable_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>& get(chntable_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>& get(const chntable_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>* get_ptr(chntable_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>* get_ptr(const chntable_iter<K,V>& it);
	
	template <typename K,typename V>
	table_mem<K,V> get_mem(chntable_iter<K,V>& it);

	template <typename K,typename V>
	const table_mem<K,V> get_mem(const chntable_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_coll_valid(const chntable_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_mem_valid(const chntable_iter<K,V>& it);

	template <typename K,typename V>
	b32 vindicate_mem(chntable_iter<K,V>& it);

	template <typename K,typename V,typename A>
	b32 free(A* a,chntable_iter<K,V>& it);
}

#define _DGGT_COLL_TABLE_ITER_H_
#endif
