#include "dggt_mem_fallback_alloc.h"

namespace dggt
{
	fallback_alloc::fallback_alloc()
	{
		baseAlloc=allocator(ALLOC_T_FALLBACK);
		p=0;
		f=0;
	}

	fallback_alloc::fallback_alloc(allocator* primary,
			allocator* fallback)
		:fallback_alloc()
	{
		p=primary;
		f=fallback;
	}

	void* alloc(fallback_alloc* a,msize size)
	{
		void* result=alloc(a->p,size);
		if (result==0)
		{
			result=alloc(a->f,size);
		}
		return result;
	}

	b32 free(fallback_alloc* a,void* ptr,msize size)
	{
		b32 result=free(a->p,ptr,size);
		if (!result)
		{
			result=free(a->f,ptr,size);
		}
		return result;
	}

	b32 clear(fallback_alloc* a)
	{
		return clear(a->p)&&clear(a->f);
	}

	b32 owns(const fallback_alloc* a,const void* ptr,msize size)
	{
		return owns(a->p,ptr,size)||owns(a->f,ptr,size);
	}

	msize available_mem(const fallback_alloc* a)
	{
		return available_mem(a->p)+available_mem(a->f);
	}

	msize used_mem(const fallback_alloc* a)
	{
		return used_mem(a->p)+used_mem(a->f);
	}

	stack_state save_stack(fallback_alloc* a)
	{
		stack_state result=SAVE_STACK_FAIL;
		if (a->p.TYPE==ALLOC_T_STACK||
				a->p.TYPE==ALLOC_T_AUTOSTACK)
		{
			result=save_stack(a->p);
		}
		else if (a->f.TYPE==ALLOC_T_STACK||
				a->f.TYPE==ALLOC_T_AUTOSTACK)
		{
			result=save_stack(a->f);
		}
		return result;
	}

	b32 restore_stack(fallback_alloc* a,stack_state state)
	{
		b32 result=false;
		if (a->p.TYPE==ALLOC_T_STACK||
				a->p.TYPE==ALLOC_T_AUTOSTACK)
		{
			result=restore_stack(a->p,state);
		}
		else if (a->f.TYPE==ALLOC_T_STACK||
				a->f.TYPE==ALLOC_T_AUTOSTACK)
		{
			result=restore_stack(a->f,state);
		}
		return result;
	}

	b32 is_stack_balanced(fallback_alloc* a)
	{
		return is_stack_balanced(a->p)&&
			is_stack_balanced(a->f);
	}
}
