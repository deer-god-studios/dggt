#include "dggt_mem_store_alloc.h"

namespace dggt
{
	store_alloc::store_alloc(msize blockSize)
	{
		ASSERT(blockSize>=sizeof(store_block));
		baseAlloc=allocator(ALLOC_T_STORE);
		head=0;
		blockCount=0;
	}

	void* alloc(store_alloc* a,msize size)
	{
		void* result=0;

		if (head)
		{
			result=(void*)head;
			a->head=head->next;
			--a->blockCount;
		}
		return result;
	}
	
	b32 free(store_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (owns(a,ptr,size))
		{
			store_block* newBlock=(store_block*)ptr;
			newBlock->next=a->head;
			a->head=newBlock;
			++a->blockCount;
			result=true;
		}
		return result;
	}
	
	b32 clear(store_alloc* a)
	{
		a->head=0;
		a->blockCount=0;
	}
	
	b32 owns(const store_alloc* a,const void* ptr,msize size)
	{
		return size==a->blockSize;
	}
	
	msize available_mem(const store_alloc* a)
	{
		return (msize)a->blockSize*a->blockCount;
	}
	
	msize used_mem(const store_alloc* a)
	{
		return available_mem(a)?0:MAX_MSIZE;
	}
	
	stack_state save_stack(store_alloc* a)
	{
		return SAVE_STACK_FAIL;
	}

	b32 restore_stack(store_alloc* a,stack_state state)
	{
		return false;
	}

	b32 is_stack_balanced(store_alloc* a)
	{
		return true;
	}
}
