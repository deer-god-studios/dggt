#include "dggt_mem_pool_alloc.h"

namespace dggt
{
	namespace dggt_internal_
	{
		void* pool_alloc(pool_block** pool,msize* used,msize blockSize)
		{
			void* result=0;
			if (*pool)
			{
				result=*pool;
				*pool=(*pool)->next;
				*used+=blockSize;
			}
			return result;
		}

		b32 pool_owns(const void* buff,msize buffSize,
				const void* ptr,msize size,msize blockSize)
		{
			return ptr>=buff&&
				ptr_add(ptr,size)<=ptr_add(buff,buffSize)&&
				size==blockSize;
		}

		b32 pool_free(pool_block** pool,
				void* buff,msize buffSize,
				msize* used,void* ptr,msize size,
				msize blockSize)
		{
			b32 result=false;
			if (pool_owns(buff,buffSize,ptr,size,blockSize))
			{
				pool_block* newBlock=(pool_block*)ptr;
				newBlock->next=*pool;
				*pool=newBlock;
				*used-=blockSize;
				result=true;
			}
			return result;
		}

		void pool_init(pool_block** pool,void* buff,msize buffSize,
				u32* blockCount,msize* used,msize blockSize)
		{
			*used=0;
			*blockCount=(u32)(buffSize/blockSize);
			*pool=(pool_block*)buff;
			for (u32 i=0;i<*blockCount;++i)
			{
				pool_block* current=*pool+i;
				current->next=
					i==*blockCount-1?0:current+1;
			}
		}
	}

	pool_alloc<0>::pool_alloc()
	{
		baseAlloc=allocator<>(ALLOC_T_POOL);
		buff=0;
		buffSize=0;
		used=0;
		blockCount=0;
		pool=0;
		blockSize=0;
	}

	pool_alloc<0>::pool_alloc(void* ptr,msize size,msize blockSize)
	: pool_alloc()
	{
		buff=ptr;
		buffSize=size;
		this->blockSize=blockSize;
		dggt_internal_::pool_init(&pool,buff,buffSize,&blockCount,
				&used,blockSize);
	}

	void* alloc(pool_alloc<>* a,msize size)
	{
		return dggt_internal_::pool_alloc(&a->pool,&a->used,
				a->blockSize);
	}

	b32 free(pool_alloc<>* a,void* ptr,msize size)
	{
		return dggt_internal_::pool_free(
				&a->pool,a->buff,a->buffSize,
				&a->used,ptr,size,
				a->blockSize);
	}

	b32 clear(pool_alloc<>* a)
	{
		dggt_internal_::pool_init(
				&a->pool,a->buff,a->buffSize,&a->blockCount,&a->used,
				a->blockSize);
		return true;
	}

	b32 owns(const pool_alloc<>* a,const void* ptr,msize size)
	{
		return dggt_internal_::pool_owns(
				a->buff,a->buffSize,ptr,size,
				a->blockSize);
	}
	
	stack_state save_stack(pool_alloc<>* a)
	{
		return SAVE_STACK_FAIL;
	}
	
	b32 restore_stack(pool_alloc<>* a,stack_state state)
	{
		return false;
	}
	
	b32 is_stack_balanced(const pool_alloc<>* a)
	{
		return true;
	}
	
	msize used_mem(const pool_alloc<>* a)
	{
		return a->used;
	}

	msize available_mem(const pool_alloc<>* a)
	{
		return a->buffSize-a->used;
	}
}
