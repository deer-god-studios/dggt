
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		array_iter<T> def_array_iter(array<T>* arr)
		{
			return { blk<T>(),0,arr };
		}
	}

	template <typename T,typename A>
	array<T> create_array(u32 capacity,A* allocator)
	{
		array<T> result=array<T>();
		blk<T> table=
			blk<T>(alloc<T>(allocator,capacity),capacity);
		result.table=table;
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	array_iter<T> push(array<T>* arr,A* allocator)
	{
		array_iter<T> result=dggt_internal_::def_array_iter(arr);
		if (arr)
		{
			++arr->count;
			result.table=arr->table;
			if (get_load_factor<real32>(arr)>0.5f)
			{
				result=resize(arr,get_capacity(arr)*2,allocator);
			}

			if (is_mem_valid(result))
			{
				result=peek(arr);
			}
		}
		return result;
	}

	template <typename T,typename A>
	array_iter<T> push(array<T>* arr,const T& val,A* allocator)
	{
		array_iter<T> result=push(arr,allocator);
		if (is_mem_valid(result)&&
				result.table.ptr&&
				result.current==get_count(arr)-1)
		{
			get(result)=val;
		}
		return result;
	}

	template <typename T,typename A>
	array_iter<T> pop(array<T>* arr,A* allocator)
	{
		array_iter<T> result=dggt_internal_::def_array_iter(arr);
		if (arr&&arr->count)
		{
			--arr->count;
			result.table=arr->table;

			if (get_load_factor<real32>(arr)<0.25f)
			{
				result=resize(arr,get_capacity(arr)*0.5f,allocator);
			}

			if (is_mem_valid(result))
			{
				result=get_iter(arr);
			}
		}
		return result;
	}

	template <typename T>
	array_iter<T> peek(array<T>* arr)
	{
		return get(arr,get_count(arr)-1);
	}

	template <typename T>
	array_iter<T> get(array<T>* arr,u32 index)
	{
		array_iter<T> result=dggt_internal_::def_array_iter(arr);
		if (arr&&index<get_count(arr))
		{
			result.table=arr->table;
			result.current=index;
		}
		return result;
	}

	template <typename T,typename A>
	array_iter<T> clear(array<T>* arr,A* allocator)
	{
		array_iter<T> result=dggt_internal_::def_array_iter(arr);
		if (arr)
		{
			arr->count=0;
			result=resize(arr,2,allocator);
		}
		return result;
	}

	template <typename T>
	u32 get_count(const array<T>* arr)
	{
		return arr?arr->count:0;
	}

	template <typename T>
	array_iter<T> get_iter(array<T>* arr)
	{
		return get(arr,0);
	}

	template <typename T>
	b32 contains(array<T>* arr,const T& item)
	{
		b32 result=false;
		if (arr)
		{
			for (array_iter<T> it=get_iter(arr);
					!is_end(&it);++it)
			{
				if (*it==item)
				{
					result=true;
					break;
				}
			}
		}
		return result;
	}

	template <typename T>
	u32 get_capacity(array<T>* arr)
	{
		return arr?arr->table.count:0;
	}

	template <typename F,typename T>
	F get_load_factor(array<T>* arr)
	{
		return arr?(F)get_count(arr)/(F)get_capacity(arr):(F)0;
	}

	template <typename T,typename A>
	array_iter<T> resize(array<T>* arr,u32 newCapacity,A* allocator)
	{
		array_iter<T> result=dggt_internal_::def_array_iter(arr);
		if (arr)
		{
			u32 oldCapacity=get_capacity(arr);
			blk<T> oldTable=arr->table;
			blk<T> newTable=blk<T>(
					alloc<T>(allocator,newCapacity),
					newCapacity);
			if (newTable.ptr)
			{
				arr->table=newTable;
				u32 copyCount=newCapacity>oldCapacity?oldCapacity:newCapacity;
				msize copySize=sizeof(T)*copyCount;
				mem_cpy(newTable.ptr,oldTable.ptr,copySize);
				b32 oldTableFreed=free(allocator,oldTable.ptr,oldTable.count);
				if (oldTableFreed)
				{
					result=get_iter(arr);
				}
				else
				{
					result.table=oldTable;
				}
			}
			else
			{
				result=get_iter(arr);
			}
		}
		return result;
	}
}
