
namespace dggt
{
	template <typename T>
	T* alloc(autostack_alloc* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T>
	b32 free(autostack_alloc* a,T* ptr,u32 count)
	{
		return free(a,(void*)ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 owns(const autostack_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,(void*)ptr,sizeof(T)*count);
	}
}
