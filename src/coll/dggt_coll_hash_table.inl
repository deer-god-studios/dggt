
namespace dggt
{
	namespace dggt_internal_
	{
		static const u32 LARGE_PRIME32=2'038'074'743;
		static const u64 LARGE_PRIME64=19'957'072'636'091;

		u32 hash(u32 preh,u32 tableSize)
		{
			u32 a=5;
			u32 b=11;
			return ((a*preh+b)%LARGE_PRIME32)%tableSize;
		}
	}
	
	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	is_end() const
	{
		return (currentIndex>=table.count)&&(currentNode==0);
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
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
	tnode<K,V>& iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get()
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	const tnode<K,V>& iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get() const
	{
		return currentNode->val;
	}

	template <typename K,typename V>
	tnode<K,V>* iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get_ptr()
	{
		return &currentNode->val;
	}
	template <typename K,typename V>
	const tnode<K,V>* iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get_ptr() const
	{
		return &currentNode->val;
	}
	
	template <typename K,typename V>
	blk<linked_list<tnode<K,V>>> iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get_mem()
	{
		return table;
	}

	template <typename K,typename V>
	const blk<linked_list<tnode<K,V>>> iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	get_mem() const
	{
		return table;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	is_coll_valid() const
	{
		return hashTable!=0;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	is_mem_valid() const
	{
		return is_coll_valid()&&table==hashTable->table;
	}

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
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
	hash_table<K,V> hash_tabl<K,V>::create_hash_table(A* alloc)
	{
		return hash_table<K,V>{
			alloc->template alloc<linked_list<tnode<K,V>>>(2),
			0};
	}

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* hashTable,const K& key,A* alloc)
	{
		table_iter<K,V> result=table_iter<K,V>{
			0,0,0,blk<linked_list<tnode<K,V>>>,0};
		if (hashTable)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(hashTable));
			linked_list<tnode<K,V>>* bucket=hashTable->table.mem+index;
			tnode<K,V> newNode=tnode<K,V>{key,T(0)};
			if (!contains(bucket,newNode))
			{
				push(bucket,newNode,alloc);
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
			0,0,0,blk<linked_list<tnode<K,V>>>,0};
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			linked_list<tnode<K,V>>* bucket=table.mem+index;
			for (list_iter<tnode<K,V>> it=get_iter(list);!is_end(it);
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
			0,0,0,blk<linked_list<tnode<K,V>>>,0};
		if (table)
		{
			u32 preh=prehash<K>(key);
			u32 index=dggt_internal_::hash(preh,get_capacity(table));
			linked_list<tnode<K,V>>* bucket=table.mem+index;
			for (list_iter<tnode<K,V>> it=get_iter(list);!is_end(it);
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
}
