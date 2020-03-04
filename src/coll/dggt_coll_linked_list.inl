
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		list_iter<T> default_iter(linked_list<T>* list)
		{
			return list_iter<T>{0,list,0};
		}
	}

	template <typename T>
	T& list_iter<T>::operator*()
	{
		return get(this);
	}

	template <typename T>
	const T& list_iter<T>::operator*() const
	{
		return get(this);
	}

	template <typename T>
	list_iter<T>& operator++()
	{
		if (!is_end(this))
		{
			advance(this);
		}
		return *this;
	}

	template <typename T>
	list_iter<T>& operator++(int)
	{
		list_iter<T>& result=*this;
		if (!is_end(this))
		{
			advance(this);
		}
		return result;
	}

	template <typename T>
	b32 is_end(const list_iter<T>* it)
	{
		return it->current==0;
	}

	template <typename T>
	b32 advance(list_iter<T>* it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			it->current=it->current->next;
			result=true;
		}
		return result;
	}

	template <typename T>
	T& get(list_iter<T>* it)
	{
		return it->current->val;
	}

	template <typename T>
	const T& get(const list_iter<T>* it)
	{
		return it->current->val;
	}
	template <typename T>
	T* get_ptr(list_iter<T>* it)
	{
		return &it->current->val;
	}

	template <typename T>
	const T* get_ptr(list_iter<T>* it)
	{
		return &it->current->val;
	}

	template <typename T>
	slnode<T>* get_mem(list_iter<T>* it)
	{
		return it->current;
	}
	template <typename T>
	const slnode<T>* get_mem(list_iter<T>* it)
	{
		return it->current;
	}

	template <typename T>
	b32 is_coll_valid(const list_iter<T>* it)
	{
		return it->list!=0;
	}

	template <typename T>
	b32 is_mem_valid(const list_iter<T>* it)
	{
		return is_coll_valid(it)&&it->memIsValid;
	}

	template <typename T>
	b32 vindicate_mem(list_iter<T>* it)
	{
		b32 result=0;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			current=list->head;
			memIsValid=1;
			result=1;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,A* a)
	{
		list_iter<T> result=dggt_internal_::default_iter(list);
		if (list&&a)
		{
			slnode<T>* newNode=alloc<slnode<T>>(a);
			if (newNode)
			{
				newNode->next=list->head;
				zero_struct<T>(&newNode->val);
				result.current=newNode;
				result.list=list;
				result.memIsValid=1;
				list->head=newNode;
				++list->count;
			}
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,const T& val,A* a)
	{
		list_iter<T> result=push(list,a);
		if (!is_end(&result))
		{
			result.current->val=val;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> pop(linked_list<T>* list,A* a)
	{
		list_iter<T> result;
		if (list&&list->count)
		{
			slnode<T>* nodeToFree=list->head;
			result.current=nodeToFree;
			result.memIsValid=0;
			list->head=nodeToFree->next;
			--list->count;
			if (free(a,nodeToFree))
			{
				result.current=list->head;
				result.list=list;
				result.memIsValid=1;
			}
		}
		return result;
	}

	template <typename T>
	list_iter<T> peek(linked_list<T>* list)
	{
		return list_iter<T>{list?list->head:0,list};
	}

	template <typename T>
	list_iter<T> get(linked_list<T>* list,u32 index)
	{
		list_iter<T> result=list_iter<T>{0,list};
		list_iter<T> it=get_iter(list);
		u32 i=0;
		while (!is_end(it)&&i<index)
		{
			++i;
			next(it);
		}
		if (!is_end(it))
		{
			result=it;
		}
		return result;
	}

	template <typename T>
	list_iter<T> get_iter(linked_list<T>* list)
	{
		return peek(list);
	}

	template <typename T>
	u32 get_count(const linked_list<T>* list)
	{
		return list?list->count:0;
	}

	template <typename T>
	b32 contains(linked_list<T>* list,const T& item)
	{
		b32 result=0;
		for (list_iter<T> it=get_iter(list);
				!it.is_end();
				it.next())
		{
			if (it.get()==item)
			{
				result=1;
				break;
			}
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> remove(
			linked_list<T>* list,
			slnode<T>* prev,
			slnode<T>* toRemove,A* a)
	{
		list_iter<T> result={0,list,0};
		if (list)
		{
			if (prev)
			{
				ASSERT(toRemove&&prev->next==toRemove);
				result.current=toRemove;
				result.memIsValid=0;
				prev->next=toRemove->next;
				--list->count;
				if (free(a,toRemove,1))
				{
					result.current=prev;
					result.list=list;
					result.memIsValid=1;
				}
			}
			else
			{
				result=pop(list,a);
			}
		}

		return result;
	}

	template <typename T,typename A>
	list_iter<T> clear(linked_list<T>* list,A* a)
	{
		list_iter<T> result=dggt_internal_::default_iter(list);
		if (list)
		{
			slnode<T>* current=list->head;
			result.memIsValid=1;
			while (current)
			{
				slnode<T>* nodeToFree=current;
				current=current->next;
				if (!free(a,nodeToFree,1))
				{
					nodeToFree->next=result.current;
					result.current=nodeToFree;
					result.memIsValid=0;
				}
			}
			if (result.memIsValid)
			{
				result.current=list->head;
			}
			list->count=0;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> insert(linked_list<T>* list,slnode<T>* prev,
			const T& val,A* a)
	{
		list_iter<T> result=list_iter<T>{0,list,0};
		if (list)
		{
			slnode<T>* newNode=alloc<slnode<T>>(a);
			if (newNode)
			{
				result.current=newNode;
				result.memIsValid=1;
				newNode->val=val;
				if (prev)
				{
					newNode->next=prev->next;
					prev->next=newNode;
				}
				else
				{
					newNode->next=list->head->next;
					list->head=newNode;
				}
				++list->count;
			}
		}
		return result;
	}
}
