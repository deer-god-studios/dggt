
namespace dggt
{
	template <typename T>
	T* alloc(store_alloc* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T>
	b32 free(store_alloc* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 owns(const store_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,count*sizeof(T));
	}
}
