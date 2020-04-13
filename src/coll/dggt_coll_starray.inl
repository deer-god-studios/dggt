
namespace dggt
{
	template <typename T,msize S>
	typename starray<T,S>::iter push(starray<T,S>& starr)
	{
		typename starray<T,S>::iter result=typename starray<T,S>::iter(starr);
		if (get_count(starr)<S)
		{
			++starr.count;
			result=peek(starr);
		}
		return result;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter push(starray<T,S>& starr,const T& val)
	{
		typename starray<T,S>::iter result=push(starr);
		if (is_mem_valid(result)&&
				result==peek(starr))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter peek(starray<T,S>& starr)
	{
		typename starray<T,S>::iter result=typename starray<T,S>::iter(starr);
		if (get_count(starr))
		{
			result=get(starr,get_count(starr)-1);
		}
		return result;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter pop(starray<T,S>& starr)
	{
		typename starray<T,S>::iter result=typename starray<T,S>::iter(starr);
		if (get_count(starr))
		{
			--starr.count;
			result=peek(starr);
		}
		return result;
	}

	template <typename T,msize S>
	msize get_count(starray<T,S>& starr)
	{
		return starr.count;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter get(starray<T,S>& starr,msize offset)
	{
		typename starray<T,S>::iter result=typename starray<T,S>::iter(starr);
		if (offset<starr.count)
		{
			result.current=starray_key<T,S>((T*)starr.mem+offset,offset);
		}
		return result;
	}

	template <typename T,msize S>
	typename starray<T,S>::iter get_iter(starray<T,S>& starr)
	{
		return get(starr,0);
	}
}
