namespace dggt
{
	template <typename T>
	T* malloc(lin_alloc* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}
}
