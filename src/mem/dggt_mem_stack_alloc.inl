
namespace dggt
{
	template <typename T>
	blk<T> allocator<alloc_t::STACK>::alloc(u32 count)
	{
		return (blk<T>)alloc(count*sizeof(T));
	}

	template<typename T>
	T* allocator<alloc_t::STACK>::alloc(u32* count)
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
		}
		else
		{
			msize size=sizeof(T);
			result=(T*)alloc(&size);
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::STACK>::free(blk<T> block)
	{
		return free<T>(block.mem,block.count);
	}

	template <typename T>
	b32 allocator<alloc_t::STACK>::free(T* ptr,u32 count)
	{
		return free((void*)ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 allocator<alloc_t::STACK>::owns(const T* ptr) const
	{
		return owns((void*)ptr);
	}

	template <typename T>
	b32 allocator<alloc_t::STACK>::owns(blk<T> block)  const
	{
		return owns(block.mem)&&
			block.mem+block.count<=ptr_add(buff.mem,buff.size);
	}
}
