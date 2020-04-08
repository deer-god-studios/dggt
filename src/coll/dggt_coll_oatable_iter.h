#ifndef _DGGT_COLL_OATABLE_ITER_H_

#include "dggt_coll_table_pair.h"

namespace dggt
{
	template <typename K,typename V>
	struct oatable;

	typedef blk<fl32> oatable_flag_mem;

	template <typename K,typename V>
	using oatable_mem=blk<table_pair<K,V>>;

	template <typename K,typename V>
	struct oatable_iter
	{
		oatable_mem<K,V> table;
		oatable_flag_mem flagTable;
		u32 currentIndex;
		fl32 currentFlag;
		table_pair<K,V>* currentPair;
		const oatable<K,V>* hashTable;

		b32 is_end() const;
		table_pair<K,V>& operator*();
		const table_pair<K,V>& operator*() const;
		oatable_iter<K,V>& operator++();
		oatable_iter<K,V> operator++(int);
	};

	template <typename K,typename V>
	b32 is_end(const oatable_iter<K,V>& it);

	template <typename K,typename V>
	b32 advance(oatable_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>& get(oatable_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>& get(const oatable_iter<K,V>& it);

	template <typename K,typename V>
	table_pair<K,V>* get_ptr(oatable_iter<K,V>& it);

	template <typename K,typename V>
	const table_pair<K,V>* get_ptr(const oatable_iter<K,V>& it);
	
	template <typename K,typename V>
	oatable_mem<K,V> get_mem(oatable_iter<K,V>& it);

	template <typename K,typename V>
	const oatable_mem<K,V> get_mem(const oatable_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_coll_valid(const oatable_iter<K,V>& it);

	template <typename K,typename V>
	b32 is_mem_valid(const oatable_iter<K,V>& it);

	template <typename K,typename V>
	b32 vindicate_mem(oatable_iter<K,V>& it);

	template <typename K,typename V,typename A>
	b32 free(A* a,oatable_iter<K,V>& it);
}

#define _DGGT_COLL_OATABLE_ITER_H_
#endif
