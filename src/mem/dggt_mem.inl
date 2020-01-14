

namespace dggt
{
	template <typename T>
	T* cache_alloc(u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			msize size=*count*sizeof(T);
			result=(T*)cache_alloc(&size);
			*count=size/sizeof(T);
		}
		return result;
	}

	template <typename T>
	blk<T> cache_alloc(u32 count)
	{
		blk<T> result;
		if (count)
		{
			result.mem=cache_alloc<T>(&count);
			result.count=count;
		}
		return result;
	}

	template <typename T>
	b32 cache_free(T* ptr,u32 count)
	{
		return cache_free((void*)ptr,(msize)count*sizeof(T));
	}

	template <typename T>
	b32 cache_free(blk<T> block)
	{
		return cache_free(block.mem,block.count);
	}

	template <alloc_t A>
	allocator<A> create_alloc(msize size)
	{
		void* buffPtr=cache_alloc(&size);
		allocator<A> result=allocator<A>();
		if (buffPtr)
		{
			result=allocator<A>(buffPtr,size);
		}
		return result;
	}

	template <alloc_t A,u32 SIZE>
	allocator<A,SIZE> create_alloc()
	{
		return allocator<A,SIZE>();
	}

	template <alloc_t A>
	b32 destroy_alloc(allocator<A>* alloc)
	{
		return alloc&&cache_free(alloc->buff.mem,alloc->buff.size);
	}
}
