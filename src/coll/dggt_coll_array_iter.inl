
namespace dggt
{
	template <typename T>
	b32 is_end(const array_iter<T>& it)
	{
		return it.current>=it.mem.size;
	}

	template <typename T>
	b32 advance(array_iter<T>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			++it.current;
			result=true;
		}
		return result;
	}

	template <typename T>
	T& get(array_iter<T>& it)
	{
		return *(it.mem);
	}

	template <typename T>
	const T& get(const array_iter<T>& it)
	{
		return *(it.mem);
	}

	template <typename T>
	T* get_ptr(array_iter<T>& it)
	{
		return (T*)it.mem;
	}

	template <typename T>
	const T* get_ptr(const array_iter<T>& it)
	{
		return (T*)it.mem;
	}
}
