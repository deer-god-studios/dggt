
namespace dggt
{
	template <typename T>
	T* alloc(null_alloc* a,msize size)
	{
		return 0;
	}

	template <typename T>
	b32 free(null_alloc* a,T* ptr,msize size)
	{
		return false;
	}

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,msize size)
	{
		return ptr==0&&size==0;
	}
}
