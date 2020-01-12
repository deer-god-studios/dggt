

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
	allocator<A>* create_alloc(msize size)
	{
		u32 allocCount=1;
		allocator<A>* result=cache_alloc<allocator<A>>(&allocCount);
		if (result)
		{
			void* buffPtr=cache_alloc(&size);
			if (buffPtr)
			{
				if (A==alloc_t::POOL)
				{
					*((allocator<alloc_t::POOL>*)result)
						=allocator<alloc_t::POOL>(buffPtr,size,8);
				}
				else
				{
					*result=allocator<A>(buffPtr,size);
				}
			}
		}
		return result;
	}

	template <alloc_t A>
	b32 destroy_alloc(allocator<A>* alloc)
	{
		return alloc&&
			cache_free(alloc->buff.mem,alloc->buff.size)&&
			cache_free(alloc,1);
	}
}
