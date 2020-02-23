
namespace dggt
{
	template <typename T>
	T* alloc(allocator* a,u32 count)
	{
		msize size*count*sizeof(T);
		return (T*)alloc(a,size);
	}

	template <typename T>
	b32 free(allocator* a,T* ptr,u32 count)
	{
		msize size=count*sizeof(T);
		return free(a,ptr,size);
	}

	template <typename T>
	b32 owns(const allocator* a,const T* ptr,u32 count)
	{
		msize size=count*sizeof(T);
		return owns(a,ptr,size);
	}
}
