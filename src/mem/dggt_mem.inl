

namespace dggt
{
	template <typename T>
	blk<T> cache_alloc(u32 count)
	{
		blk<void> block=cache_alloc(count*sizeof(T));
		return blk<T>(block.mem,block.mem?count:0);
	}

	template <typename T>
	void cache_free(blk<T>& block)
	{
		blk<void> b=blk<void>(block);
		cache_free(b);
	}
}
