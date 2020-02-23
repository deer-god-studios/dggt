#include "dggt_mem_pool_alloc.h"

namespace dggt
{
	pool_alloc::pool_alloc(msize blockSize)
	{
		ASSERT(blockSize>=sizeof(pool_block));
		baseAlloc=allocator(ALLOC_T_POOL);
		buff=0;
		buffSize=0;
		used=0;
		pool=0;
		bSize=blockSize;
	}
	
	pool_alloc::pool_alloc(void* ptr,msize size,msize blockSize)
	: pool_alloc(blockSize)
	{
		buff=ptr;
		buffSize=size;
		pool->next=0;
		blockCount=(u32)(size/bSize);
		pool=(pool_block*)ptr;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block* current=pool+i;
			current->next=
				i==blockCount-1?0:current+1;
		}
	}

	void* alloc(pool_alloc* a,msize size)
	{
		void* result=0;
		if (a->pool)
		{
			result=a->pool;
			a->pool=a->pool->next;
			a->used+=a->bSize;
		}
		return result;
	}
	
	b32 free(pool_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (owns(a,ptr,a->blockSize))
		{
			pool_block* newBlock=(pool_block*)ptr;
			newBlock->next=a->pool;
			a->pool=newBlock;
			a->used-=a->bSize;
			result=true;
		}
		return result;
	}
	
	b32 clear(pool_alloc* a)
	{
		pool=(pool_block*)buff;
		for (u32 i=0;i<a->blockCount;++i)
		{
			pool_block* current=a->pool+i;
			pool->next=i==a->blockCount-1?0:current+1;

		}
		a->used=0;
		return true;
	}
	
	b32 owns(const pool_alloc* a,const void* ptr,msize size)
	{
		return ptr>=a->buff&&
			ptr_add(ptr,size)<=ptr_add(a->buff,a->buffSize)&&
			size==a->blockSize;
	}

	msize available_mem(const pool_alloc* a)
	{
		return a->buffSize-a->used;
	}

	msize used_mem(const pool_alloc* a)
	{
		return a->used;
	}

	stack_state save_stack(pool_alloc* a)
	{
		return SAVE_STACK_FAIL;
	}

	b32 restore_stack(pool_alloc* a,stack_state state)
	{
		return false;
	}

	b32 is_stack_balanced(const pool_alloc* a)
	{
		return true;
	}
}
