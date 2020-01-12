
namespace dggt
{

	template <typename T>
	blk<T>::blk(T* mem,size_t count)
	{
		this->mem=mem;
		this->count=count;
	}
	template <typename T>
	blk<T>::blk()
	: blk(0,0) { }

	template <typename T>
	blk<T>::blk(const blk<T>& other)
	:blk(other.mem,other.count) { }

	template <typename T>
	blk<T> blk<T>::operator+(uint32_t offset) const
	{
		blk<T> result;
		if (offset%sizeof(T)==0)
		{
			result=blk<T>(mem+offset,count-offset);
		}

		return result;
	}

	template <typename T>
	blk<T> blk<T>::operator-(uint32_t offset) const
	{
		return blk<T>(mem-offset,count+offset);
	}

	template <typename T>
	blk<T>& blk<T>::operator=(const blk<T>& rhs)
	{
		if (this!=&rhs)
		{
			mem=rhs.mem;
			count=rhs.count;
		}
		return *this;
	}

	template <typename T>
	uint32_t blk<T>::operator==(const blk<T>& rhs) const
	{
		return this==&rhs||(mem==rhs.mem&&count==rhs.count);
	}

	template <typename T>
	uint32_t blk<T>::operator!=(const blk<T>& rhs) const
	{
		return this!=&rhs&&(mem!=rhs.mem||count!=rhs.count);
	}

	template <typename T>
	T* blk<T>::data()
	{
		return mem;
	}

	template <typename T>
	const T* blk<T>::data() const
	{
		return mem;
	}

	template <typename T>
	T* blk<T>::operator->()
	{
		return mem;
	}

	template <typename T>
	const T* blk<T>::operator->() const
	{
		return mem;
	}

	template <typename T>
	T& blk<T>::operator*()
	{
		return *mem;
	}
	template <typename T>
	const T& blk<T>::operator*() const
	{
		return *mem;
	}
	template <typename T>
	T& blk<T>::operator[](uint32_t index)
	{
		return *(mem+index);
	}

	template <typename T>
	const T& blk<T>::operator[](uint32_t index) const
	{
		return *(mem+index);
	}

	template <typename T>
	blk<T>::operator T*()
	{
		return mem;
	}

	template <typename T>
	template <typename S>
	blk<T>::operator blk<S>()
	{
		msize totalSize=count*sizeof(T);
		u32 newCount=totalSize/sizeof(S);
		return blk<S>((S*)mem,newCount);
	}

	template <typename T>
	blk<T> blk_alloc(u32 count)
	{
		T* ptr=(T*)mem_alloc(count*sizeof(T));
		if (ptr==0)
		{
			count=0;
		}
		return blk<T>(ptr,count);
	}

	template <typename T>
	void blk_free(blk<T> block)
	{
		mem_free(block.ptr,block.size*sizeof(T));
	}

	template <typename T>
	void blk_cpy(blk<T> dest,blk<T> src,u32 count)
	{
		blk_cpy(blk<void>(dest),blk<void>(src),sizeof(T)*count);
	}
}
