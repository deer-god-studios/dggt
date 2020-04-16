#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	void* malloc(stack_alloc* a,msize size)
	{
		void* result=0;
		if (a)
		{
			result=malloc(&a->linAlloc,size);
		}
		return result;
	}

	b32 free(stack_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a)
		{
			if (ptr_add(get_buff_ptr(a),get_used(a))==
					ptr_add(ptr,size))
			{
				a->linAlloc.used-=size;
				if (a->prevState==get_used(a))
				{
					restore_stack(a,get_used(a));
				}
			}
		}
		return result;
	}
	
	b32 clear(stack_alloc* a)
	{
		b32 result=clear(&a->linAlloc);
		if (result)
		{
			a->prevState=0;
			a->stateCount=0;
		}
		return result;
	}

	stack_state save_stack(stack_alloc* a)
	{
		stack_state result=SAVE_STACK_FAIL;
		if (a)
		{
			result=get_used(a);
			++a->stateCount;
		}
		return result;
	}

	b32 restore_stack(stack_alloc* a,stack_state state)
	{
		b32 result=false;
		if (a)
		{
			if (state!=SAVE_STACK_FAIL&&
					state==a->prevState)
			{
				a->linAlloc.used=state;
				--a->stateCount;
			}
		}
		return result;
	}

	b32 is_stack_balanced(stack_alloc* a)
	{
		return a?a->stateCount==0:true;
	}

	void* get_buff_ptr(stack_alloc* a)
	{
		return a?get_buff_ptr(&a->linAlloc):0;
	}

	const void* get_buff_ptr(const stack_alloc* a)
	{
		return a?get_buff_ptr(&a->linAlloc):0;
	}

	msize get_used(const stack_alloc* a)
	{
		return a?get_used(&a->linAlloc):0;
	}

	msize get_available(const stack_alloc* a)
	{
		return a?get_used(&a->linAlloc):0;
	}
}
