namespace dggt
{
	template <typename T>
	b32 queue_iter<T>::is_end() const
	{
		return dggt::is_end(*this);
	}

	template <typename T>
	T& queue_iter<T>::operator*()
	{
		return *table.ptr;
	}

	template <typename T>
	const T& queue_iter<T>::operator*() const
	{
		return *table.ptr;
	}

	template <typename T>
	queue_iter<T>& queue_iter<T>::operator++()
	{
		if (!is_end(*this))
		{
			advance(*this);
		}
		return *this;
	}

	template <typename T>
	queue_iter<T> queue_iter<T>::operator++(int)
	{
		queue_iter<T> result=*this;
		if (!is_end(this))
		{
			advance(this);
		}
		return result;
	}

	template <typename T>
	b32 is_end(const queue_iter<T>& it)
	{
		bool32 result=false;
		bool32 validColl=is_coll_valid(it);
		bool32 validMem=is_mem_valid(it);
		bool32 headFirst=it.head<it.tail;
		bool32 validCurrent=is_index_valid(it.q,it.current);
		result=!validColl||
			!validCurrent||
			!validMem;
		return result;
	}

	template <typename T>
	b32 advance(queue_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			it.current=(it.current+1)%it.table.count;
		}
		return result;
	}

	template <typename T>
	T& get(queue_iter<T>& it)
	{
		return it.table[it.current];
	}

	template <typename T>
	const T& get(const queue_iter<T>& it)
	{
		return it.table[it.current];
	}

	template <typename T>
	T* get_ptr(queue_iter<T>& it)
	{
		return it.table.ptr+it.current;
	}

	template <typename T>
	const T* get_ptr(const queue_iter<T>& it)
	{
		return it.table.mem+it.current;
	}

	template <typename T>
	blk<T> get_mem(queue_iter<T>& it)
	{
		return it.table;
	}

	template <typename T>
	const blk<T> get_mem(const queue_iter<T>& it)
	{
		return it.table;
	}

	template <typename T>
	b32 is_coll_valid(const queue_iter<T>& it)
	{
		return it.q!=0;
	}

	template <typename T>
	b32 is_mem_valid(const queue_iter<T>& it)
	{
		return is_coll_valid(it)&&
			it.table==it.q->table;
	}

	template <typename T>
	b32 vindicate_mem(queue_iter<T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it)&&
				is_coll_valid(it))
		{
			it.table=it.q->table;
			result=true;
		}
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,queue_iter<T>& it)
	{
		b32 result=false;
		if (!is_mem_valid(it))
		{
			free(a,it.table.ptr,it.table.count);
			vindicate_mem(it);
		}
		return result;
	}
}
