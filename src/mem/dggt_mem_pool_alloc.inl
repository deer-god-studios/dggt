
namespace dggt
{

	template <typename T>
	allocator<alloc_t::POOL>::allocator(T* ptr,u32 count)
		: allocator(ptr,sizeof(T)*count,sizeof(T)) { }

	template <typename T>
	allocator<alloc_t::POOL>::allocator(blk<T> buffer)
		: allocator(buffer.mem,buffer.count) { }

	template <typename T>
	blk<T> allocator<alloc_t::POOL>::alloc()
	{
		return (T*)alloc<void>();
	}

	template <typename T>
	b32 allocator<alloc_t::POOL>::free(T* ptr)
	{
		return free((void*)ptr);
	}

	template <typename T>
	b32 allocator<alloc_t::POOL>::free(blk<T> block)
	{
		return free(block.ptr);
	}

	template <typename T>
	b32 allocator<alloc_t::POOL>::owns(const blk<T> block) const
	{
		return owns(blk<void>(block));
	}
}
