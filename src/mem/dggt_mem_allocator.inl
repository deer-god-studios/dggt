
namespace dggt
{
	template <typename T>
	T* malloc(allocator* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T>
	page<T> malloc_page(allocator* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T>
	b32 free(allocator* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	b32 free(allocator* a,page<T>& pge)
	{
		return free(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
	
	template <typename T>
	b32 owns(const allocator* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	b32 owns(const allocator* a,page<T>& pge)
	{
		return owns(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
}
