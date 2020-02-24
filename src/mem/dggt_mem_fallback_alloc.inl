
namespace dggt
{

	template <msize PrimaryArg,msize FallbackArg>
	fallback_alloc<PrimaryArg,msize FallbackArg>::fallback_alloc()
	{
		baseAlloc(allocator<>(ALLOC_T_FALLBACK));
		p=0;
		f=0;
	}

	template <msize PrimaryArg,msize FallbackArg>
	fallback_alloc<PrimaryArg,msize FallbackArg>::fallback_alloc(
			allocator<PrimaryArg>* primary,
			allocator<FallbackArg>* fallback)
	: fallback_alloc()
	{
		p=primary;
		f=fallback;
	}

	template <msize PrimaryArg,msize FallbackArg>
	void* alloc(fallback_alloc<PrimaryArg,FallbackArg>* a,msize size)
	{
		void* result=alloc(a->p,size);
		if (result==0)
		{
			result=alloc(a->f,size);
		}
		return result;
	}

	template <msize PrimaryArg,msize FallbackArg>
	b32 free(fallback_alloc<PrimaryArg,FallbackArg>* a,void* ptr,msize size)
	{
		b32 result=free(a->p,ptr,size);
		if (!result)
		{
			result=free(a->f,ptr,size);
		}
		return result;
	}
	
	template <msize PrimaryArg,msize FallbackArg>
	b32 clear(fallback_alloc<PrimaryArg,FallbackArg>* a)
	{
		return clear(a->p)&&clear(a->f);
	}

	template <msize PrimaryArg,msize FallbackArg>
	b32 owns(const fallback_alloc<PrimaryArg,FallbackArg>* a,
			const void* ptr,msize size)
	{
		return owns(a->p,ptr,size)||owns(a->f,ptr,size);
	}

	template <msize PrimaryArg,msize FallbackArg>
	stack_state save_stack(fallback_alloc<PrimaryArg,FallbackArg>* a)
	{
		stack_state result=SAVE_STACK_FAIL;
		if (a->p.type==ALLOC_T_STACK)
		{
			result=save_stack(a->p);
		}
		else if (result==SAVE_STACK_FAIL&&
				a->f.type==ALLOC_T_STACK)
		{
			result=save_stack(a->f);
		}
		return result;
	}

	template <msize PrimaryArg,msize FallbackArg>
	b32 restore_stack(fallback_alloc<PrimaryArg,FallbackArg>* a,
			stack_state state)
	{
		b32 result=restore_stack(a->p,state);
		if (!result)
		{
			result=restore_stack(a->f,state);
		}
		return result;
	}

	template <msize PrimaryArg,msize FallbackArg>
	b32 is_stack_balanced(const fallback_alloc<PrimaryArg,FallbackArg>* a)
	{
		return is_stack_balanced(a->p)&&
			is_stack_balanced(a->f);
	}

	template <msize PrimaryArg,msize FallbackArg>
	msize used_mem(const fallback_alloc<PrimaryArg,FallbackArg>* a)
	{
		return used_mem(a->p)+used_mem(a->f);
	}

	template <msize PrimaryArg,msize FallbackArg>
	msize available_mem(const fallback_alloc<PrimaryArg,FallbackArg>* a)
	{
		return available_mem(a->p)+used_mem(a->f);
	}

	template <typename T,msize PrimaryArg,msize FallbackArg>
	T* alloc(fallback_alloc<PrimaryArg,FallbackArg>* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T,msize PrimaryArg,msize FallbackArg>
	b32 free(fallback_alloc<PrimaryArg,FallbackArg>* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T,msize PrimaryArg,msize FallbackArg>
	b32 owns(const fallback_alloc<PrimaryArg,FallbackArg>* a,
			const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}
}
