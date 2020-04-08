#include "dggt_coll_hash.h"
#include "mem/dggt_mem.h"
#include "math/dggt_math_constants.h"

namespace dggt
{
	namespace dggt_internal_
	{
		static const fl32 TABLE_EMPTY=0;
		static const fl32 TABLE_OCCUPIED=1;
		static const fl32 TABLE_DELETED=2;

		template <typename K,typename V>
		chntable_iter<K,V> def_chntable_iter(chntable<K,V>* table)
		{
			return chntable_iter<K,V>{
				0,0,0,chntable_mem<K,V>(),table
			};
		}

		u32 hash(u32 preh,u32 tableSize)
		{
			u32 a=5;
			u32 b=11;
			return ((a*preh+b)%LARGE_PRIME32)%tableSize;
		}
	}

	template <typename K,typename V>
	chntable_iter<K,V> chntable<K,V>::operator[](const K& key)
	{
		return search(this,key);
	}

	template <typename K,typename V>
	const chntable_iter<K,V> chntable<K,V>::operator[](const K& key) const
	{
		return search(this,key);
	}

	template <typename K,typename V,typename A>
	chntable<K,V> create_chntable(A* allocator)
	{
		u32 count=0;
		u32 capacity=2;
		chntable_mem<K,V> table=
			chntable_mem<K,V>(alloc<table_bucket<K,V>>(allocator,capacity),
					capacity);
		for (u32 i=0;i<capacity;++i)
		{
			table.ptr[i]=create_sllist<table_pair<K,V>>();
		}
		return chntable<K,V>{table,count};
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> destroy_chntable(chntable<K,V>* table,A* allocator)
	{
		chntable_iter<K,V> result=clear(table);
		if (is_mem_valid(result))
		{
			result.chnTable=NULLPTR;
			result.currentBucket=NULLPTR;
			result.currentNode=NULLPTR;
			result.currentIndex=0;
		}
		return result;
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> insert(chntable<K,V>* chnTable,const K& key,
			A* allocator)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(chnTable);
		if (chnTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(chnTable));
			table_bucket<K,V>* bucket=chnTable->table.ptr+index;
			table_pair<K,V> newNode=table_pair<K,V>(key,V(0));
			++chnTable->count;
			result.table=chnTable->table;
			result.currentBucket=bucket;
			if (!contains(bucket,newNode))
			{
				push(bucket,newNode,allocator);
			}
			result.currentNode=bucket->chain.ptr;
			if (get_load_factor<float32>(chnTable)>2.0f)
			{
				u32 cap=get_capacity(chnTable);
				chntable_iter<K,V> resizeResult=resize(chnTable,2.0f*cap,
						allocator);
				result=search(chnTable,key);
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> insert(chntable<K,V>* table,const K& key,
			const V& val,A* allocator)
	{
		chntable_iter<K,V> result=insert(table,key,allocator);
		table_pair<K,V> newNode=table_pair<K,V>(key,val);
		get(result)=newNode;
		return result;
	}

	template <typename K,typename V>
	chntable_iter<K,V> search(chntable<K,V>* table,const K& key)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(table);
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table->table.ptr+index;
			for (bucket_iter<K,V> it=get_iter(bucket);!it.is_end();
					++it)
			{
				table_pair<K,V> node=get(it);
				if (node.key_==key)
				{
					result=chntable_iter<K,V>{
						index,bucket,get_mem(it),table->table,table};
					break;
				}
			}
		}
		return result;
	}

	template <typename K,typename V>
	const chntable_iter<K,V> search(const chntable<K,V>* table,const K& key)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(table);
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table.mem+index;
			for (sllist_iter<table_pair<K,V>> it=get_iter(bucket);!is_end(it);
					++it)
			{
				table_pair<K,V> node=get(it);
				if (node.key==key)
				{
					result=chntable_iter<K,V>{
						index,bucket,get_mem(it),table->table,table};
					break;
				}
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> remove(chntable<K,V>* chnTable,const K& key,
			A* allocator)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(chnTable);
		if (chnTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(chnTable));
			table_bucket<K,V>* bucket=chnTable->table.ptr+index;
			slnode<table_pair<K,V>>* current=0;
			slnode<table_pair<K,V>>* prev=current;
			for (sllist_iter<table_pair<K,V>> it=get_iter(bucket);!is_end(it);
					++it)
			{
				current=get_mem(it);
				if (get(it).get_key()==key)
				{
					remove(bucket,prev,current,allocator);
					--chnTable->count;
					break;
				}
				prev=current;
			}
			result=get_iter(chnTable);
			if (get_load_factor<float32>(chnTable)<0.25f)
			{
				u32 cap=get_capacity(chnTable);
				result=resize(chnTable,0.5f*cap,allocator);
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> clear(chntable<K,V>* table,A* allocator)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(table);
		if (table)
		{
			result=get_iter(table);
			if (allocator)
			{
				for (u32 i=0;i<get_capacity(table);++i)
				{
					table_bucket<K,V>* bucket=table->table.mem+i;
					if (get_count(bucket))
					{
						sllist_iter<table_pair<K,V>> clearResult=clear(bucket,
								allocator);
						if (!is_mem_valid(clearResult))
						{
							slnode<table_pair<K,V>>* current=
								clearResult.current;
							while (current)
							{
								slnode<table_pair<K,V>>* toFree=current;
								toFree->next=result.currentNode;
								result.currentNode=toFree;
								current=current->next;
							}
						}
					}
				}
				blk<table_bucket<K,V>> tableToFree=table->table;
				result.table=tableToFree;
				if (free(allocator,tableToFree))
				{
					result.table=blk<table_bucket<K,V>>();
				}
			}
			table->count=0;
			table->table=blk<table_bucket<K,V>>();
		}
		return result;
	}

	template <typename F,typename K,typename V>
	F get_load_factor(const chntable<K,V>* table)
	{
		return F(get_count(table))/F(get_capacity(table));
	}

	template <typename K,typename V>
	u32 get_count(const chntable<K,V>* table)
	{
		return table?table->count:0;
	}

	template <typename K,typename V>
	u32 get_capacity(const chntable<K,V>* table)
	{
		return table?table->table.count:0;
	}

	template <typename K,typename V,typename A>
	chntable_iter<K,V> resize(chntable<K,V>* chnTable,u32 newSize,
			A* allocator)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(chnTable);
		if (chnTable)
		{
			chntable_mem<K,V> newTable=
				chntable_mem<K,V>(alloc<table_bucket<K,V>>(allocator,newSize),
						newSize);
			if (newTable.ptr)
			{
				for (u32 i=0;i<newTable.count;++i)
				{
					newTable.ptr[i]=create_sllist<table_pair<K,V>>();
				}
				chntable_mem<K,V> oldTable=chnTable->table;
				chnTable->table=newTable;
				chnTable->count=0;
				for (u32 index=0;index<oldTable.count;++index)
				{
					table_bucket<K,V>* bucket=oldTable.ptr+index;
					if (get_count(bucket))
					{
						for (sllist_iter<table_pair<K,V>> it=get_iter(bucket);
								!it.is_end();++it)
						{
							K key=get(it).key_;
							V val=get(it).val_;
							insert(chnTable,key,val,allocator);
						}
					}
				}
			}
			result=get_iter(chnTable);
		}
		return result;
	}

	template <typename K,typename V>
	chntable_iter<K,V> get_iter(chntable<K,V>* table)
	{
		chntable_iter<K,V> result=dggt_internal_::def_chntable_iter(table);
		if (table)
		{
			result.chnTable=table;
			result.currentIndex=0;
			for (u32 index=0;index<get_capacity(table);++index)
			{
				table_bucket<K,V>* bucket=table->table.ptr+index;
				if (get_count(bucket))
				{
					result.currentBucket=bucket;
					break;
				}
			}
			if (result.currentBucket)
			{
				result.currentNode=result.currentBucket->chain.ptr;
			}
			result.table=table->table;
			result.chnTable=table;
		}
		return result;
	}
}
