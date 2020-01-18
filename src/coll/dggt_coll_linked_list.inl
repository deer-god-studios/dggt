
namespace dggt
{
	template <typename T>
	b32 iter<T,linked_list<T>,slnode<T>*>::is_end() const
	{
		return current==0;
	}

	template <typename T>
	b32 iter<T,linked_list<T>,slnode<T>*>::next()
	{
		if (!is_end())
		{
			current=current->next;
			return 1;
		}
		return 0;
	}

	template <typename T>
	T& iter<T,linked_list<T>,slnode<T>*>::get()
	{
		return current->val;
	}

	template <typename T>
	const T& iter<T,linked_list<T>,slnode<T>*>::get() const
	{
		return current->val;
	}
	template <typename T>
	T* iter<T,linked_list<T>,slnode<T>*>::get_ptr()
	{
		return &current->val;
	}

	template <typename T>
	const T* iter<T,linked_list<T>,slnode<T>*>::get_ptr() const
	{
		return &current->val;
	}

	template <typename T>
	slnode<T>* iter<T,linked_list<T>,slnode<T>*>::get_mem()
	{
		return current;
	}
	template <typename T>
	const slnode<T>* iter<T,linked_list<T>,slnode<T>*>::get_mem() const
	{
		return current;
	}

	template <typename T>
	b32 iter<T,linked_list<T>,slnode<T>*>::is_coll_valid() const
	{
		return list!=0;
	}

	template <typename T>
	b32 iter<T,linked_list<T>,slnode<T>*>::is_mem_valid() const
	{
		return is_coll_valid()&&memIsValid;
	}

	template <typename T>
	b32 iter<T,linked_list<T>,slnode<T>*>::vindicate_mem()
	{
		b32 result=0;
		if (is_coll_valid()&&!is_mem_valid())
		{
			current=list->head;
			memIsValid=1;
			result=1;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,A* alloc)
	{
		list_iter<T> result=list_iter<T>{0,list,0};
		if (list&&alloc)
		{
			u32 nodeCount=1;
			slnode<T>* newNode=alloc->template alloc<slnode<T>>(&nodeCount);
			if (newNode)
			{
				newNode->next=list->head;
				zero_struct<T>(&newNode.val);
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
	list_iter<T> push(linked_list<T>* list,const T& val,A* alloc)
	{
		list_iter<T> result=push(list,alloc);
		if (!result.is_end())
		{
			result.current->val=val;
		}
		return result;
	}

	template <typename T,typename A>
	list_iter<T> pop(linked_list<T>* list,A* alloc)
	{
		list_iter<T> result;
		if (list&&list->count)
		{
			slnode<T>* nodeToFree=list->head;
			result.current=nodeToFree;
			result.memIsValid=0;
			list->head=nodeToFree->next;
			--list->count;
			if (alloc->free(nodeToFree))
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
		return list_iter<T>{list?list->current:0,list};
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
}
