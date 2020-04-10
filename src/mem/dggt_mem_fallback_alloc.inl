
namespace dggt
{
	template <typename P,typename F>
	fallback_alloc<P,F>::fallback_alloc()
	{
		p=0;
		f=0;
	}

	template <typename P,typename F>
	fallback_alloc<P,F>::fallback_alloc(P* primary,F* fallback)
	: fallback_alloc()
	{
		p=primary;
		f=fallback;
	}

	template <typename P,typename F>
	void* malloc(fallback_alloc<P,F>* a,msize size)
	{
		void* result=malloc(a->p,size);
		if (result==0)
		{
			result=malloc(a->f,size);
		}
		return result;
	}

	template <typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,void* ptr,msize size)
	{
		b32 result=free(a->p,ptr,size);
		if (!result)
		{
			result=free(a->f,ptr,size);
		}
		return result;
	}
	
	template <typename P,typename F>
	b32 clear(fallback_alloc<P,F>* a)
	{
		return clear(a->p)&&clear(a->f);
	}

	template <typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,
			const void* ptr,msize size)
	{
		return owns(a->p,ptr,size)||owns(a->f,ptr,size);
	}

	template <typename P,typename F>
	stack_state save_stack(fallback_alloc<P,F>* a)
	{
		stack_state result=save_stack(a->p);
		if (result==SAVE_STACK_FAIL)
		{
			result=save_stack(a->f);
		}
		return result;
	}

	template <typename P,typename F>
	b32 restore_stack(fallback_alloc<P,F>* a,
			stack_state state)
	{
		b32 result=restore_stack(a->p,state);
		if (!result)
		{
			result=restore_stack(a->f,state);
		}
		return result;
	}

	template <typename P,typename F>
	b32 is_stack_balanced(const fallback_alloc<P,F>* a)
	{
		return is_stack_balanced(a->p)&&
			is_stack_balanced(a->f);
	}

	template <typename P,typename F>
	msize used_mem(const fallback_alloc<P,F>* a)
	{
		return used_mem(a->p)+used_mem(a->f);
	}

	template <typename P,typename F>
	msize available_mem(const fallback_alloc<P,F>* a)
	{
		return available_mem(a->p)+used_mem(a->f);
	}

	template <typename T,typename P,typename F>
	T* malloc(fallback_alloc<P,F>* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,T* ptr,msize size)
	{
		return free(a,ptr,sizeof(T)*size);
	}

	template <typename T,typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,
			const T* ptr,msize size)
	{
		return owns(a,ptr,sizeof(T)*size);
	}
}
