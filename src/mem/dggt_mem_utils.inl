namespace dggt
{
	template <typename T>
	void zero_struct(T* ptr)
	{
		zero_mem(ptr,sizeof(T));
	}
}
