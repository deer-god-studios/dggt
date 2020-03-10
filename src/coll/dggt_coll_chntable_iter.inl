
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename K,typename V>
		chntable_iter<K,V> def_chntable_iter(chntable<K,V>* table)
		{
			return chntable_iter<K,V>{
				0,0,0,table_mem<K,V>(),table
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
	table_pair<K,V>& chntable_iter<K,V>::operator*()
	{
		return *table.ptr;
	}

	template <typename K,typename V>
	const table_pair<K,V>& chntable_iter<K,V>::operator*() const
	{
		return *table.ptr;
	}

	template <typename K,typename V>
	b32 chntable_iter<K,V>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename K,typename V>
	chntable_iter<K,V>& chntable_iter<K,V>::operator++()
	{
		if (!is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename K,typename V>
	chntable_iter<K,V> chntable_iter<K,V>::operator++(int)
	{
		chntable_iter<K,V> result=*this;
		if (!is_end(*this))
		{
			advance(*this);
		}
		return result;
	}


	template <typename K,typename V>
	b32 is_end(const chntable_iter<K,V>& it)
	{
		return (it.currentIndex>=it.table.count)&&
			(it.currentNode==0);
	}

	template <typename K,typename V>
	b32 advance(chntable_iter<K,V>& it) 
	{
		b32 result=false;
		if (!is_end(it))
		{
			if (it.currentNode)
			{
				it.currentNode=it.currentNode->next;
				if (!it.currentNode)
				{
					while (it.currentIndex<it.table.count)
					{
						it.currentBucket=it.table.mem+it.currentIndex++;
						if (get_count(it.currentBucket))
						{
							it.currentNode=it.currentBucket->head;
							result=true;
							break;
						}
					}
				}
				else
				{
					result=true;
				}
			}
		}
		return result;
	}

	template <typename K,typename V>
	table_pair<K,V>& get(chntable_iter<K,V>& it)
	{
		return it.currentNode->val;
	}

	template <typename K,typename V>
	const table_pair<K,V>& get(const chntable_iter<K,V>& it) 
	{
		return it.currentNode->val;
	}

	template <typename K,typename V>
	table_pair<K,V>* get_ptr(chntable_iter<K,V>& it) 
	{
		return &it.currentNode->val;
	}
	template <typename K,typename V>
	const table_pair<K,V>* get_ptr(const chntable_iter<K,V>& it)
	{
		return &it.currentNode->val;
	}
	
	template <typename K,typename V>
	table_mem<K,V> gem_mem(chntable_iter<K,V>& it)
	{
		return it.table;
	}

	template <typename K,typename V>
	const table_mem<K,V> get_mem(const chntable_iter<K,V>& it)
	{
		return it.table;
	}

	template <typename K,typename V>
	b32 is_coll_valid(const chntable_iter<K,V>& it)
	{
		return it.hashTable!=0;
	}

	template <typename K,typename V>
	b32 is_mem_valid(const chntable_iter<K,V>& it)
	{
		return is_coll_valid(it)&&it.table==it.hashTable->table;
	}

	template <typename K,typename V>
	b32 vindicate_mem(chntable_iter<K,V>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			it.table=it.hashTable->table;
			result=true;
		}
		return result;
	}

	template <typename K,typename V,typename A>
	b32 free(A* a,chntable_iter<K,V>& it)
	{
		b32 result=false;
		if (is_mem_valid(it))
		{
			if (is_coll_valid(it))
			{
				for (u32 i=0;i<it.table.count;++i)
				{
					clear(it.table.ptr[i],a);
				}
			}
			free(a,it.table.ptr,it.table.count);
			vindicate_mem(it);
		}
		return result;
	}
}
