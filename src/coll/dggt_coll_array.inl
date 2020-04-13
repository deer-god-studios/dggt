
namespace dggt
{
	template <typename T,typename A>
	array<T> create_array(A* allocator,msize capacity)
	{
		array<T> result=array<T>{};
		typename array<T>::mem_type mem=
			malloc_array_mem<T>(allocator,capacity);
		result.mem=mem;
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	typename array<T>::iter destroy_array(array<T>& arr,A* allocator)
	{
		typename array<T>::iter result=get_iter(arr);
		arr.count=0;
		if (free(allocator,arr.mem))
		{
			result=typename array<T>::iter();
		}
		return result;
	}

	template <typename T,typename A>
	typename array<T>::iter push(array<T>& arr,A* allocator)
	{
		typename array<T>::iter result=peek(arr);
		if (get_count(arr)+1>get_capacity(arr))
		{
			result=resize(arr,get_capacity(arr)*2,allocator);
		}
		if (is_mem_valid(result))
		{
			++arr.count;
			result=peek(arr);
		}
		return result;
	}

	template <typename T,typename A>
	typename array<T>::iter push(array<T>& arr,const T& val,A* allocator)
	{
		typename array<T>::iter result=push(arr,allocator);
		if (is_mem_valid(result)&&
				result==peek(arr))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,typename A>
	typename array<T>::iter pop(array<T>& arr,A* allocator)
	{
		typename array<T>::iter result=typename array<T>::iter(arr);
		if (get_count(arr))
		{
			if (allocator)
			{
				--arr.count;
				if (get_load_factor(arr)<0.25f)
				{
					result=resize(arr,get_capacity(arr)*0.5f,allocator);
				}

				if (is_mem_valid(result))
				{
					result=peek(arr);
				}
			}
			else
			{
				result=peek(arr);
				--arr.count;
			}
		}

		return result;
	}

	template <typename T>
	typename array<T>::iter peek(array<T>& arr)
	{
		return get(arr,get_count(arr)-1);
	}

	template <typename T>
	typename array<T>::iter get(array<T>& arr,u32 index)
	{
		typename array<T>::iter result=typename array<T>::iter(arr);
		if (index<get_count(arr))
		{
			result.current=array_key<T>((T*)arr.mem+index,arr.count,index);
		}
		return result;
	}

	template <typename T,typename A>
	typename array<T>::iter clear(array<T>& arr,A* allocator)
	{
		typename array<T>::iter result=typename array<T>::iter(arr);
		arr.count=0;
		result=resize(arr,0,allocator);
		return result;
	}

	template <typename T>
	u32 get_count(const array<T>& arr)
	{
		return arr.count;
	}

	template <typename T>
	typename array<T>::iter get_iter(array<T>& arr)
	{
		return get(arr,0);
	}

	template <typename T>
	b32 contains(array<T>& arr,const T& item)
	{
		b32 result=false;
		for (typename array<T>::iter it=get_iter(arr);
				!is_end(&it);++it)
		{
			if (*it==item)
			{
				result=true;
				break;
			}
		}
		return result;
	}

	template <typename T>
	u32 get_capacity(array<T>& arr)
	{
		return arr.mem.size;
	}

	template <typename T,typename F>
	F get_load_factor(array<T>& arr)
	{
		return (F)get_count(arr)/(F)get_capacity(arr);
	}

	template <typename T,typename A>
	typename array<T>::iter resize(array<T>& arr,u32 newCapacity,A* allocator)
	{
		typename array<T>::iter result=typename array<T>::iter(arr);
		u32 oldCapacity=get_capacity(arr);
		if (oldCapacity!=newCapacity)
		{
			typename array<T>::mem_type oldMem=arr.mem;
			typename array<T>::mem_type newMem=
				malloc_array_mem<T>(allocator,newCapacity);
			if ((T*)newMem)
			{
				arr.mem=newMem;
				u32 copyCount=newCapacity>oldCapacity?oldCapacity:newCapacity;
				msize copySize=sizeof(T)*copyCount;
				mem_cpy(newMem.ptr,oldMem.ptr,copySize);
				b32 oldMemFreed=free(allocator,oldMem);
				if (oldMemFreed)
				{
					result=peek(arr);
				}
				else
				{
					result.mem=oldMem;
				}
			}
			else
			{
				result=peek(arr);
			}
		}
		return result;
	}
}
