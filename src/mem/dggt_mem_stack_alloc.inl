
template <typename T>
b32 allocator<alloc_t::STACK>::owns(const blk<T>& block) const
{
	return block.mem>=this->block.mem&&
		block.mem+block.count<=ptr_add(this->block.mem,this->block.size);
}

template <typename T>
blk<T> allocator<alloc_t::STACK>::alloc(u32 count)
{
	blk<T> result;
	if (used+count*sizeof(T)<=block.size)
	{
		result=blk<T>((T*)(ptr_add(block.mem,used)),count);
		used+=count*sizeof(T);
	}
	return result;
}
