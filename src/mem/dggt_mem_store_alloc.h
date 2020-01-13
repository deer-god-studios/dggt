#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::STORE>
	{
		static const alloc_t TYPE=alloc_t::STORE;
		msize blockSize;
		store_block* head;
		u32 blockCount;

		allocator(msize blockSize);
		template <typename T>
		allocator();
		blk<void> alloc();
		template <typename T>
		blk<T> alloc();

		b32 free(void* ptr);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr);
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

		private:
		allocator();
	};
}
#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
