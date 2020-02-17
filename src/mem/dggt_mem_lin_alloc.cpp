#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	allocator<ALLOC_T_LINEAR>::allocator()
	{
		buff=blk<void>();
		used=0;
	}

	allocator<ALLOC_T_LINEAR>::allocator(void* ptr,msize size)
		:allocator()
	{
		buff.mem=ptr;
		buff.size=size;
	}

	allocator<ALLOC_T_LINEAR>::allocator(vblk block)
		:allocator(block.mem,block.size)
	{
	}

	void* alloc(lin_alloc* a,msize* size)
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

	vblk alloc(lin_alloc* a,msize size)
	{
		void* mem=alloc(a,&size);
		return vblk(mem,size);
	}

	b32 free(lin_alloc* a,void* ptr,msize size)
	{
		return 0;
	}

	b32 free(lin_alloc* a,vblk block)
	{
		return 0;
	}

	b32 clear(lin_alloc* a)
	{
		a->used=0;
		return 1;
	}

	b32 owns(const lin_alloc* a,const void* ptr,msize size)
	{
		return ptr>=a->buff.mem&&
			ptr_add(ptr,size)<=ptr_add(a->buff.mem,a->buff.size);
	}

	b32 owns(const lin_alloc* a,const vblk block)
	{
		return owns(a,block.mem,block.size);
	}

	msize available_mem(lin_alloc* a)
	{
		return a->buff.size-a->used;
	}

	msize used_mem(lin_alloc* a)
	{
		return a->used;
	}

	stack_state save_stack(lin_alloc* a)
	{
		return 0;
	}

	b32 restore_stack(lin_alloc* a,stack_state state)
	{
		return 0;
	}

	b32 is_stack_balanced(lin_alloc* a)
	{
		return 1;
	}
}
