#ifndef _DGGT_MEM_ALLOC_H_

#include "dggt_mem_blk.h"

namespace dggt
{
	enum alloc_t:u32
	{
		NONE,
		LINEAR,
		STACK,
		FREE_LIST,
		POOL
	};

	struct pool_block;
	struct free_block;
	typedef msize stack_state;

	struct allocator
	{
		alloc_t type;
		blk<void> buffer;
		u32 used;

		// stack allocator
		u32 stateCount;
		stack_state prevState;

		// pool allocator
		msize blockSize;
		msize blockCount;
		pool_block* pool;

		// free list allocator
		free_block* freeList;

		allocator();
		allocator(alloc_t type,msize blockSize=0);
		allocator(alloc_t type,blk<void>& block,msize blockSize=0);
		allocator(alloc_t type,void* ptr,msize size,msize blockSize=0);

		msize available_mem() const;
		msize used_mem() const;

		blk<void> alloc(msize size=0);
		template <typename T>
		blk<T> alloc(u32 count=1);
		b32 free(blk<void>& block);
		b32 free(void* ptr,msize size);
		template <typename T>
		b32 free(blk<T>& block);
		template <typename T>
		b32 free(T* ptr,msize size);
		void clear();

		b32 owns(const blk<void>& block) const;
		template <typename T>
		b32 owns(const blk<T>& block) const;

		stack_state save_stack();
		b32 restore_stack(stack_state state);
		b32 is_stack_balanced() const;
	};
}
#include "dggt_mem_alloc.inl"

#define _DGGT_MEM_ALLOC_H_
#endif
