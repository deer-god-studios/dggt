#ifndef _DGGT_MEM_STORE_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	// NOTE: TABLESIZE must be a power of 2!!
	template <u32 TABLESIZE>
	struct allocator<alloc_t::STORE_TABLE,TABLESIZE>
	{
		static const alloc_t TYPE=alloc_t::STORE;
		static const u32 S=TABLESIZE;
		u32 storeCount;
		flag32 flagTable[TABLESIZE];
		allocator<alloc_t::STORE> storeTable[TABLESIZE];

		allocator();

		void* alloc(msize* size);
		blk<void> alloc(msize size);
		template <typename T>
		T* alloc(u32* count);
		template <typename T>
		blk<T> alloc(u32 count);

		b32 free(void* ptr,msize size);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr,u32 count);
		template <typename T>
		b32 free(blk<T> block);

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;

		msize available_mem() const;
		msize used_mem() const;
		u32 available_blocks() const;
		u32 used_blocks() const;
	};
}

#include "dggt_mem_store_table_alloc.inl"

#define _DGGT_MEM_STORE_TABLE_ALLOC_H_
#endif
