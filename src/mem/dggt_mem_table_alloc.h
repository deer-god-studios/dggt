#ifndef _DGGT_MEM_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	template <msize TABLESIZE>
	struct table_alloc
	{
		allocator<TABLESIZE> baseAlloc;
		flag32 flagTable[TABLESIZE];
		store_alloc<> storeTable[TABLESIZE];
		msize availableMem;
		u32 storeCount;

		table_alloc();
	};

	template <msize TABLESIZE>
	void* alloc(table_alloc<TABLESIZE>* a,msize size);

	template <msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,void* ptr,msize size);
	
	template <msize TABLESIZE>
	b32 clear(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const void* ptr,msize size);

	template <msize TABLESIZE>
	stack_state save_stack(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	b32 restore_stack(table_alloc<TABLESIZE>* a,stack_state state);

	template <msize TABLESIZE>
	b32 is_stack_balanced(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize used_mem(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize available_mem(const table_alloc<TABLESIZE>* a);

	template <typename T,msize TABLESIZE>
	T* alloc(table_alloc<TABLESIZE>* a,u32 count);

	template <typename T,msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,T* ptr,u32 count);

	template <typename T,msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const T* ptr,u32 count);
}

#include "dggt_mem_table_alloc.inl"

#define _DGGT_MEM_TABLE_ALLOC_H_
#endif
