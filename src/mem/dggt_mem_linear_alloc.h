#ifndef _DGGT_MEM_LINEAR_ALLOC_H_

#include "dggt_mem_alloc.h"

template <>
struct allocator<alloc_t::LINEAR>
{
	static const alloc_t TYPE=alloc_t::LINEAR;
	blk<void> block;
	msize used;

	allocator();
	explicit allocator(blk<void>& block);
	allocator(void* ptr,msize size);

	blk<void> alloc(msize size);
	void clear();

	template <typename T>
	blk<T> alloc(u32 count);

	b32 owns(const blk<void>& block) const;

	template <typename T>
	b32 owns(const blk<T>& block) const;

	msize available() const;
};

#include "dggt_mem_linear_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOC_H_
#endif
