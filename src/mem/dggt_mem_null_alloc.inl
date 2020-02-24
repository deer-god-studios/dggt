
namespace dggt
{
	template <typename T>
	T* alloc(null_alloc* a,u32 count)
	{
		return 0;
	}

	template <typename T>
	b32 free(null_alloc* a,T* ptr,u32 count)
	{
		return false;
	}

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,u32 count)
	{
		return ptr==0&&count==0;
	}
}
