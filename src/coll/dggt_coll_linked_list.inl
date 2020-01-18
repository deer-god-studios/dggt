
namespace dggt
{
	template <typename T>
	b32 iter<T,linked_list<T>>::is_end() const
	{
		return current&&list&&list->head==current;
	}

	template <typename T>
	b32 iter<T,linked_list<T>>::next()
	{
		if (!is_end())
		{
			current=current->next;
			return 1;
		}
		return 0;
	}

	template <typename T>
	T& iter<T,linked_list<T>>::get()
	{
		return current->val;
	}

	template <typename T>
	const T& iter<T,linked_list<T>>::get() const
	{
		return current->val;
	}
	template <typename T>
	T* iter<T,linked_list<T>>::get_ptr()
	{
		return &current->val;
	}

	template <typename T>
	const T* iter<T,linked_list<T>>::get_ptr() const
	{
		return &current->val;
	}

	template <typename T>
	slnode<T>* iter<T,linked_list<T>>::get_node()
	{
		return current;
	}
	template <typename T>
	const slnode<T>* iter<T,linked_list<T>>::get_node() const
	{
		return current;
	}

	template <typename T,typename A>
	list_iter<T> push(linked_list<T>* list,A* alloc)
	{
		list_iter<T> result=list_iter<T>{0,list};
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
			list->head=nodeToFree->next;
			--list->count;
			if (alloc->free(nodeToFree))
			{
				result.current=list->head;
				result.list=list;
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
