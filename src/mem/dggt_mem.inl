

template <typename T>
blk<T> dggt_mem_cache_alloc(u32 count)
{
	blk<void> block=dggt_mem_cache_alloc(count*sizeof(T));
	return blk<T>(block.mem,block.mem?count:0);
}

template <typename T>
void dggt_mem_cache_free(blk<T>& block)
{
	blk<void> b=blk<void>(block);
	dggt_mem_cache_free(b);
}
