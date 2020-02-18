
namespace dggt
{
	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	struct allocator<ALLOC_T_FALLBACK,
	PTYPE,PU32...,PTYPES...,
	FTYPE,FU32s...,FTYPES>::allocator()
		p((palloc*)0),
		f((falloc*)0)
	{
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	struct allocator<ALLOC_T_FALLBACK,
	PTYPE,PU32...,PTYPES...,
	FTYPE,FU32s...,FTYPES>::allocator(
			palloc* primary,
			falloc* fallback)
	{
		p=primary;
		f=fallback;
	}


	void* alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			msize* size)
	{
		void* result=0;
		if (a->p)
		{
			result=alloc(a->p,size);
		}
		if (!result&&a->f)
		{
			result=alloc(a->f,size);
		}
		return result;
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	blkv alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			msize size)
	{
		blkv result=blkv();
		void* ptr=alloc(a,&size);
		result.mem=ptr;
		result.size=size;
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	T* alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			u32* count)
	{
		T* result=0;
		msize size=0;
		if (count)
		{
			size=sizeof(T)*(*count);
		}
		result=(T*)alloc(a,&size);
		if (count)
		{
			*count=size/sizeof(T);
		}
		return result;
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	blk<T> alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			u32 count)
	{
		blk<T> result=blk<T>();
		result.mem=alloc(a,&count);
		result.count=count;
		return result;
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			void* ptr,
			msize size)
	{
		b32 result=0;
		if (a->p)
		{
			result=free(p,ptr,size);
		}
		else if (a->f)
		{
			result=free(f,ptr,size);
		}
		return result;
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			blkv block)
	{
		void* ptr=block.mem;
		msize size=block.size;
		b32 result=free(a,ptr,size);
		return result;
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			T* ptr,
			u32 count)
	{
		msize size=block.count*sizeof(T);
		return free(a,ptr,size);
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			blk<T> block)
	{
		return free(block.mem,block.count);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 clear(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a)
	{
		b32 result=0;
		return clear(a->p)&&clear(a->f);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const void* ptr,
			msize size)
	{
		return owns(a->p,ptr,size)||owns(a->f,ptr,size);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const blkv block)
	{
		return owns(a,block.mem,block.size);
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const T* ptr,
			u32 count)
	{
		return owns(a,ptr,count*sizeof(T));
	}

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	msize available_mem(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a)
	{
		return available_mem(a->p)+available_mem(a->f);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	msize used_mem(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a)
	{
		reutnr used_mem(a->p)+used_mem(a->f);
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	stack_state save_stack(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a)
	{
		stack_state result=0;
		if (a->p)
		{
			result=save_stack(a->p);
		}
		else if (result==SAVE_STACK_FAIL&&a->f)
		{
			result=save_stack(a->f);
		}
		return result;
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 restore_stack(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			stack_state state)
	{
		b32 result=0;
		if (state!=SAVE_STACK_FAIL)
		{
			if (a->p)
			{
				result=restore_stack(a->p,state);
			}
			else if (!result||a->f)
			{
				result=restore_stack(a->f,state);
			}
		}
		return result;
	}

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 is_stack_balanced(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a)
	{
		return is_stack_balanced(a->p)&&is_stack_balanced(a->f);
	}
}
