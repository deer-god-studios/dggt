#ifndef _DGGT_MEM_STORE_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	// NOTE: TABLESIZE must be a power of 2!!
	template <u32 TABLESIZE>
	struct allocator<ALLOC_T_STORE_TABLE,TABLESIZE>
	{
		static const alloc_t TYPE=alloc_t::STORE;
		static const u32 S=TABLESIZE;
		u32 blockCount;
		flag32 flagTable[TABLESIZE];
		allocator<ALLOC_T_STORE> storeTable[TABLESIZE];

		allocator();
	};

	template
}

#include "dggt_mem_store_table_alloc.inl"

#define _DGGT_MEM_STORE_TABLE_ALLOC_H_
#endif
