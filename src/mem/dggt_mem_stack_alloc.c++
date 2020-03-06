#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	namespace dggt_internal_
	{
		void* stack_alloc(void* buff,msize buffSize,
				msize* used,msize size)
		{
			void* result=0;
			if (size&&(*used)+size<=buffSize)
			{
				result=ptr_add(buff,*used);
				*used+=size;
			}
			return result;
		}

		b32 stack_owns(void* buff,msize buffSize,
				const void* ptr,msize size)
		{
			return ptr>buff&&
				ptr_add(ptr,size)<=ptr_add(buff,buffSize);
		}

		b32 stack_free(void* buff,msize buffSize,stack_state prevState,
				msize* used,void* ptr,msize size)
		{
			b32 result=false;
			if (stack_owns(buff,buffSize,ptr,size)&&
					*used-size>=(msize)prevState)
			{
				void* allocEndAddr=ptr_add(buff,*used);
				void* blkEndAddr=ptr_add(ptr,size);
				if (allocEndAddr==blkEndAddr)
				{
					result=true;
					*used-=size;
				}
			}
			return result;
		}

		stack_state stack_save_stack(msize used,stack_state prevState)
		{
			stack_state result=(stack_state)used;
			prevState=result;
			return result;
		}
		
		b32 stack_clear(msize* used,stack_state* prevState,
				u32* stateCount)
		{
			*used=0;
			*prevState=0;
			*stateCount=0;
			return true;
		}

		stack_state stack_save_stack(msize used,
				stack_state* prevState,u32* stateCount)
		{
			stack_state result=(stack_state)used;
			*prevState=result;
			++*stateCount;
			return result;
		}

		b32 stack_restore_stack(msize used,
				stack_state* prevState,
				u32* stateCount)
		{
			stack_state result=(stack_state)used;
			*prevState=result;
			++*stateCount;
			return result;
		}

		b32 stack_is_stack_balanced(u32 stateCount)
		{
			return stateCount==0;
		}

		msize stack_used_mem(msize used)
		{
			return used;
		}

		msize stack_available_mem(msize used,msize buffSize)
		{
			return buffSize-used;
		}
	}

	stack_alloc::stack_alloc()
	{
		buff=0;
		buffSize=0;
		used=0;
		prevState=0;
		stateCount=0;
	}

	stack_alloc::stack_alloc(void* ptr,msize size)
		: stack_alloc()
	{
		buff=ptr;
		buffSize=size;
	}

	void* alloc(stack_alloc* a,msize size)
	{
		return dggt_internal_::stack_alloc(a->buff,a->buffSize,
			&a->used,size);
	}

	b32 free(stack_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a)
		{
			result=dggt_internal_::stack_free(a->buff,a->buffSize,
					a->prevState,&a->used,ptr,size);
		}
		return result;
	}
	
	b32 clear(stack_alloc* a)
	{
		return dggt_internal_::stack_clear(&a->used,
				&a->prevState,&a->stateCount);
	}

	b32 owns(const stack_alloc* a,const void* ptr,msize size)
	{
		return dggt_internal_::stack_owns(a->buff,a->buffSize,
				ptr,size);
	}

	stack_state save_stack(stack_alloc* a)
	{
		return dggt_internal_::stack_save_stack(a->used,
				&a->prevState,&a->stateCount);
	}

	b32 restore_stack(stack_alloc* a,stack_state state)
	{
		return dggt_internal_::stack_restore_stack(a->used,
				&a->prevState,&a->stateCount);
	}

	b32 is_stack_balanced(const stack_alloc* a)
	{
		return dggt_internal_::stack_is_stack_balanced(a->stateCount);
	}

	msize used_mem(const stack_alloc* a)
	{
		return dggt_internal_::stack_used_mem(a->used);
	}

	msize available_mem(const stack_alloc* a)
	{
		return dggt_internal_::stack_available_mem(a->used,a->buffSize);
	}
}
