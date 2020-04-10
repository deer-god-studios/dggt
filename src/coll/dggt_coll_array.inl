
namespace dggt
{
	template <typename T,typename A>
	array<T> create_array(u32 capacity,A* allocator)
	{
		array<T> result=array<T>();
		array<T>::mem_type mem=
			malloc_page<T>(allocator,capacity);
		result.mem=mem;
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	array<T>::iter destroy_array(array<T>* arr,A* allocator)
	{
		array<T>::iter result=array<T>::iter(arr);
		if (arr)
		{
			result.mem=arr->mem;
			arr->count=0;
			b32 freeResult=free(allocator,arr->mem);
			if (freeResult)
			{
				result=array<T>::iter();
			}
		}
		return result;
	}

	template <typename T,typename A>
	array<T>::iter push(array<T>* arr,A* allocator)
	{
		array<T>::iter result=array<T>::iter(arr);
		if (arr)
		{
			++arr->count;
			result.mem=arr->mem;
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
	array<T>::iter push(array<T>* arr,const T& val,A* allocator)
	{
		array<T>::iter result=push(arr,allocator);
		if (is_mem_valid(result)&&
				result.mem.ptr&&
				result.current==get_count(arr)-1)
		{
			*result=val;
		}
		return result;
	}

	template <typename T,typename A>
	array<T>::iter pop(array<T>* arr,A* allocator)
	{
		array<T>::iter result=array<T>::iter(arr);
		if (arr&&arr->count)
		{
			--arr->count;
			result.mem=arr->mem;

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
	array<T>::iter peek(array<T>* arr)
	{
		return get(arr,get_count(arr)-1);
	}

	template <typename T>
	array<T>::iter get(array<T>* arr,u32 index)
	{
		array<T>::iter result=array<T>::iter(arr);
		if (arr&&index<get_count(arr))
		{
			result.mem=arr->mem;
			result.current=index;
		}
		return result;
	}

	template <typename T,typename A>
	array<T>::iter clear(array<T>* arr,A* allocator)
	{
		array<T>::iter result=array<T>::iter(arr);
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
	array<T>::iter get_iter(array<T>* arr)
	{
		return get(arr,0);
	}

	template <typename T>
	b32 contains(array<T>* arr,const T& item)
	{
		b32 result=false;
		if (arr)
		{
			for (array<T>::iter it=get_iter(arr);
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
		return arr?arr->mem.count:0;
	}

	template <typename F,typename T>
	F get_load_factor(array<T>* arr)
	{
		return arr?(F)get_count(arr)/(F)get_capacity(arr):(F)0;
	}

	template <typename T,typename A>
	array<T>::iter resize(array<T>* arr,u32 newCapacity,A* allocator)
	{
		array<T>::iter result=array<T>::iter(arr);
		if (arr)
		{
			u32 oldCapacity=get_capacity(arr);
			array<T>::mem_type oldMem=arr->mem;
			array<T>::mem_type newMem=malloc_page<T>(allocator,newCapacity);
			if (newMem.ptr)
			{
				arr->mem=newMem;
				u32 copyCount=newCapacity>oldCapacity?oldCapacity:newCapacity;
				msize copySize=sizeof(T)*copyCount;
				mem_cpy(newMem.ptr,oldMem.ptr,copySize);
				b32 oldMemFreed=free(allocator,oldMem.ptr,oldMem.count);
				if (oldMemFreed)
				{
					result=get_iter(arr);
				}
				else
				{
					result.mem=oldMem;
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
