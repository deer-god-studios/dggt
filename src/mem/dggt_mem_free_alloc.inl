
namespace dggt
{
	template <typename T>
	T* malloc(free_alloc* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T>
	b32 free(free_alloc* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	b32 owns(const free_alloc* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}
}
