
namespace dggt
{
	template <typename T>
	blk<T> allocator<alloc_t::LINEAR>::alloc(u32 count)
	{
		return (blk<T>)alloc((msize)count*sizeof(T));
	}

	template <typename T>
	T* allocator<alloc_t::LINEAR>::alloc(u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			msize size=*count*sizeof(T);
			result=(T*)alloc(&size);
			if (result)
			{
				*count=size/sizeof(T);
			}
			else
			{
				*count=0;
			}
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::LINEAR>::owns(const blk<T> block) const
	{
		return owns(block.mem)&&
			block.mem+block.count<=ptr_add(buff.mem,buff.size);
	}

	template <typename T>
	b32 allocator<alloc_t::LINEAR>::owns(const T* ptr) const
	{
		return owns((void*)ptr);
	}


}
