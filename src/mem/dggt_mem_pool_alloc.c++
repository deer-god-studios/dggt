#include "dggt_mem_pool_alloc.h"

namespace dggt
{
	void* malloc(pool_alloc* a,msize size)
	{
		return malloc(&a->storeAlloc);
	}
	
	b32 free(pool_alloc* a,void* ptr,msize size)
	{
		return free(&a->storeAlloc,ptr);
	}
	
	b32 clear(pool_alloc* a)
	{
		b32 result=0;
		if (a)
		{
			clear(&a->storeAlloc);
			clear(&a->linAlloc);
			msize count=get_capacity(&a->linAlloc)/a->storeAlloc.bSize;
			for (msize i=0;i<count;++i)
			{
				free<pool_block>(&a->storeAlloc,
						malloc<pool_block>(&a->linAlloc,a->storeAlloc.bSize));
			}
		}
		return result;
	}
	
	msize get_used(const pool_alloc* a)
	{
		return get_capacity(&a->linAlloc)-get_available(&a->storeAlloc);
	}

	msize get_available(const pool_alloc* a)
	{
		return get_available(&a->storeAlloc);
	}

	b32 owns(const pool_alloc* a,const void* ptr,msize size)
	{
		return owns(&a->linAlloc,ptr,size)&&owns(&a->storeAlloc,ptr,size);
	}
}
