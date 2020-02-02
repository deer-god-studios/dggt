
namespace dggt
{
	template <typename T>
	blk<T> allocator<alloc_t::STORE>::alloc()
	{
		blk<T> result=NULL_BLK<T>;
		if (head)
		{
			result=blk<T>((T*)head,sizeof(T));
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::free(T* ptr,u32 count)
	{
		b32 result=1;
		for (u32 i=0;i<count;++i)
		{
			result=result&&free(blk<T>(ptr,1));
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::free(blk<T> block)
	{
		return free(blk<void>(block));
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::owns(const T* ptr) const
	{
		return sizeof(T)==blockSize;
	}
	
	template <typename T>
	b32 allocator<alloc_t::STORE>::owns(const blk<T> block) const
	{
		return owns(block.mem)&&
			block.count==1;
	}
}
