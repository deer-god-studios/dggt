
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		inline queue_iter<T> default_iter(queue<T>* q)
		{
			return queue_iter<T>{0,0,0,blk<T>(),q};
		}

		u32 get_index_from_head(u32 head,u32 cap,u32 index)
		{
			return (head+index)%cap;
		}

		u32 get_index_from_tail(u32 tail,u32 cap,u32 index)
		{
			return (tail-index)%cap;
		}

		template <typename T>
		b32 is_index_valid(queue<T>* q,u32 index)
		{
			b32 result=0;
			if (q)
			{
				bool32 headFirst=q->head<q->tail;
				bool32 validIndex=0;
				if (headFirst)
				{
					validIndex=
						(index>=q->head&&
						 index<=q->tail);
				}
				else
				{
					validIndex=
						(index<=q->tail||
						 index>=q->head);
				}
				result=validIndex;
			}
			return result;
		}
	}
	template <typename T>
	b32 iter<T,queue<T>,blk<T>>::is_end() const
	{
		bool32 result=0;
		bool32 validColl=is_coll_valid();
		bool32 validMem=is_mem_valid();
		bool32 headFirst=head<tail;
		bool32 validCurrent=dggt_internal_::is_index_valid(q,current);
		result=!validColl||
			!validCurrent||
			!validMem;
		return result;
	}

	template <typename T>
	b32 iter<T,queue<T>,blk<T>>::next()
	{
		b32 result=0;
		if (!is_end())
		{
			current=(current+1)%table.count;
		}
		return result;
	}

	template <typename T>
	T& iter<T,queue<T>,blk<T>>::get()
	{
		return table[current];
	}

	template <typename T>
	const T& iter<T,queue<T>,blk<T>>::get() const
	{
		return table[current];
	}

	template <typename T>
	T* iter<T,queue<T>,blk<T>>::get_ptr()
	{
		return table.mem+current;
	}

	template <typename T>
	const T* iter<T,queue<T>,blk<T>>::get_ptr() const
	{
		return table.mem+current;
	}

	template <typename T>
	blk<T> iter<T,queue<T>,blk<T>>::get_mem()
	{
		return table;
	}

	template <typename T>
	const blk<T> iter<T,queue<T>,blk<T>>::get_mem() const
	{
		return table;
	}

	template <typename T>
	b32 iter<T,queue<T>,blk<T>>::is_coll_valid() const
	{
		return q!=0;
	}

	template <typename T>
	b32 iter<T,queue<T>,blk<T>>::is_mem_valid() const
	{
		return is_coll_valid()&&
			table==q->table;
	}

	template <typename T>
	b32 iter<T,queue<T>,blk<T>>::vindicate_mem()
	{
		b32 result=0;
		if (!is_mem_valid()&&
				is_coll_valid())
		{
			table=q->table;
			result=1;
		}
		return result;
	}

	template <typename T>
	T& queue<T>::operator[](u32 index)
	{
		return table[(tail-index)%table.count];
	}

	template <typename T>
	const T& queue<T>::operator[](u32 index) const
	{
		return table[(head+index)%table.count];
	}

	template <typename T,typename A>
	queue_iter<T> enqueue(queue<T>* q,A* alloc)
	{
		queue_iter<T> result=queue_iter<T>{0,0,0,blk<T>(),q};
		if (q)
		{
			u32 count=get_count(q);
			u32 capacity=get_capacity(q);
			if (count+1>capacity) // needs resizing.
			{
				result=resize(q,2*capacity,alloc);
				capacity=get_capacity(q);
			}
			else if (q)
			{
				result.table=q->table;
			}
			if (result.is_coll_valid())
			{
				q->tail=q->count%capacity;
				//q->tail=(q->tail+1)%capacity;
				++q->count;
				zero_struct<T>(q->table.mem+q->tail);
				result.current=q->tail;
				result.head=q->head;
				result.tail=q->tail;
				if (result.is_mem_valid())
				{
					result=get_iter(q);
				}
			}
		}
		return result;
	}
	
	template <typename T,typename A>
	queue_iter<T> enqueue(queue<T>* q,const T& val,A* alloc)
	{
		queue_iter<T> result=enqueue(q,alloc);
		if (q)
		{
			q->table.mem[q->tail]=val;
		}
		return result;
	}

	template <typename T,typename A>
	queue_iter<T> clear(queue<T>* q,A* alloc)
	{
		queue_iter<T> result=dggt_internal_::default_iter(q);
		if (q)
		{
			blk<T> table=q->table;
			result.table=table;
			q->table=blk<T>();
			q->count=0;
			if (alloc->free(table))
			{
				result.table=blk<T>();
			}
		}
		return result;
	}
	template <typename T,typename A>
	queue_iter<T> dequeue(queue<T>* q,A* alloc)
	{
		queue_iter<T> result=dggt_internal_::default_iter(q);
		u32 count=get_count(q);
		u32 capacity=get_capacity(q);
		if (q&&count)
		{
			q->head=(q->head+1)%capacity;
			--q->count;
			result.current=dggt_internal_::get_index_from_head(q->head,
					get_capacity(q),0);
			result.head=q->head;
			result.tail=q->tail;
			result.table=q->table;
			count=get_count(q);
			u32 capacity=get_capacity(q);
			if (count&&get_load_factor<real32>(q)<0.25f)
			{
				result=resize(q,capacity/2,alloc);
			}
			if (result.is_mem_valid())
			{
				result=get_iter(q);
			}
		}
		return result;
	}

	template <typename T>
	u32 get_head(const queue<T>* q)
	{
		return q?q->head:0;
	}

	template <typename T>
	u32 get_tail(const queue<T>* q)
	{
		return q?q->tail:0;
	}

	template <typename T>
	queue_iter<T> get(queue<T>* q,u32 index)
	{
		return get_iter(q,index);
	}

	template <typename T>
	queue_iter<T> get_iter(queue<T>* q,u32 index)
	{
		queue_iter<T> result=dggt_internal_::default_iter(q);
		u32 absIndex=dggt_internal_::get_index_from_head(q->head,
				get_capacity(q),
				index);
		if (q&&dggt_internal_::is_index_valid(q,absIndex))
		{
			result.current=absIndex;
			result.head=q->head;
			result.tail=q->tail;
			result.table=q->table;
			result.q=q;
		}
		return result;
	}

	template <typename T>
	u32 get_count(const queue<T>* q)
	{
		return q?q->count:0;
	}

	template <typename T>
	u32 get_capacity(const queue<T>* q)
	{
		return q?q->table.count:0;
	}

	template <typename T,typename F>
	F get_load_factor(const queue<T>* q)
	{
		return q?F(get_count(q))/F(get_capacity(q)):F(0);
	}

	template <typename T,typename A>
	queue_iter<T> resize(queue<T>* q,u32 newCapacity,A* alloc)
	{
		queue_iter<T> result={0,0,0,blk<T>(),q};
		if (q&&alloc)
		{
			result.table=q->table;
			u32 oldCapacity=get_capacity(q);
			blk<T> newTable=alloc->template alloc<T>(newCapacity);
			if (newTable.mem)
			{
				blk<T> oldTable=q->table;
				u32 copyCount=min<u32>(oldCapacity,newCapacity);
				for (u32 i=0;i<copyCount;++i)
				{
					newTable.mem[i]=
						*(oldTable.mem+
								dggt_internal_::get_index_from_head(
									q->head,oldTable.count,i));
				}
				q->head=0;
				q->tail=q->count?q->count-1:0;
				q->table=newTable;
				if (alloc->free(oldTable))
				{
					result.table=newTable;
				}
			}
		}
		return result;
	}
}
