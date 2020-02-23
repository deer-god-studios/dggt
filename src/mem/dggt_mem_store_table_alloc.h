#ifndef _DGGT_MEM_STORE_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	struct store_table
	{
		allocator baseAlloc;
		u32 blockCount;
		u32 storeCount;
		msize availableMem;
		flag32* flagTable;
		store_alloc* storeTable;

		allocator(msize tableSize=DEF_TABLESIZE);
	};

	void* alloc(store_table_alloc* a,msize size=4);

	template <typename T>
	T* alloc(store_table_alloc* a,u32 count=1);

	b32 free(store_table_alloc* a,void* ptr,msize size=4);

	template <typename T>
	b32 free(store_table_alloc* a,T* ptr,u32 count=1);

	b32 clear(store_table_alloc* a);

	b32 owns(const store_table_alloc* a,const void* ptr,msize size=4);

	template <typename T>
	b32 owns(const store_table_alloc* a,const T* ptr,u32 count=1);

	msize available_mem(const store_table_alloc* a);
	
	msize used_mem(const store_table_alloc* a);

	stack_state save_stack(store_table_alloc* a);

	b32 restore_stack(store_table_alloc* a,stack_state state);

	b32 is_stack_balanced(store_table_alloc* a);
}

#include "dggt_mem_store_table_alloc.inl"

#define _DGGT_MEM_STORE_TABLE_ALLOC_H_
#endif
