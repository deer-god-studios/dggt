#include "math/dggt_math_constants.h"
namespace dggt
{
	namespace dggt_internal_
	{
		u32 hash(u32 preh,u32 tableSize)
		{
			u32 a=5;
			u32 b=11;
			return ((a*preh+b)%LARGE_PRIME32)%tableSize;
		}
	}
	
	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_end() const
	{
		return (currentIndex>=table.count)&&(currentNode==0);
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
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
					while (get_count(currentBucket)==0&&
							currentIndex<table.count)
					{
						currentBucket=table.mem+currentIndex++;
					}
					if (get_count(currentBucket))
					{
						currentNode=currentBucket->head;
						result=1;
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
	tnode<K,V>& iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get()
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	const tnode<K,V>& iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get() const
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	tnode<K,V>* iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_ptr()
	{
		return &currentNode->val;
	}
	template <typename K,typename V>
	const tnode<K,V>* iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_ptr() const
	{
		return &currentNode->val;
	}
	
	template <typename K,typename V>
	blk<table_bucket<K,V>> iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_mem()
	{
		return table;
	}

	template <typename K,typename V>
	const blk<table_bucket<K,V>> iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	get_mem() const
	{
		return table;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_coll_valid() const
	{
		return hashTable!=0;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
	is_mem_valid() const
	{
		return is_coll_valid()&&table==hashTable->table;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<table_bucket<K,V>>>::
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
		return hash_table<K,V>{
			alloc->template alloc<table_bucket<K,V>>(2),
			0};
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* hashTable,const K& key,A* alloc)
	{
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),hashTable};
		if (hashTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(hashTable));
			table_bucket<K,V>* bucket=hashTable->table.mem+index;
			tnode<K,V> newNode=tnode<K,V>{key,V(0)};
			++hashTable->count;
			if (!contains(bucket,newNode))
			{
				push(bucket,newNode,alloc);
			}
			if (get_load_factor<float32>(hashTable)>2.0f)
			{
				u32 cap=get_capacity(hashTable);
				result=resize(hashTable,2.0f*cap,alloc);
			}
		}
		return result;
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key,
			const V& val,A* alloc)
	{
		table_iter<K,V> result=push(table,key,alloc);
		result.get()=val;
		return result;
	}

	template <typename K,typename V>
	table_iter<K,V> search(hash_table<K,V>* table,const K& key)
	{
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),table};
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table.mem+index;
			for (list_iter<tnode<K,V>> it=get_iter(bucket);!is_end(it);
					next(it))
			{
				tnode<K,V> node=get(it);
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

	template <typename K,typename V>
	const table_iter<K,V> search(const hash_table<K,V>* table,const K& key)
	{
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),table};
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			table_bucket<K,V>* bucket=table.mem+index;
			for (list_iter<tnode<K,V>> it=get_iter(bucket);!is_end(it);
					next(it))
			{
				tnode<K,V> node=get(it);
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
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),hashTable};
		if (hashTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(hashTable));
			table_bucket<K,V>* bucket=hashTable->table.mem+index;
			slnode<tnode<K,V>>* current=0;
			slnode<tnode<K,V>>* prev=current;
			for (list_iter<tnode<K,V>> it=get_iter(bucket);!is_end(it);
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
			if (get_load_factor<float32>(hashTable)<0.25f)
			{
				u32 cap=get_capacity(hashTable);
				result=resize(hashTable,0.5f*cap,alloc);
			}
		}
	}

	template <typename K,typename V,typename F>
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
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),hashTable};
		if (hashTable)
		{
			blk<table_bucket<K,V>> newTable=
				alloc->template alloc<table_bucket<K,V>>(&newSize);
			if (newTable.mem)
			{
				hashTable->table=newTable;
				hashTable->count=0;
				blk<table_bucket<K,V>> oldTable=hashTable->table;
				for (u32 index=0;index<oldTable.count;++index)
				{
					table_bucket<K,V>* bucket=oldTable.mem+index;
					if (get_count(bucket))
					{
						for (list_iter<tnode<K,V>> it=get_iter(bucket);
								!is_end(it);next(it))
						{
							K key=it.get().key;
							V val=it.get().val;
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
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<table_bucket<K,V>>(),table};
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
	}
}
