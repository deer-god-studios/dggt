#include "dggt_coll_hash.h"
#include "mem/dggt_mem.h"
#include "math/dggt_math_constants.h"

namespace dggt
{
	namespace dggt_internal_
	{
		template <typename K,typename V>
		oatable_iter<K,V> def_oatable_iter(oatable<K,V>* table)
		{
			return oatable_iter<K,V>{
				0,0,0,oatable_mem<K,V>(),flag_mem(),table
			};
		}

		u32 hash0(u32 preh,u32 tableSize)
		{
			u32 a=5;
			u32 b=11;
			return ((a*preh+b)%LARGE_PRIME32)%tableSize;
		}

		u32 hash1(u32 preh,u32 tableSize)
		{
			return (((hash0(preh,tableSize)>>1)<<1)|1);
		}

		u32 hash(u32 preh,u32 tableSize,u32 trial)
		{
			return hash0(preh,tableSize)+
				trial*hash1(preh,tableSize);
		}
	}

	template <typename K,typename V>
	oatable_iter<K,V>& oatable<K,V>::operator[](const K& key)
	{
		return search(this,key);
	}

	template <typename K,typename V>
	const oatable_iter<K,V>& oatable<K,V>::operator[](const K& key) const
	{
		return search(this,key);
	}

	template <typename K,typename V,typename A>
	oatable<K,V> create_oatable(A* allocator)
	{
		u32 count=0;
		u32 capacity=2;
		oatable_mem<K,V> table=
			oatable_mem<K,V>(alloc<table_pair<K,V>>(allocator,capacity),
					capacity);
		flag_mem flagTable=flag_mem(
				alloc<fl32>(allocator,capacity),
				capacity);
		for (u32 i=0;i<capacity;++i)
		{
			table.ptr[i]=table_pair<K,V>();
			flagTable.ptr[i]=TABLE_EMPTY;
		}
		return oatable<K,V>{flagTable,table,count};
	}

	template <typename K,typename V,typename A>
	oatable_iter<K,V> insert(oatable<K,V>* oaTable,const K& key,
			A* allocator)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(oaTable);
		if (oaTable)
		{
			u32 trial=0;
			u32 count=oaTable->count;
			u32 tableSize=result.table.count;
			result.flagTable=oaTable->flagTable;
			result.table=oaTable->table;
			u32 preh=prehash<K>(key);
			result.currentIndex=dggt_internal_::hash(preh,count,trial);
			result.currentFlag=result.flagTable.ptr[result.currentIndex];
			result.currentPair=result.table.ptr[result.currentIndex];

			while (trial<tableSize&&
					result.currentFlag==TABLE_OCCUPIED)
			{
				result.currentIndex=
					dggt_internal_::hash(preh,tableSize,trial++);
				result.currentFlag=result.flagTable.ptr[result.currentIndex];
				result.currentPair=result.table.ptr+result.currentIndex;
			}
			if (result.currentFlag==TABLE_EMPTY||
					result.currentFlag==TABLE_DELETED)
			{
				*result.currentPair=table_pair<K,V>(key,V(0));
				result.flagTable.ptr[result.currentIndex]==
					dggt_internal_::TABLE_OCCUPIED;
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	oatable_iter<K,V> insert(oatable<K,V>* table,const K& key,
			const V& val,A* allocator)
	{
		oatable_iter<K,V> result=insert(table,key,allocator);
		table_pair<K,V> newNode=table_pair<K,V>(key,val);
		get(result)=newNode;
		return result;
	}

	template <typename K,typename V>
	oatable_iter<K,V> search(oatable<K,V>* oaTable,const K& key)
	{
		return search(oaTable,key);
	}

	template <typename K,typename V>
	const oatable_iter<K,V> search(const oatable<K,V>* table,const K& key)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(table);
		if (table)
		{
			u32 trial=0;
			u32 count=result.hashTable->count;
			u32 capacity=result.table.count;
			result.table=table->table;
			result.flagTable=table->flagTable;
			u32 preh=prehash<K>(key);
			result.currentIndex=dggt_internal_::hash(preh,capacity,trial);
			result.currentFlag=result.flagTable.ptr[result.currentIndex];
			result.currentPair=result.flagTable.ptr[result.currentIndex];

			while (trial<capacity&&
					result.currentFlag==TABLE_EMPTY||
					result.currentFlag==TABLE_DELETED)
			{
				result.currentIndex=dggt_internal_::hash(preh,capacity,trial++);
				result.currentFlag=result.flagTable.ptr[result.currentIndex];
				result.currentPair=result.flagTable.ptr[result.currentIndex];
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	oatable_iter<K,V> remove(oatable<K,V>* oaTable,const K& key,
			A* allocator)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(oaTable);
		if (oaTable)
		{

		}
		return result;
	}

	template <typename K,typename V,typename A>
	oatable_iter<K,V> clear(oatable<K,V>* table,A* allocator)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(table);
		if (table)
		{

		}
		return result;
	}

	template <typename F,typename K,typename V>
	F get_load_factor(const oatable<K,V>* table)
	{
		return F(get_count(table))/F(get_capacity(table));
	}

	template <typename K,typename V>
	u32 get_count(const oatable<K,V>* table)
	{
		return table?table->count:0;
	}

	template <typename K,typename V>
	u32 get_capacity(const oatable<K,V>* table)
	{
		return table?table->table.count:0;
	}

	template <typename K,typename V,typename A>
	oatable_iter<K,V> resize(oatable<K,V>* oaTable,u32 newSize,
			A* allocator)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(oaTable);
		if (oaTable)
		{

		}
		return result;
	}

	template <typename K,typename V>
	oatable_iter<K,V> get_iter(oatable<K,V>* table)
	{
		oatable_iter<K,V> result=dggt_internal_::def_oatable_iter(table);
		if (table)
		{
			u32 tableCount=table->table.count;
			u32 count=table->count;
			result.flagTable=table->flagTable;
			result.table=table->table;
			result.currentIndex=0;
			result.currentFlag=result.flagTable.ptr[result.CurrentIndex];
			while (result.currentIndex<tableCount&&
					result.currentFlag!=TABLE_OCCUPIED)
			{
				++result.currentIndex;
				result.currentFlag=
					result.flagTable.ptr[result.currentIndex];
				result.currentPair=result.table.ptr[result.currentIndex];
			}
		}
		return result;
	}
}
