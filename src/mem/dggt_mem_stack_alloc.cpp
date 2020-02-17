#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	allocator<ALLOC_T_STACK>::allocator()
	{
		buff=vblk();
		used=0;
		stateCount=0;
		prevState=0;
	}

	allocator<ALLOC_T_STACK>::allocator(void* ptr,msize size)
	{
		buff.mem=ptr;
		buff.size=size;
	}

	allocator<ALLOC_T_STACK>::allocator(vblk block)
		:stack_alloc_(block.mem,block.size)
	{
	}

	void* alloc(stack_alloc* a,msize* size)
	{
		void* result=0;
		if (size&&*size)
		{
			if (a->used+*size<=a->buff.size)
			{
				result=ptr_add(a->buff.mem,a->used);
				a->used+=*size;
			}
			else
			{
				*size=0;
			}
		}
		else
		{
			msize s=4;
			if (a->used+s<=a->buff.size)
			{
				result=ptr_add(a->buff.mem,a->used);
				a->used+=s;
			}
		}
		return result;
	}

	vblk alloc(stack_alloc* a,msize size)
	{
		void* result=alloc(&size);
		return vblk(result,size);
	}

	b32 free(stack_alloc* a,void* ptr,msize size)
	{
		b32 result=0;
		vblk b=vblk(ptr,size);
		if (owns(b)&&
				a->used-size>=(msize)a->prevState)
		{
			void* allocEndAddr=ptr_add(a->buff.mem,a->used);
			void* blkEndAddr=ptr_add(ptr,size);
			if (allocEndAddr==blkEndAddr)
			{
				a->used-=size;
				result=1;
			}
		}
		return result;
	}

	b32 free(stack_alloc* a,vblk block)
	{
		return free(a,block.mem,block.size);
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
		used=0;
		stateCount=0;
		prevState=0;
		return 1;
	}

	b32 is_stack_balance(const stack_alloc* a)
	{
		return a->stateCount==0;
	}

	b32 owns(const stack_alloc* a,const void* ptr,msize size)
	{
		return ptr>=buff.mem&&
			ptr_add(ptr,size)<=ptr_add(buff.mem,buff.size);
	}

	b32 owns(const stack_alloc* a,const vblk block)
	{
		return owns(a,block.mem,block.size);
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
