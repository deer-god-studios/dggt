
namespace dggt
{
	template <typename T>
	T* alloc(free_list_alloc* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T>
	b32 free(free_list_alloc* a,T* ptr,u32 count)
	{
		return free(ptr,count*sizeof(T));
	}

	template <typename T>
	b32 owns(const free_list_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}
}
