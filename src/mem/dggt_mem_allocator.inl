
namespace dggt
{
	template <typename D>
	allocator<D>::allocator(D* derivedAlloc/*,alloc_t allocType*/)
	{
		derived=derivedAlloc;
		//type=allocType;
	}

	template <typename D>
	vblk alloc(allocator<D>* a,msize size)
	{
		return alloc(a->derived,size);
	}

	template <typename D>
	void* alloc(allocator<D>* a,msize* size)
	{
		return alloc(a->derived,size);
	}

	template <typename D,typename T>
	blk<T> alloc(allocator<D>* a,u32 count)
	{
		return alloc(a->derived,count);
	}

	template <typename D,typename T>
	T* alloc(allocator<D>* a,u32* count)
	{
		return alloc(a->derived,count);
	}

	template <typename D>
	b32 free(allocator<D>* a,void* ptr,msize size)
	{
		return free(a->derived,ptr,size);
	}

	template <typename D>
	b32 free(allocator<D>* a,vblk block)
	{
		return free(a->derived,block);
	}

	template <typename D,typename T>
	b32 free(allocator<D>* a,T* ptr,u32 count)
	{
		return free(a->derived,ptr,count);
	}

	template <typename D,typename T>
	b32 free(allocator<D>* a,blk<T> block)
	{
		return free(a->derived,block);
	}

	template <typename D>
	b32 clear(allocator<D>* a)
	{
		return free(a->derived);
	}

	template <typename D>
	b32 owns(const allocator<D>* a,const void* ptr,msize size)
	{
		return owns(a->derived,ptr,size);
	}

	template <typename D,typename T>
	b32 owns(const allocator<D>* a,const blk<T> block)
	{
		return owns(a->derived,block);
	}
	
	template <typename D,typename T>
	b32 owns(const allocator<D>* a,const T* ptr,u32 count)
	{
		return owns(a->derived,ptr,count);
	}
}
