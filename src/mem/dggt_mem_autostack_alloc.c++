#include "dggt_mem_autostack.h"

namespace dggt
{
	autostack_alloc::autostack_alloc()
	{
		a=0;
		prevState=0;
	}

	autostack_alloc::autostack_alloc(const autostack_alloc& other)
	{
		a=&other.a;
		prevState=save_state(a);
	}

	autostack_alloc::autostack_alloc(const stack_alloc& other)
	{
		a=&other;
		prevState=save_state(a);
	}

	autostack_alloc& autostack_alloc=(const autostack_alloc& rhs)
	{
		if (this!=rhs)
		{
			a=rhs.a;
			prevState=save_state(a);
		}
		return *this;
	}

	autostack_alloc& autostack_alloc=(const stack_alloc& rhs)
	{
		a=rhs;
		prevState=save_state(a);
		return *this;
	}

	autostack_alloc::~autostack_alloc()
	{
		restore_stack(a,prevState);
	}

	void* malloc(autostack_alloc* a,msize size)
	{
		return malloc(a->a,size);
	}

	b32 free(autostack_alloc* a,void* ptr,msize size)
	{
		return free(a->a,ptr,size);
	}
	
	b32 clear(autostack_alloc* a)
	{
		return clear(a->a);
	}

	b32 owns(const autostack_alloc* a,const void* ptr,msize size)
	{
		return owns(a->a,ptr,size);
	}

	stack_state save_stack(autostack_alloc* a)
	{
		return save_stack(a->a);
	}

	b32 restore_stack(autostack_alloc* a,stack_state state)
	{
		return restore_stack(a->a,state);
	}

	b32 is_stack_balanced(const autostack_alloc* a)
	{
		return is_stack_balanced(a->a);
	}

	msize used_mem(const autostack_alloc* a)
	{
		return used_mem(a->a);
	}

	msize available_mem(const autostack_alloc* a)
	{
		return available_mem(a->a);
	}
}
