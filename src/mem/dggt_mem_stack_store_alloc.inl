
namespace dggt
{
	template <typename T>
	blk<T> allocator<alloc_t::STACK_STORE>::alloc(u32 count)
	{
		return (blk<T>)alloc(count*sizeof(T));
	}

	template <typename T>
	T* allocator<alloc_t::STACK_STORE>::alloc(u32* count)
	{
		msize size=count?*count*sizeof(T):sizeof(T);
		return (T*)alloc(&size);
	}

	template <typename T>
	b32 allocator<alloc_t::STACK_STORE>::owns(const T* ptr) const
	{
		return owns(blk<T>(ptr,sizeof(T)));
	}

	template <typename T>
	b32 allocator<alloc_t::STACK_STORE>::owns(const blk<T> block) const
	{
		return owns(blk<void>(block));
	}

}
