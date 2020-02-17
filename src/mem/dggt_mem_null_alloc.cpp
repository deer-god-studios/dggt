
#include "dggt_mem_null_alloc.h"

namespace dggt
{
	blkv alloc(null_alloc* a,msize size)
	{
		return blkv();
	}

	void* alloc(null_alloc* a,msize* size)
	{
		return 0;
	}

	b32 free(null_alloc* a,void* ptr,msize size)
	{
		return 0;
	}

	b32 free(null_alloc* a,blkv block)
	{
		return 0;
	}

	b32 clear(null_alloc* a)
	{
		return 0;
	}
	
	b32 owns(const null_alloc* a,const void* ptr,msize size)
	{
		return ptr==0&&size==0;
	}

	b32 owns(const null_alloc* a,const blkv block)
	{
		return block.mem==0&&block.size==0;
	}

	stack_state save_stack(null_alloc* a)
	{
		return 0;
	}

	b32 restore_stack(null_alloc* a,stack_state state)
	{
		return 0;
	}

	b32 is_stack_balanced(null_alloc* a)
	{
		return 1;
	}
}
