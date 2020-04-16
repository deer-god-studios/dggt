#ifndef _DGGT_MEM_TABLE_ALLOC_H_

#include "dggt_mem_allocator.h"
#include "dggt_mem_store_alloc.h"

namespace dggt
{
	global constexpr msize DEF_TABLESIZE=4096;
	global const flag32 STORE_TABLE_EMPTY=0;
	global const flag32 STORE_TABLE_OCCUPIED=1;
	global const flag32 STORE_TABLE_DELETED=2;

	template <msize TABLESIZE=DEF_TABLESIZE>
	struct table_alloc:
		allocator<table_alloc<TABLESIZE>>
	{
		flag32 flagTable[TABLESIZE];
		store_alloc storeTable[TABLESIZE];
		msize availableMem;
		u32 storeCount;

		table_alloc():
			allocator<table_alloc<TABLESIZE>>(this)
		{
			for (msize i=0;i<TABLESIZE;++i)
			{
				flagTable[i]=STORE_TABLE_EMPTY;
			}
			availableMem=0;
			storeCount=0;
		}
	};

	template <msize TABLESIZE>
	void* malloc(table_alloc<TABLESIZE>* a,msize size);

	template <msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,void* ptr,msize size);
	
	template <msize TABLESIZE>
	b32 clear(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const void* ptr,msize size);

	template <msize TABLESIZE>
	msize get_used(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize get_available(const table_alloc<TABLESIZE>* a);
}

#include "dggt_mem_table_alloc.inl"

#define _DGGT_MEM_TABLE_ALLOC_H_
#endif
