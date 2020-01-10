#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

struct pool_block;

template <>
struct allocator<alloc_t::POOL>
{
	static const alloc_t TYPE=alloc_t::POOL;
	blk<void> block;
	pool_block* pool;
	msize blockSize;
	msize itemCount;
	msize used;

	allocator();
	explicit allocator(msize blockSize);
	allocator(blk<void>& block,msize blockSize);
	allocator(void* ptr,msize size,msize blockSize);

	blk<void> alloc();
	void free(blk<void>& block);
	void clear();
	msize available() const;
	b32 owns(const blk<void>& block) const;

	template <typename T>
	blk<T> alloc();
	template <typename T>
	void free(blk<T>& block);

	template <typename T>
	b32 owns(const blk<T>& block) const;
};

#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
