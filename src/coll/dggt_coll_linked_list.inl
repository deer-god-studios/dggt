
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,alloc_t A>
		list_node<T>* alloc_node(allocator<A>* alloc)
		{
			list_node<T>* result=0;
			if (alloc)
			{
				u32 count=1;
				result=alloc->template alloc<list_node<T>>(&count);
			}
			else
			{
				result=0;
			}
			return result;
		}

		template <typename T>
		list_node<T>* alloc_node(allocator<alloc_t::POOL>* alloc)
		{
			if (alloc)
			{
				return alloc->template alloc<list_node<T>>();
			}
			else
			{
				return 0;
			}
		}

		template <typename T,alloc_t A>
		b32 free_node(allocator<A>* alloc,list_node<T>* node)
		{
			b32 result=0;
			if (alloc&&node)
			{
				result=alloc->free(node,sizeof(list_node<T>));
			}
			return result;
		}

		template <typename T>
		b32 free_node(allocator<alloc_t::POOL>* alloc,list_node<T>* node)
		{
			b32 result=0;
			if (alloc&&node)
			{
				result=alloc->free(node);
			}
			return result;
		}

		template <typename T>
		b32 free_node(allocator<alloc_t::LINEAR>* alloc,list_node<T>* node)
		{
			return 0;
		}

		template  <typename T>
		b32 free_node(free_store<list_node<T>>* freeStore,list_node<T>* node)
		{
			freeStore->push(node);
			return 1;
		}

		template <typename T,alloc_t A>
		list_node<T>* alloc_node(allocator<A>* alloc,
				free_store<list_node<T>>* store)
		{
			list_node<T>* result=0;
			if (store&&store->available_mem())
			{
				result=store->pop();
			}
			else
			{
				result=alloc_node<T>(alloc);
			}
			return result;
		}

		template <typename T,alloc_t A>
		b32 free_node(allocator<A>* alloc,
				free_store<list_node<T>>* store,
				list_node<T>* node)
		{
			b32 result=0;
			if (alloc)
			{
				result=free_node(alloc,node);
			}
			if (!result)
			{
				result=free_node(store,node);
			}
			return result;
		}
	}

	template <typename T>
	list_node<T>::list_node() { }

	template <typename T>
	list_node<T>::list_node(const T& val,list_node* next)
	{
		this->val=val;
		this->next=next;
	}

	template <typename T>
	list_node<T>::list_node(const T& val)
		: list_node(val,0) { }

	template <typename T>
	list_iter<T>::list_iter() { current=0; }

	template <typename T>
	list_iter<T>::list_iter(list_node<T>* begin)
	{
		current=begin;
	}

	template <typename T>
	b32 list_iter<T>::is_end() const
	{
		return current==0;
	}

	template <typename T>
	void list_iter<T>::advance()
	{
		if (!is_end())
		{
			current=current->next;
		}
	}

	template <typename T>
	const T& list_iter<T>::get() const
	{
		return current->val;
	}

	template <typename T>
	T& list_iter<T>::get()
	{
		return current->val;
	}

	template <typename T>
	list_node<T>* list_iter<T>::node()
	{
		return current;
	}

	template <typename T>
	const list_node<T>* list_iter<T>::node() const
	{
		return current;
	}

	template <typename T>
	linked_list<T> create_list()
	{
		return linked_list<T>{};
	}

	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore)
	{
		list_iter<T> result=list_iter<T>();
		if (list)
		{
			list_node<T>* newNode=
				dggt_internal_::alloc_node(alloc,freeStore);
			if (newNode)
			{
				zero_struct<T>(&newNode->val);
				newNode->next=list->head;
				list->head=newNode;
				++list->count;
				result=list_iter<T>(newNode);
			}
		}
		return result;
	}

	template <typename T>
	list_iter<T> push(linked_list<T>* list,
			free_store<list_node<T>>* freeStore)
	{
		return push(list,0,freeStore);
	}

	template <typename T,alloc_t A>
	list_iter<T> push(linked_list<T>* list,
			const T& val,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore)
	{
		list_iter<T> result=push(list,alloc,freeStore);
		if (!result.is_end())
		{
			result.get()=val;
		}
		return result;
	}

	template <typename T>
	list_iter<T> push(linked_list<T>* list, const T& val,
			free_store<list_node<T>>* freeStore)
	{
		return push(list,val,0,freeStore);
	}

	template <typename T,alloc_t A>
	list_iter<T> pop(linked_list<T>* list,allocator<A>* alloc,
			free_store<list_node<T>>* freeStore)
	{
		list_iter<T> result=list_iter<T>();
		if (list)
		{
			list_node<T>* toFree=list->head;
			if (toFree)
			{
				result=list_iter<T>(toFree);
				list->head=toFree->next;
				--list->count;
				if (dggt_internal_::free_node(alloc,freeStore,toFree))
				{
					result=list_iter<T>(list->head);
				}
			}
		}
		return result;
	}

	template <typename T>
	list_iter<T> pop(linked_list<T>* list,
			free_store<list_node<T>>* freeStore)
	{
		return pop(list,0,freeStore);
	}

	template <typename T>
	list_iter<T> peek(linked_list<T>* list)
	{
		return list_iter<T>(list->head);
	}

	template <typename T>
	list_iter<T> get(linked_list<T>* list, u32 index)
	{
		list_iter<T> result=list_iter<T>();
		if (list)
		{
			u32 i=0;
			list_iter<T> it=list_iter<T>();
			for (it=begin_iter(list);!it.is_end();it.advance())
			{
				if (i==index)
				{
					break;
				}
				++i;
			}
			result=it;
		}
		return result;
	}

	template <typename T>
	list_iter<T> begin_iter(linked_list<T>* list)
	{
		return list_iter<T>(list->head);
	}

	template <typename T>
	b32 is_begin_iter(linked_list<T>* list,list_iter<T> iter)
	{
		return (list&&iter.current==list->head);
	}

	template <typename T>
	b32 is_end_iter(linked_list<T>* list,list_iter<T> iter)
	{
		return iter.is_end();
	}
}
