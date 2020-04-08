
namespace dggt
{
	template <typename T>
	b32 sllist_iter<T>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename T>
	T& sllist_iter<T>::operator*()
	{
		return get(*this);
	}

	template <typename T>
	const T& sllist_iter<T>::operator*() const
	{
		return get(*this);
	}

	template <typename T>
	sllist_iter<T>& sllist_iter<T>::operator++()
	{
		if (!dggt::is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename T>
	sllist_iter<T> sllist_iter<T>::operator++(int)
	{
		sllist_iter<T>& result=*this;
		if (!is_end(*this))
		{
			advance(*this);
		}
		return result;
	}

	template <typename T>
	b32 vindicate_mem(sllist_iter<T>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&!is_mem_valid(it))
		{
			it->current=it->list->chain.ptr;
			it->memIsValid=true;
			result=true;
		}
		return result;
	}

	template <typename T>
	b32 is_end(const sllist_iter<T>& it)
	{
		return it.current==0;
	}

	template <typename T>
	b32 advance(sllist_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			it.current=it.current->next;
			result=true;
		}
		return result;
	}

	template <typename T>
	T& get(sllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	const T& get(const sllist_iter<T>& it)
	{
		return it.current->val;
	}

	template <typename T>
	T* get_ptr(sllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	const T* get_ptr(const sllist_iter<T>& it)
	{
		return &it.current->val;
	}

	template <typename T>
	slnode<T>* get_mem(sllist_iter<T>& it)
	{
		return it.current;
	}
	template <typename T>
	const slnode<T>* get_mem(const sllist_iter<T>& it)
	{
		return it.current;
	}

	template <typename T>
	b32 is_coll_valid(const sllist_iter<T>& it)
	{
		return it.list!=0;
	}

	template <typename T>
	b32 is_mem_valid(const sllist_iter<T>& it)
	{
		return is_coll_valid(it)&&it.memIsValid;
	}

	template <typename T,typename A>
	b32 free(sllist_iter<T>& it,A* a)
	{
		b32 result=false;
		if (!is_mem_valid(it))
		{
			slnode<T>* current=it.current;
			while (current)
			{
				slnode<T>* toFree=current;
				current=current->next;
				b32 freeResult=free(a,toFree);
				if (!freeResult)
				{
					result=false;
					break;
				}
			}
			vindicate_mem(it);
			result=true;
		}
		return result;
	}
}
