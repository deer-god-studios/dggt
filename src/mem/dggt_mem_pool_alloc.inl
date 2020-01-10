

template <typename T>
blk<T> allocator<alloc_t::POOL>::alloc()
{
	return (blk<T>)alloc();
}

template <typename T>
void allocator<alloc_t::POOL>::free(blk<T>& block)
{
	blk<void> mem=blk<void>(block.mem,sizeof(T)*block.count);
	free(mem);
}

template <typename T>
b32 allocator<alloc_t::POOL>::owns(const blk<T>& block) const
{
	blk<void> mem=blk<void>(block.mem,block.mem?sizeof(T)*block.count:0);
	return owns(mem);
}
