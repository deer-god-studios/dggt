
namespace dggt
{
	// lin_alloc
	// {

	template <typename T>
	T* alloc(lin_alloc* a,u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			msize size=*count*sizeof(T);
			result=(T*)alloc(a,&size);
			if (result)
			{
				*count=size/sizeof(T);
			}
			else
			{
				*count=0;
			}
		}
		else
		{
			msize size=sizeof(T);
			result=(T*)alloc(a,&size);
			if (result&&count)
			{
				*count=size/sizeof(T);
			}
		}
		return result;
	}

	template <typename T>
	blk<T> alloc(lin_alloc* a,u32 count)
	{
		return (blk<T>)alloc(a,(msize)count*sizeof(T));
	}

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count)
	{
		return 0;
	}

	template <typename T>
	b32 free(lin_alloc* a,blk<T> block)
	{
		return 0;
	}

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 owns(const lin_alloc* a,const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	// }

	// lin_stalloc<SIZE>
	// {
	template <u32 SIZE>
	allocator<ALLOC_T_LINEAR,SIZE>::allocator()
	{
		a_=lin_alloc_<0>((void*)buff,SIZE);
	}

	template <u32 SIZE>
	void* alloc(lin_stalloc<SIZE>* a,msize* size)
	{
		return alloc(&a->a_,size);
	}

	template <u32 SIZE>
	vblk alloc(lin_stalloc<SIZE>* a,msize size)
	{
		return alloc(&a->a_,size);
	}

	template <u32 SIZE,typename T>
	T* alloc(lin_stalloc<SIZE>* a,u32* count)
	{
		return alloc(&a->a_,count);
	}

	template <u32 SIZE,typename T>
	blk<T> alloc(lin_stalloc<SIZE>* a,u32 count)
	{
		return alloc(&a->a_,count);
	}

	template <u32 SIZE>
	b32 free(lin_stalloc<SIZE>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <u32 SIZE>
	b32 free(lin_stalloc<SIZE>* a,vblk block)
	{
		return free(&a->a_,block);
	}

	template <u32 SIZE,typename T>
	b32 free(lin_stalloc<SIZE>* a,T* ptr,u32 count)
	{
		return free(&a->a_,ptr,count);
	}

	template <u32 SIZE,typename T>
	b32 free(lin_stalloc<SIZE>* a,blk<T> block)
	{
		return free(&a->a_,block);
	}

	template <u32 SIZE>
	b32 clear(lin_stalloc<SIZE>* a)
	{
		return clear(&a->a_);
	}

	template <u32 SIZE>
	b32 owns(const lin_stalloc<SIZE>* a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <u32 SIZE>
	b32 owns(const lin_stalloc<SIZE>* a,const vblk block)
	{
		return owns(&a->a_,block);
	}

	template <u32 SIZE,typename T>
	b32 owns(const lin_stalloc<SIZE>* a,const T* ptr,u32 count)
	{
		return owns(&a->a_,ptr,count);
	}

	template <u32 SIZE,typename T>
	b32 owns(const lin_stalloc<SIZE>* a,const blk<T> block)
	{
		return owns(&a->a_,block);
	}

	template <u32 SIZE>
	msize available_mem(const lin_stalloc<SIZE>* a)
	{
		return available_mem(&a->a_);
	}

	template <u32 SIZE>
	msize used_mem(const lin_stalloc<SIZE>* a)
	{
		return used_mem(&a->a_);
	}

	template <u32 SIZE>
	stack_state save_stack(lin_stalloc<SIZE>* a)
	{
		return 0;
	}

	template <u32 SIZE>
	b32 restore_stack(lin_stalloc<SIZE>* a,stack_state state)
	{
		return 0;
	}

	template <u32 SIZE>
	b32 is_stack_balanced(lin_stalloc<SIZE>* a)
	{
		return 1;
	}

	// }
}
