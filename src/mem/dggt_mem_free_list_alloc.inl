
namespace dggt
{

	template <typename T>
	T* allocator<alloc_t::FREE_LIST>::alloc(u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			msize size=*count*sizeof(T);
			result=(T*)alloc(&size);
		}
		return result;
	}

	template <typename T>
	blk<T> allocator<alloc_t::FREE_LIST>::alloc(u32 count)
	{
		return (blk<T>)alloc((msize)count*sizeof(T));
	}

	template <typename T>
	b32 allocator<alloc_t::FREE_LIST>::free(T* ptr,u32 count)
	{
		return free(ptr,(msize)count*sizeof(T));
	}

	template <typename T>
	b32 allocator<alloc_t::FREE_LIST>::free(blk<T> block)
	{
		return free(block.mem,block.count);
	}

	template <typename T>
	b32 allocator<alloc_t::FREE_LIST>::owns(const T* ptr) const
	{
		return owns((void*)ptr);
	}

	template <typename T>
	b32 allocator<alloc_t::FREE_LIST>::owns(const blk<T> block) const
	{
		return owns(block.mem)&&
			block.mem+block.count<=ptr_add(buff.mem,buff.size);
	}
}
