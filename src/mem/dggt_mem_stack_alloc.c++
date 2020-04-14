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

	
		b32 stack_clear(msize* used,stack_state* prevState,
				u32* stateCount)
		{
			*used=0;
			*prevState=0;
			*stateCount=0;
			return true;
		}

	}

	void* malloc(stack_alloc* a,msize size)
	{
		if (a)
		{
			return dggt_internal_::stack_alloc(a->val.pge.ptr,
					a->val.pge.size,
					&a->val.used,size);
		}
		else
		{
			return 0;
		}
	}

	b32 free(stack_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a)
		{
			result=dggt_internal_::stack_free(a->val.pge.ptr,
					a->val.pge.size,
					a->val.prevState,&a->val.used,ptr,size);
		}
		return result;
	}
	
	b32 clear(stack_alloc* a)
	{
		return dggt_internal_::stack_clear(&a->val.used,
				&a->val.prevState,&a->val.stateCount);
	}

}
