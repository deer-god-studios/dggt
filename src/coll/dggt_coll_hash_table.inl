#include "math/dggt_math_constants.h"
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename K,typename V>
		table_iter<K,V> default_iter(hash_table<K,V>* table)
		{
			return table_iter<K,V>{
				0,0,0,blk<table_bucket<K,V>>(),table
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
	b32 iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_end() const
	{
		return (currentIndex>=table.count)&&(currentNode==0);
	}

	template <typename K,typename V>
	b32 iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	next()
	{
		b32 result=0;
		if (!is_end())
		{
			if (currentNode)
			{
				currentNode=currentNode->next;
				if (!currentNode)
				{
					while (currentIndex<table.count)
					{
						currentBucket=table.mem+currentIndex++;
						if (get_count(currentBucket))
						{
							currentNode=currentBucket->head;
							result=1;
							break;
						}
					}
				}
				else
				{
					result=1;
				}
			}
		}
		return result;
	}

	template <typename K,typename V>
	table_pair<K,V>& iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get()
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	const table_pair<K,V>& iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get() const
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	table_pair<K,V>* iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_ptr()
	{
		return &currentNode->val;
	}
	template <typename K,typename V>
	const table_pair<K,V>* iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_ptr() const
	{
		return &currentNode->val;
	}
	
	template <typename K,typename V>
	blk<table_bucket<K,V>> iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_mem()
	{
		return table;
	}

	template <typename K,typename V>
	const blk<table_bucket<K,V>> iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_mem() const
	{
		return table;
	}

	template <typename K,typename V>
	b32 iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_coll_valid() const
	{
		return hashTable!=0;
	}

	template <typename K,typename V>
	b32 iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_mem_valid() const
	{
		return is_coll_valid()&&table==hashTable->table;
	}

	template <typename K,typename V>
	b32 iter<table_pair<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	vindicate_mem()
	{
		b32 result=0;
		if (is_coll_valid()&&!is_mem_valid())
		{
			table=hashTable->table;
			result=1;
		}
		return result;
	}

	template <typename K,typename V>
	table_iter<K,V> hash_table<K,V>::operator[](const K& key)
	{
		return search(this,key);
	}

	template <typename K,typename V>
	const table_iter<K,V> hash_table<K,V>::operator[](const K& key) const
	{
		return search(this,key);
	}

	template <typename K,typename V,typename A>
	hash_table<K,V> create_hash_table(A* alloc)
	{
		u32 count=0;
		u32 capacity=2;
		table_blk<K,V> table=alloc->template alloc<table_bucket<K,V>>(capacity);
		for (u32 i=0;i<capacity;++i)
		{
			table.mem[i]=create_linked_list<table_pair<K,V>>();
		}
		return hash_table<K,V>{table,count};
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* hashTable,const K& key,A* alloc)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(hashTable);
		if (hashTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(hashTable));
			table_bucket<K,V>* bucket=hashTable->table.mem+index;
			table_pair<K,V> newNode=table_pair<K,V>(key,V(0));
			++hashTable->count;
			result.table=hashTable->table;
			result.currentBucket=bucket;
			if (!contains(bucket,newNode))
			{
				push(bucket,newNode,alloc);
			}
			result.currentNode=bucket->head;
			if (get_load_factor<float32>(hashTable)>2.0f)
			{
				u32 cap=get_capacity(hashTable);
				table_iter<K,V> resultResult=resize(hashTable,2.0f*cap,alloc);
				result=search(hashTable,key);
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key,
			const V& val,A* alloc)
	{
		table_iter<K,V> result=insert(table,key,alloc);
		table_pair<K,V> newNode=table_pair<K,V>(key,val);
		result.get()=newNode;
		return result;
	}

	template <typename K,typename V>
	table_iter<K,V> search(hash_table<K,V>* table,const K& key)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(table);
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table->table.mem+index;
			for (bucket_iter<K,V> it=get_iter(bucket);!it.is_end();
					it.next())
			{
				table_pair<K,V> node=it.get();
				if (node.key_==key)
				{
					result=table_iter<K,V>{
						index,bucket,it.get_mem(),table->table,table};
					break;
				}
			}
		}
		return result;
	}

	template <typename K,typename V>
	const table_iter<K,V> search(const hash_table<K,V>* table,const K& key)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(table);
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table.mem+index;
			for (list_iter<table_pair<K,V>> it=get_iter(bucket);!is_end(it);
					next(it))
			{
				table_pair<K,V> node=get(it);
				if (node.key==key)
				{
					result=table_iter<K,V>{
						index,bucket,get_mem(it),table->table,table};
					break;
				}
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> remove(hash_table<K,V>* hashTable,const K& key,
			A* alloc)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(hashTable);
		if (hashTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(hashTable));
			table_bucket<K,V>* bucket=hashTable->table.mem+index;
			slnode<table_pair<K,V>>* current=0;
			slnode<table_pair<K,V>>* prev=current;
			for (list_iter<table_pair<K,V>> it=get_iter(bucket);!is_end(it);
					next(it))
			{
				current=it.get_ptr();
				if (it.get()==key)
				{
					remove(bucket,prev,current,alloc);
					--hashTable->count;
					break;
				}
				prev=current;
			}
			result=get_iter(hashTable);
			if (get_load_factor<float32>(hashTable)<0.25f)
			{
				u32 cap=get_capacity(hashTable);
				result=resize(hashTable,0.5f*cap,alloc);
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> clear(hash_table<K,V>* table,A* alloc)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(table);
		if (table)
		{
			result=get_iter(table);
			if (alloc)
			{
				for (u32 i=0;i<get_capacity(table);++i)
				{
					table_bucket<K,V>* bucket=table->table.mem+i;
					if (get_count(bucket))
					{
						list_iter<table_pair<K,V>> clearResult=clear(bucket,alloc);
						if (!clearResult.is_mem_valid())
						{
							slnode<table_pair<K,V>>* current=clearResult.current;
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
				if (alloc->free(tableToFree))
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
	F get_load_factor(const hash_table<K,V>* table)
	{
		return F(get_count(table))/F(get_capacity(table));
	}

	template <typename K,typename V>
	u32 get_count(const hash_table<K,V>* table)
	{
		return table?table->count:0;
	}

	template <typename K,typename V>
	u32 get_capacity(const hash_table<K,V>* table)
	{
		return table?table->table.count:0;
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> resize(hash_table<K,V>* hashTable,u32 newSize,A* alloc)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(hashTable);
		if (hashTable)
		{
			table_blk<K,V> newTable=
				alloc->template alloc<table_bucket<K,V>>(newSize);
			if (newTable.mem)
			{
				for (u32 i=0;i<newTable.count;++i)
				{
					newTable.mem[i]=create_linked_list<table_pair<K,V>>();
				}
				table_blk<K,V> oldTable=hashTable->table;
				hashTable->table=newTable;
				hashTable->count=0;
				for (u32 index=0;index<oldTable.count;++index)
				{
					table_bucket<K,V>* bucket=oldTable.mem+index;
					if (get_count(bucket))
					{
						for (list_iter<table_pair<K,V>> it=get_iter(bucket);
								!it.is_end();it.next())
						{
							K key=it.get().key_;
							V val=it.get().val_;
							insert(hashTable,key,val,alloc);
						}
					}
				}
			}
			result=get_iter(hashTable);
		}
		return result;
	}

	template <typename K,typename V>
	table_iter<K,V> get_iter(hash_table<K,V>* table)
	{
		table_iter<K,V> result=dggt_internal_::default_iter(table);
		if (table)
		{
			result.hashTable=table;
			result.currentIndex=0;
			for (u32 index=0;index<get_capacity(table);++index)
			{
				table_bucket<K,V>* bucket=table->table.mem+index;
				if (get_count(bucket))
				{
					result.currentBucket=bucket;
					break;
				}
			}
			if (result.currentBucket)
			{
				result.currentNode=result.currentBucket->head;
			}
			result.table=table->table;
			result.hashTable=table;
		}
		return result;
	}
}
