
#include "math/dggt_math_constants.h"

namespace dggt
{

	template <typename K,typename V>
	table_pair<K,V>& oatable_iter<K,V>::operator*()
	{
		return *table.ptr;
	}

	template <typename K,typename V>
	const table_pair<K,V>& oatable_iter<K,V>::operator*() const
	{
		return *table.ptr;
	}

	template <typename K,typename V>
	b32 oatable_iter<K,V>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename K,typename V>
	oatable_iter<K,V>& oatable_iter<K,V>::operator++()
	{
		if (!is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename K,typename V>
	oatable_iter<K,V> oatable_iter<K,V>::operator++(int)
	{
		oatable_iter<K,V> result=*this;
		if (!is_end(*this))
		{
			advance(*this);
		}
		return result;
	}


	template <typename K,typename V>
	b32 is_end(const oatable_iter<K,V>& it)
	{
		return (it.currentIndex>=it.table.count)&&
			(it.currentPair==0);
	}

	template <typename K,typename V>
	b32 advance(oatable_iter<K,V>& it) 
	{
		b32 result=false;
		if (!is_end(it))
		{
			fl32 currentFlag=it.flagTable.ptr[it.current];
			while (!is_end(it)&&
					currentFlag==TABLE_EMPTY||
					currentFlag==TABLE_DELETED)
			{
				currentFlag=it.flagTable.ptr[++it.current];
			}
			if (!is_end(it))
			{
				it.currentPair=it.table+it.current;
				result=true;
			}

		}
		return result;
	}

	template <typename K,typename V>
	table_pair<K,V>& get(oatable_iter<K,V>& it)
	{
		return it.currentPair;
	}

	template <typename K,typename V>
	const table_pair<K,V>& get(const oatable_iter<K,V>& it) 
	{
		return it.currentPair;
	}

	template <typename K,typename V>
	table_pair<K,V>* get_ptr(oatable_iter<K,V>& it) 
	{
		return &it.currentPair;
	}
	template <typename K,typename V>
	const table_pair<K,V>* get_ptr(const oatable_iter<K,V>& it)
	{
		return &it.currentPair;
	}
	
	template <typename K,typename V>
	oatable_mem<K,V> gem_mem(oatable_iter<K,V>& it)
	{
		return it.table;
	}

	template <typename K,typename V>
	const oatable_mem<K,V> get_mem(const oatable_iter<K,V>& it)
	{
		return it.table;
	}

	template <typename K,typename V>
	b32 is_coll_valid(const oatable_iter<K,V>& it)
	{
		return it.hashTable!=0;
	}

	template <typename K,typename V>
	b32 is_mem_valid(const oatable_iter<K,V>& it)
	{
		return is_coll_valid(it)&&it.table==it.hashTable->table&&
			it.flagTable==it.hashTable->flagTable;
	}

	template <typename K,typename V>
	b32 vindicate_mem(oatable_iter<K,V>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			it.table=it.hashTable->table;
			it.flagTable=it.hashTable->flagTable;
			result=true;
		}
		return result;
	}

	template <typename K,typename V,typename A>
	b32 free(A* a,oatable_iter<K,V>& it)
	{
		b32 result=false;
		if (is_mem_valid(it))
		{
			b32 freeTable=free(a,it.table.ptr,it.table.count);
			b32 freeFlagTable=free(a,it.flagTable.ptr,it.flagTable.count);
			b32 vindicated=vindicate_mem(it);
			result=vindicated&&freeTable&&freeFlagTable;
		}
		return result;
	}
}
