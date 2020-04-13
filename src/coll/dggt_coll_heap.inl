
namespace dggt
{
	template <typename T,typename A>
	heap<T> create_heap(A* allocator,msize capacity)
	{
		heap<T> result={};
		result.mem=malloc_heap_mem(allocator,capacity);
		result.count=0;
		return result;
	}

	template <typename T,typename A>
	heap<T> create_heap(A* allocator,array<T>& arr)
	{
		create_max_heap(allocator,arr);
	}

	template <typename T,typename A>
	heap<T> create_max_heap(A* allocator,array<T>& arr)
	{
		heap<T> result={};
		result.mem=malloc_heap_mem(allocator,get_capacity(arr));
		result.count=get_count(arr);
		// copy array
		for (msize i=0;i<get_count(arr);++i)
		{
			result.mem[i]=arr[i];
		}
		// build_max_heap algorithm
		for (heap<T>::iter it=get(result,get_count(result)/2);
				!it.is_end();--it)
		{
			heapify(result,it);
		}
		return result;
	}

	template <typename T,typename A>
	heap<T> create_min_heap(A* allocator,array<T>& arr)
	{
		heap<T> result={};
		result.mem=malloc_heap_mem(allocator,get_capacity(arr));
		result.count=get_count(arr);
		// copy array
		for (msize i=0;i<get_count(arr);++i)
		{
			result.mem[i]=arr[i];
		}
		// build_max_heap algorithm
		for (heap<T>::iter it=get(result,get_count(result)/2);
				!it.is_end();--it)
		{
			min_heapify(result,it);
		}
		return result;
	}

	template <typename T,typename A>
	heap<T>::iter destroy_heap(heap<T>& hp,A* allocator)
	{
		heap<T>::iter result=get_iter(hp,allocator);
		if (free(allocator,hp.mem))
		{
			result=heap<T>::iter();
		}
		return result;
	}

	template <typename T,typename A>
	heap<T>::iter push(heap<T>& hp,A* allocator)
	{
		heap<T>::iter result=get_iter(hp);
		push(hp.mem,allocator);
		result=peek(hp);
		return result;
	}

	template <typename T,typename A>
	heap<T>::iter push(heap<T>& hp,const T& val,A* allocator)
	{
		heap<T>::iter result=push(hp,allocator);
		if (is_mem_valid(result))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,typename A>
	heap<T>::iter pop(heap<T>& hp,A* allocator)
	{
		heap<T>::iter result=get_iter(hp);
		pop(hp.mem,allocator);
		result=peek(hp);
		return result;
	}

	template <typename T>
	heap<T>::iter peek(heap<T>& hp);

	template <typename T>
	heap<T>::iter get(heap<T>& hp,u32 index);

	template <typename T,typename A>
	heap<T>::iter clear(heap<T>& hp,A* allocator);

	template <typename T>
	u32 get_count(const heap<T>& hp);

	template <typename T>
	heap<T>::iter get_iter(heap<T>& hp);

	template <typename T>
	b32 contains(heap<T>& hp,const T& item);

	template <typename T>
	u32 get_capacity(heap<T>& hp);

	template <typename T,typename F=float32>
	F get_load_factor(heap<T>& hp);

	template <typename T>
	heap<T>::iter get_parent(heap<T>& hp,heap<T>::iter& node);

	template <typename T>
	heap<T>::iter get_left_child(heap<T>& hp,heap<T>::iter& node);

	template <typename T>
	heap<T>::iter get_right_child(heap<T>& hp,heap<T>::iter& node);

	template <typename T,typename A>
	heap<T>::iter resize(heap<T>& hp,u32 newCapacity,A* allocator);

	template <typename T,typename A>
	heap<T>::iter insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter max_heap_insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter min_heap_insert(heap<T>& hp,const T& val,A* a);

	template <typename T,typename A>
	heap<T>::iter heapify(heap<T>& hp,heap<T>::iter& node);
	
	template <typename T,typename A>
	heap<T>::iter max_heapify(heap<T>& hp,heap<T>::iter& node);

	template <typename T,typename A>
	heap<T>::iter min_heapify(heap<T>& hp,heap<T>::iter& node);
}
