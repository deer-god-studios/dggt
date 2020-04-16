#ifndef _DGGT_MEM_LIN_ALLOC_H_

#include "dggt_mem_allocator.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	struct lin_alloc:allocator<lin_alloc>
	{
		vpage buff;
		msize used;

		lin_alloc(vpage buff)
			:allocator<lin_alloc>(this),used(0) { }
		lin_alloc(void* ptr,msize size) :
			lin_alloc(vpage(ptr,size)) { }
	};

	void* malloc(lin_alloc* a,msize size);

	b32 owns(const lin_alloc* a,void* ptr,msize size);

	b32 clear(lin_alloc* a);

	msize get_used(const lin_alloc* a);

	msize get_available(const lin_alloc* a);

	void* get_buff_ptr(lin_alloc* a);

	const void* get_buff_ptr(const lin_alloc* a);


}

#define _DGGT_MEM_LIN_ALLOC_H_
#endif
