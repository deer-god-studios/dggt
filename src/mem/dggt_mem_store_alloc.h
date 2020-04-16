#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct store_block
	{
		store_block* next;
	};

	struct store_alloc:allocator<store_alloc>
	{
		store_block* store;
		msize bCount;
		msize bSize;

		store_alloc(msize blockSize)
			: allocator<store_alloc>(this),
			store(0),bCount(0),
			bSize(blockSize<sizeof(store_block)?
					sizeof(store_block):blockSize) { }
	};

	void* malloc(store_alloc* a,msize size=0);
	
	b32 free(store_alloc* a,void* ptr,msize size=0);
	
	b32 clear(store_alloc* a);
	
	b32 owns(const store_alloc* a,const void* ptr,msize size);

	msize get_used(const store_alloc* a);
	
	msize get_available(const store_alloc* a);
}

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
