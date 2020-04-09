
namespace dggt
{

	template <typename T,typename M,typename C>
	iter<T,M,C>::iter(MemType mem,CollType* coll)
	:this->mem(mem),this->coll(coll) { }

	template <typename T,typename M,typename C>
	T& iter<T,M,C>::operator*()
	{
		return *mem;
	}

	template <typename T,typename M,typename C>
	const T& iter<T,M,C>::operator*() const
	{
		return *mem;
	}

	template <typename T,typename M,typename C>
	explicit operator iter<T,M,C>::M&()
	{
		return mem;
	}
}
