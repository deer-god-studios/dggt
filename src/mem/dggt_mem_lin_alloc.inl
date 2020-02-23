
namespace dggt
{
	template <typename T>
	T* alloc(lin_alloc* a,u32 count)
	{
		return (T*)alloc(a,count*sizeof(T));
	}

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count)
	{
		return 0;
	}

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}
}
