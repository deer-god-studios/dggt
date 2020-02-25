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
				*head=*head->next;
				++*blockCount;
			}
			return result;
		}

		b32 store_owns(void* ptr,msize size,msize blockSize)
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

	store_alloc<0>::store_alloc(msize blockSize)
	{
		ASSERT(blockSize>=sizeof(store_block));
		baseAlloc(allocator<>(ALLOC_T_STORE));
		head=0;
		blockCount=0;
		this->blockSize=blockSize;
	}

	void* alloc(store_alloc<>* a,msize size)
	{
		return dggt_internal_::store_alloc(&a->head,
				&a->blockCount,size);
	}

	b32 free(store_alloc<>* a,void* ptr,msize size)
	{
		return dggt_internal_::store_free(&a->head,&a->blockCount,
				ptr,size,blockSize);
	}
	
	b32 clear(store_alloc<>* a)
	{
		return dggt_internal_::store_clear(&a->head,&a->blockCount);
	}

	b32 owns(const store_alloc<>* a,const void* ptr,msize size)
	{
		return dggt_internal_::store_owns(ptr,size,a->blockSize);
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
		return dggt_internal_::store_used_mem(a->blockCount);
	}

	msize available_mem(const store_alloc<>* a)
	{
		return dggt_internal_::store_available_mem(a->blockCount);
	}

	T* alloc(store_alloc<>* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	b32 free(store_alloc<>* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	b32 owns(const store_alloc<>* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}
}
