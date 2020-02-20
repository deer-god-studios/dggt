#ifndef _DGGT_MEM_STORE_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	// NOTE: TABLESIZE must be a power of 2!!
	template <u32 TABLESIZE=DEF_TABLESIZE>
	struct allocator<ALLOC_T_STORE_TABLE,TABLESIZE>
	{
		static const u32 TYPE=ALLOC_T_STORE;
		static const u32 S=TABLESIZE;
		u32 blockCount;
		u32 storeCount;
		msize availableMem;
		flag32 flagTable[TABLESIZE];
		store_alloc<> storeTable[TABLESIZE];

		allocator();
	};

	template <u32 TABLESIZE>
	using store_table_alloc=allocator<ALLOC_T_STORE_TABLE,TABLESIZE>;

	template <u32 TABLESIZE>
	void* alloc(store_table_alloc<TABLESIZE>* a,msize* size=0);

	template <u32 TABLESIZE>
	blkv alloc(store_table_alloc<TABLESIZE>* a,msize size=4);

	template <typename T,u32 TABLESIZE>
	T* alloc(store_table_alloc<TABLESIZE>* a,u32* count=0);

	template <typename T,u32 TABLESIZE>
	blk<T> alloc(store_table_alloc<TABLESIZE>* a,u32 count=1);

	template <u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,void* ptr,msize size);

	template <u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,blkv block);

	template <typename T,u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,T* ptr,u32 count);

	template <typename T,u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,blk<T> block);

	template <u32 TABLESIZE>
	b32 clear(store_table_alloc<TABLESIZE>* a);

	template <u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const void* ptr,msize size);

	template <u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const blkv block);

	template <typename T,u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const T* ptr,u32 count);

	template <typename T,u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const blk<T> block);

	template <u32 TABLESIZE>
	msize available_mem(const store_table_alloc<TABLESIZE>* a);
	
	template <u32 TABLESIZE>
	msize used_mem(const store_table_alloc<TABLESIZE>* a);

	template <u32 TABLESIZE>
	stack_state save_stack(store_table_alloc<TABLESIZE>* a);

	template <u32 TABLESIZE>
	b32 restore_stack(store_table_alloc<TABLESIZE>* a,stack_state state);

	template <u32 TABLESIZE>
	b32 is_stack_balanced(store_table_alloc<TABLESIZE>* a);

	template <u32 TABLESIZE>
	u32 get_block_size(store_table_alloc<TABLESIZE>* a);
}

#include "dggt_mem_store_table_alloc.inl"

#define _DGGT_MEM_STORE_TABLE_ALLOC_H_
#endif
