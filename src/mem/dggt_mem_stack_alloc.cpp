#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	stack_alloc::stack_alloc()
	{
		baseAlloc=allocator(ALLOC_T_STACK);
		buff=0;
		buffSize=0;
		used=0;
		stateCount=0;
		prevState=0;
	}

	stack_alloc::stack_alloc(void* ptr,msize size)
		:stack_alloc()
	{
		buff=ptr;
		buffSize=size;
	}

	void* alloc(stack_alloc* a,msize size)
	{
		void* result=0;
		if (size)
		{
			if (a->used+size<=a->buffSize)
			{
				result=ptr_add(a->buff,a->used);
				a->used+=size;
			}
		}
		return result;
	}

	b32 free(stack_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (owns(a,ptr,size)&&
				a->used-size>=(msize)a->prevState)
		{
			void* allocEndAddr=ptr_add(a->buff,a->used);
			void* blkEndAddr=ptr_add(ptr,size);
			if (allocEndAddr==blkEndAddr)
			{
				a->used-=size;
				result=true;
			}
		}
		return result;
	}

	stack_state save_stack(stack_alloc* a)
	{
		stack_state result=(stack_state)a->used;
		a->prevState=result;
		++a->stateCount;
		return result;
	}

	b32 restore_stack(stack_alloc* a,stack_state state)
	{
		b32 result=state==a->prevState;
		if (result)
		{
			a->used=state;
			--a->stateCount;
		}
		return result;
	}

	b32 clear(stack_alloc* a)
	{
		a->used=0;
		a->stateCount=0;
		a->prevState=0;
		return true;
	}

	b32 owns(const stack_alloc* a,const void* ptr,msize size)
	{
		return ptr>=a->buff&&
			ptr_add(ptr,size)<=ptr_add(a->buff,a->buffSize);
	}


	b32 is_stack_balance(const stack_alloc* a)
	{
		return a->stateCount==0;
	}

	msize available_mem(const stack_alloc* a)
	{
		return a->buff.size-a->used;
	}

	msize used_mem(const stack_alloc* a)
	{
		return a->used;
	}
}
