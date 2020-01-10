

template <typename T>
blk<T> xmem_cache_alloc(u32 count)
{
	blk<void> block=xmem_cache_alloc(count*sizeof(T));
	return blk<T>(block.mem,block.mem?count:0);
}

template <alloc_t A>
allocator<A> create_alloc(msize size)
{
	allocator<A> result=allocator<A>();
	if (xmem_is_initialized())
	{
		blk<void> allocBlock=xmem_cache_alloc(size);
		result=allocator<A>(allocBlock);
	}
	return result;
}

template <alloc_t A>
void free_alloc(allocator<A>& alloc)
{
	if (xmem_is_initialized())
	{
		xmem_cache_free(alloc.block);
		alloc=allocator<A>();
	}
}
