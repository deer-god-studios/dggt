#ifndef _DGGT_MEM_FREE_ALLOC_H_

#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	struct free_block
	{
		free_block* next;
		msize size;
	};

	struct free_alloc:
		allocator<free_alloc>
	{
		lin_alloc linAlloc;
		free_block* freeList;

		free_alloc(void* ptr,msize size)
			: allocator<free_alloc>(this),
			linAlloc(lin_alloc(ptr,size)),
			freeList((free_block*)ptr)
		{
			freeList->next=0;
			freeList->size=size;
		}

		free_alloc(vpage buff)
			: free_alloc(buff.ptr,buff.size) { }
		free_alloc() : free_alloc(0,0) { }
	};

	void* malloc(free_alloc* a,msize size);
	
	b32 free(free_alloc* a,void* ptr,msize size);
	
	b32 clear(free_alloc* a);
	
	b32 owns(const free_alloc* a,const void* ptr,msize size);

	msize get_used(const free_alloc* a);
	
	msize get_available(const free_alloc* a);

	msize get_capacity(const free_alloc* a);

	void* get_buff_ptr(free_alloc* a);

	const void* get_buff_ptr(const free_alloc* a);
}

#define _DGGT_MEM_FREE_ALLOC_H_
#endif
