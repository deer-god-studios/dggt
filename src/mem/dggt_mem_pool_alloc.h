#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_lin_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	typedef store_block pool_block;

	struct pool_alloc
		: allocator<pool_alloc>
	{
		lin_alloc linAlloc;
		store_alloc storeAlloc;

		pool_alloc(void* ptr,msize size,msize blockSize)
			:allocator<pool_alloc>(this),
			linAlloc(ptr,size),
			storeAlloc(blockSize)
		{
			ASSERT(size>=sizeof(store_block));
			msize count=size/storeAlloc.bSize;
			for (msize i=0;i<count;++i)
			{
					free<pool_block>(&storeAlloc,
							malloc<pool_block>(&linAlloc,storeAlloc.bSize));
			}
		}

		pool_alloc(vpage buff,msize blockSize)
			: pool_alloc(buff.ptr,buff.size,blockSize) { }
	};

	void* malloc(pool_alloc* a,msize size=0);
	
	b32 free(pool_alloc* a,void* ptr,msize size=0);
	
	b32 clear(pool_alloc* a);
	
	msize get_used(const store_alloc* a);

	msize get_available(const pool_alloc* a);

	b32 owns(const store_alloc* a,const void* ptr,msize size);
}

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
