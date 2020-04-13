
namespace dggt
{
	template <typename T>
	T* cache_malloc(msize size)
	{
		return (T*)cache_malloc(sizeof(T)*size);
	}

	template <typename T>
	b32 cache_free(T* ptr,msize size)
	{
		return cache_free((void*)ptr,sizeof(T)*size);
	}
}
