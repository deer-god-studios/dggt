#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::POOL>
	{
		static const alloc_t TYPE=alloc_t::POOL;

		blk<void> buff;
		msize used;
		msize blockSize;
		u32 blockCount;
		u32 blocksUsed;
		pool_block* pool;

		allocator(void* ptr,msize size,msize blockSize);
		allocator(blk<void> buffer,msize blockSize);
		template <typename T>
		allocator(T* ptr,u32 count);
		template <typename T>
		allocator(blk<T> buffer);

		template <typename T>
		blk<T> alloc();
		blk<void> alloc();

		b32 free(void* ptr);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr);
		template <typename T>
		b32 free(blk<T> block);

		void clear();

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

		allocator();
	};

}
#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
