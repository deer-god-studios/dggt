
namespace dggt
{
	// free_list_alloc

	template <typename T>
	T* alloc(free_list_alloc* a,u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			msize size=*count*sizeof(T);
			result=(T*)alloc(a,&size);
		}
		return result;
	}

	template <typename T>
	blk<T> alloc(free_list_alloc* a,u32 count)
	{
		return (blk<T>)alloc(a,(msize)count*sizeof(T));
	}

	template <typename T>
	b32 free(free_list_alloc* a,T* ptr,u32 count)
	{
		return free(ptr,(msize)count*sizeof(T));
	}

	template <typename T>
	b32 free(free_list_alloc* a,blk<T> block)
	{
		return free(block.mem,block.count);
	}

	template <typename T>
	b32 owns(const free_list_alloc* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}

	template <typename T>
	b32 owns(const free_list_alloc* a,const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	// free_list_stalloc

	template <u32 BUFFSIZE>
	void* alloc(free_list_stalloc<BUFFSIZE>* a,msize* size)
	{
		return alloc(&a->a_,size);
	}
	
	template <u32 BUFFSIZE>
	blkv alloc(free_list_stalloc<BUFFSIZE>* a,msize size)
	{
		return alloc(&a->a_,size);
	}

	template <u32 BUFFSIZE,typename T>
	T* alloc(free_list_stalloc<BUFFSIZE>* a,u32* count)
	{
		return alloc(&a->a_,count);
	}
	
	template <u32 BUFFSIZE,typename T>
	blk<T> alloc(free_list_stalloc<BUFFSIZE>* a,u32 count)
	{
		return alloc(&a->a_,count);
	}

	template <u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <u32 BUFFSIZE>
	b32 free(free_list_stalloc<BUFFSIZE>* a,blkv block)
	{
		return free(&a->a_,block);
	}

	template <u32 BUFFSIZE,typename T>
	b32 free(free_list_stalloc<BUFFSIZE>* a,T* ptr,u32 count)
	{
		return free(&a->a_,ptr,count);
	}

	template <u32 BUFFSIZE,typename T>
	b32 free(free_list_stalloc<BUFFSIZE>* a,blk<T> block)
	{
		return free(&a->a_,block);
	}

	template <u32 BUFFSIZE>
	b32 clear(free_list_stalloc<BUFFSIZE>* a)
	{
		return clear(&a->a_);
	}

	template <u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <u32 BUFFSIZE>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const blkv block)
	{
		return owns(&a->a_,block);
	}

	template <u32 BUFFSIZE,typename T>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const T* ptr,u32 count)
	{
		return owns(&a->a_,ptr,count);
	}

	template <u32 BUFFSIZE,typename T>
	b32 owns(const free_list_stalloc<BUFFSIZE>* a,const blk<T> block)
	{
		return owns(&a->a_,block);
	}

	template <u32 BUFFSIZE>
	msize available_mem(const free_list_stalloc<BUFFSIZE>* a)
	{
		return available_mem(&a->a_);
	}

	template <u32 BUFFSIZE>
	msize used_mem(const free_list_stalloc<BUFFSIZE>* a)
	{
		return used_mem(&a->a_);
	}

	template <u32 BUFFSIZE>
	stack_state save_stack(free_list_stalloc<BUFFSIZE>* a)
	{
		return save_stack(&a->a_);
	}

	template <u32 BUFFSIZE>
	b32 restore_stack(free_list_stalloc<BUFFSIZE>* a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <u32 BUFFSIZE>
	b32 is_stack_balanced(free_list_stalloc<BUFFSIZE>* a)
	{
		return is_stack_balanced(&a->a_);
	}
}
