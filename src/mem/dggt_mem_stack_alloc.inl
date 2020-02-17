
namespace dggt
{
	// stack_alloc
	
	template <typename T>
	T* alloc(stack_alloc* a,u32* count)
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
		}
		else
		{
			msize size=sizeof(T);
			result=(T*)alloc(a,&size);
		}
		return result;
	}

	template <typename T>
	blk<T> alloc(stack_alloc* a,u32 count)
	{
		return (blk<T>)alloc(a,count*sizeof(T));
	}

	template <typename T>
	b32 free(stack_alloc* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 free(stack_alloc* a,blk<T> block)
	{
		return free(a,block.mem,block.count);
	}

	template <typename T>
	b32 owns(stack_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 owns(stack_alloc* a,const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	// stack_stalloc

	template <u32 SIZE>
	allocator<ALLOC_T_STACK,SIZE>::allocator()
	{
		a_=allocator((void*)buff,SIZE);
	}

	template <u32 SIZE>
	void* alloc(stack_stalloc<SIZE>* a,msize* size)
	{
		return alloc(&a->a_,size);
	}
	
	template <u32 SIZE>
	vblk alloc(stack_stalloc<SIZE>* a,msize size)
	{
		alloc(&a->a_,size);
	}

	template <u32 SIZE,typename T>
	T* alloc(stack_stalloc<SIZE>* a,u32* count)
	{
		alloc(&a->a_,count);
	}
	
	template <u32 SIZE,typename T>
	blk<T> alloc(stack_stalloc<SIZE>* a,u32 count)
	{
		return alloc(&a->a_,count);
	}

	template <u32 SIZE>
	b32 free(stack_stalloc<SIZE>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <u32 SIZE>
	b32 free(stack_stalloc<SIZE>* a,vblk block)
	{
		return free(&a->a_,block);
	}

	template <u32 SIZE,typename T>
	b32 free(stack_stalloc<SIZE>* a,T* ptr,u32 count)
	{
		return free(&a->a_,ptr,count);
	}

	template <u32 SIZE,typename T>
	b32 free(stack_stalloc<SIZE>* a,blk<T> block)
	{
		return free(&a->a_,block);
	}

	template <u32 SIZE>
	b32 clear(stack_stalloc<SIZE>* a)
	{
		return clear(&a->a_);
	}

	template <u32 SIZE>
	b32 owns(const stack_stalloc<SIZE>* a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <u32 SIZE>
	b32 owns(const stack_stalloc<SIZE>* a,const vblk block)
	{
		return owns(&a->a_,block);
	}

	template <u32 SIZE,typename T>
	b32 owns(const stack_stalloc<SIZE>* a,const T* ptr,u32 count)
	{
		return owns(&a->a_,ptr,count);
	}

	template <u32 SIZE,typename T>
	b32 owns(const stack_stalloc<SIZE>* a,const blk<T> block)
	{
		return owns(&a->a_,block);
	}

	template <u32 SIZE>
	msize available_mem(const stack_stalloc<SIZE>* a)
	{
		return available_mem(&a->a_);
	}

	template <u32 SIZE>
	msize used_mem(const stack_stalloc<SIZE>* a)
	{
		return used_mem(&a->a_);
	}

	template <u32 SIZE>
	stack_state save_stack(stack_stalloc<SIZE>* a)
	{
		return save_stack(&a->a_);
	}

	template <u32 SIZE>
	b32 restore_stack(stack_stalloc<SIZE>* a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <u32 SIZE>
	b32 is_stack_balanced(stack_stalloc<SIZE>* a)
	{
		return is_stack_balanced(&a->a_);
	}
}
