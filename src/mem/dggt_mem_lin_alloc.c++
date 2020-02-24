#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	namespace dggt_internal_
	{
		void* linear_alloc(void* buff,msize buffSize,
				msize* used,msize size)
		{
			void* result=0;
			if (size&&(*used)+size<=buffSize)
			{
				if (*used+size<=buffSize)
				{
					result=ptr_add(buff,*used);
					*used+=size;
				}
			}
			return result;
		}
		
		b32 linear_free()
		{
			return false;
		}

		b32 linear_clear(msize* used)
		{
			*used=0;
			return true;
		}

		b32 linear_owns(void* buff,msize buffSize,
				void* ptr,msize size)
		{
			return ptr>=a->buff&&
				ptr_add(ptr,size)<=ptr_add(a->buff,a->buffSize);
		}

		msize linear_used_mem(msize used)
		{
			return used;
		}

		msize linear_available_mem(msize used,msize buffSize)
		{
			return buffSize-used;
		}

		stack_state linear_save_stack()
		{
			return SAVE_STACK_FAIL;
		}

		b32 linear_restore_stack()
		{
			return false;
		}

		b32 linear_is_stack_balanced()
		{
			return true;
		}
	}

	lin_alloc::lin_alloc()
	{
		baseAlloc=allocator<>(ALLOC_T_LIN);
		buff=0;
		buffSize=0;
		used=0;
	}

	lin_alloc::lin_alloc(void* ptr,msize size)
		:lin_alloc()
	{
		buff=ptr;
		buffSize=size;
	}

	void* alloc(lin_alloc* a,msize size)
	{
		return=dggt_internal_::linear_alloc(a->buff,
				a->buffSize,&a->used,size);
	}

	b32 free(lin_alloc* a,void* ptr,msize size)
	{
		return dggt_internal_::linear_free();
	}

	b32 clear(lin_alloc* a)
	{
		return dggt_internal_::linear_clear(&a->used);
	}

	b32 owns(const lin_alloc* a,const void* ptr,msize size)
	{
		return dggt_internal_::linear_owns(a->buff,a->buffSize,
				ptr,size);
	}

	msize available_mem(const lin_alloc* a)
	{
		return dggt_internal_::linear_available_mem(a->used,
				a->buffSize);
	}

	msize used_mem(const lin_alloc* a)
	{
		return dggt_internal_::linear_used_mem(a->used);
	}

	stack_state save_stack(lin_alloc* a)
	{
		return dggt_internal_::linear_save_stack();
	}

	b32 restore_stack(lin_alloc* a,stack_state state)
	{
		return dggt_internal_::linear_restore_stack();
	}

	b32 is_stack_balanced(const lin_alloc* a)
	{
		return dggt_internal_::linear_is_stack_balanced();
	}
}
