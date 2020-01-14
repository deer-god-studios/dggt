namespace dggt
{

	template <typename T>
	blk<T> allocator<alloc_t::LINEAR_STORE>::alloc(u32 count)
	{
		return (blk<T>)alloc(count*sizeof(T));
	}

	template <typename T>
	T* allocator<alloc_t::LINEAR_STORE>::alloc(u32* count)
	{
		T* result=0;
		u32 c=count?*count:1;
		blk<T> b=alloc(c);
		result=b.mem;
		if (count)
		{
			*count=b.count;
		}

		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::LINEAR_STORE>::free(T* ptr)
	{
		return free(blk<T>(ptr,1));
	}

	template <typename T>
	b32 allocator<alloc_t::LINEAR_STORE>::free(blk<T> block)
	{
		return free(blk<void>(block,block.size*sizeof(T));
	}
	template <typename T>
	b32 allocator<alloc_t::LINEAR_STORE>::owns(const T* ptr) const
	{
		return owns(blk<T>(ptr,1)); 
	}
	template <typename T>
	b32 allocator<alloc_t::LINEAR_STORE>::owns(const blk<T> block) const
	{
		return owns(blk<void>(block)); 
	}
}
