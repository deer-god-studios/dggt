#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{

	template <u32 BLOCKSIZE=NO_BLOCKSIZE>
	struct allocator<ALLOC_T_STORE,BLOCKSIZE>
	: member_val_or<BLOCKSIZE>
	{
		static const alloc_t TYPE=ALLOC_T_STORE;
		store_block* head;

		allocator();
		allocator(msize blockSize);
	};
}
#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
