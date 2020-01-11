
template <typename T>
blk<T> allocator::alloc(u32 count)
{
	return (blk<T>)alloc((msize)(sizeof(T)*count));
}

template <typename T>
b32 allocator::free(blk<T>& block)
{
	blk<void> b=blk<void>(block);
	return free(b);
}

template <typename T>
b32 allocator::owns(const blk<T>& block) const
{
	return owns(blk<void>(block));
}