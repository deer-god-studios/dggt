
template <typename T>
blk<T> allocator<alloc_t::FREE_LIST>::alloc(u32 count)
{
	blk<T> result=(blk<T>)alloc(count*sizeof(T));
	
	return result;
}

template <typename T>
void allocator<alloc_t::FREE_LIST>::free(blk<T>& block)
{
	blk<void> mem=blk<void>(block.mem,sizeof(T)*block.count);
	free(mem);
}

template <typename T>
b32 allocator<alloc_t::FREE_LIST>::owns(const blk<T>& block) const
{
	blk<void> mem=blk<void>(block.mem,
			block.mem?sizeof(T)*block.count:0);
	return owns(mem);
}
