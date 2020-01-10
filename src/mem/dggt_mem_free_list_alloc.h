#ifndef _DGGT_MEM_FREE_LIST_ALLOC_H_

#include "dggt_mem_alloc.h"

struct free_block;
template <>
struct allocator<alloc_t::FREE_LIST>
{
	static const alloc_t TYPE=alloc_t::FREE_LIST;
	blk<void> block;
	free_block* freeList;
	msize used;

	allocator();
	explicit allocator(blk<void>& block);
	allocator(void* ptr,msize size);

	blk<void> alloc(msize size);
	void free(blk<void>& block);
	void clear();

	msize available() const;
	b32 owns(const blk<void>& block) const;

	template <typename T>
	blk<T> alloc(u32 count);
	template <typename T>
	void free(blk<T>& block);

	template <typename T>
	b32 owns(const blk<T>& block) const;
};

#include "dggt_mem_free_list_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
