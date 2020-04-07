
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,msize S>
		starray_iter<T,S> get_def_starray_iter(
				starray<T,S>* starr)
		{
			starray_iter<T,S> result={};
			result.starr=starr;
			return result;
		}
	}

	template <typename T,msize S>
	starray_iter<T,S> push(starray<T,S>* starr)
	{
		starray_iter<T,S> result=dggt_internal_::get_def_starray_iter(
				starr);
		if (starr&&
				get_count(starr)<S)
		{
			result.starrayMem=starr->mem;
			result.currentOffset=get_count(starr);
			++starr->count;
		}
		return result;
	}

	template <typename T,msize S>
	starray_iter<T,S> push(starray<T,S>* starr,const T& val)
	{
		starray_iter<T,S> result=push(starr);
		if (is_mem_valid(result))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,msize S>
	starray_iter<T,S> peek(starray<T,S>* starr)
	{
		starray_iter<T,S> result=dggt_internal_::get_def_starray_iter(starr);
		if (starr&&
				get_count(starr))
		{
			result.starrayMem=starr->mem;
			result.currentOffset=get_count(starr)-1;
		}
		return result;
	}

	template <typename T,msize S>
	starray_iter<T,S> pop(starray<T,S>* starr)
	{
		starray_iter<T,S> result=dggt_internal_::get_def_starray_iter(starr);
		if (starr&&get_count(starr))
		{
			result.starrayMem=starr->mem;
			--starr->count;
		}
		return result;
	}

	template <typename T,msize S>
	msize get_count(starray<T,S>* starr)
	{
		return starr?starr->count:0;
	}

	template <typename T,msize S>
	starray_iter<T,S> get(starray<T,S>* starr,msize offset)
	{
		starray_iter<T,S> result=
			dggt_internal_::get_def_starray_iter(starr);
		if (starr)
		{
			result.starrayMem=starr->mem;
			if (offset<S)
			{
				result.currentOffset=offset;
			}
		}
		return result;
	}

	template <typename T,msize S>
	starray_iter<T,S> get_iter(starray<T,S>* starr)
	{
		return get(starr,0);
	}
}
