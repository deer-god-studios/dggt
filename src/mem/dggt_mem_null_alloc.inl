
namespace dggt
{
	template <typename T>
	T* alloc(null_alloc* a,u32* count)
	{
		return 0;
	}

	template <typename T>
	blk<T> alloc(null_alloc* a,u32 count)
	{
		return blk<T>();
	}

	template <typename T>
	b32 free(null_alloc* a,T* ptr,u32 count)
	{
		return 0;
	}

	template <typename T>
	b32 free(null_alloc* a,blk<T> block)
	{
		return 0;
	}

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,u32 count)
	{
		return ptr==0&&count==0;
	}

	template <typename T>
	b32 owns(const null_alloc* a,const blk<T> block)
	{
		return block.mem==0&&block.count==0;
	}


}
