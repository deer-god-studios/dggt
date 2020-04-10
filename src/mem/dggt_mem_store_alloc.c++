#include "dggt_mem_store_alloc.h"

namespace dggt
{
	namespace dggt_internal_
	{
		void* store_alloc(store_block** head,
				u32* blockCount,msize size)
		{
			void* result=0;
			if (*head)
			{
				result=*head;
				*head=(*head)->next;
				++*blockCount;
			}
			return result;
		}

		b32 store_owns(const void* ptr,msize size,msize blockSize)
		{
			return size==blockSize;
		}

		b32 store_free(store_block** head,u32* blockCount,
				void* ptr,msize size,msize blockSize)
		{
			b32 result=false;
			if (store_owns(ptr,size,blockSize))
			{
				store_block* newBlock=(store_block*)ptr;
				newBlock->next=*head;
				*head=newBlock;
				++*blockCount;
				result=true;
			}
			return result;
		}

		b32 store_clear(store_block** head,u32* blockCount)
		{
			*head=0;
			*blockCount=0;
			return true;
		}

		msize store_used_mem(u32 blockCount)
		{
			return blockCount?0:MAX_MSIZE;
		}

		msize store_available_mem(u32 blockCount,msize blockSize)
		{
			return (msize)blockCount*blockSize;
		}
	}

	store_alloc<0>::store_alloc()
	{
		head=0;
		blockCount=0;
		blockSize=0;
	}

	store_alloc<0>::store_alloc(msize blockSize)
	{
		ASSERT(blockSize>=sizeof(store_block));
		head=0;
		blockCount=0;
		this->blockSize=blockSize;
	}

	void* malloc(store_alloc<>* a,msize size)
	{
		if (a)
		{
			return dggt_internal_::store_alloc(&a->head,
					&a->blockCount,size);
		}
		else
		{
			return 0;
		}
	}

	b32 free(store_alloc<>* a,void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::store_free(&a->head,&a->blockCount,
					ptr,size,a->blockSize);
		}
		else
		{
			return 0;
		}
	}
	
	b32 clear(store_alloc<>* a)
	{
		if (a)
		{
			return dggt_internal_::store_clear(&a->head,&a->blockCount);
		}
		else
		{
			return 0;
		}
	}

	b32 owns(const store_alloc<>* a,const void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::store_owns(ptr,size,a->blockSize);
		}
		else
		{
			return 0;
		}
	}

	stack_state save_stack(store_alloc<>* a)
	{
		return SAVE_STACK_FAIL;
	}

	b32 restore_stack(store_alloc<>* a,stack_state state)
	{
		return false;
	}

	b32 is_stack_balanced(const store_alloc<>* a)
	{
		return true;
	}

	msize used_mem(const store_alloc<>* a)
	{
		if (a)
		{
			return dggt_internal_::store_used_mem(a->blockCount);
		}
		else
		{
			return 0;
		}
	}

	msize available_mem(const store_alloc<>* a)
	{
		if (a)
		{
			return dggt_internal_::store_available_mem(a->blockCount,
					a->blockSize);
		}
		else
		{
			return 0;
		}
	}
}
