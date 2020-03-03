
namespace dggt
{
	template <typename T>
	T* cache_alloc(u32 count)
	{
		return (T*)cache_alloc(sizeof(T)*count);
	}

	template <typename T>
	b32 cache_free(T* ptr,u32 count)
	{
		return cache_free((void*)ptr,sizeof(T)*count);
	}
}
