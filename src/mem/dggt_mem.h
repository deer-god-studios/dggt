#ifndef _DGGT_MEM_H_

// TODO: add set_block functions to allocators.
// TODO: comments and docs!

#include "dggt_mem_free_list.h"
#include "dggt_mem_alloc.h"

namespace dggt
{
	void cache_init(msize cacheSize);
	b32 cache_is_initialized();
	void cache_shutdown();
	void cache_reinit(msize cacheSize);
	msize available_cache_mem();
	msize used_cache_mem();
	msize cache_size();
	void cache_clear();
	void cache_free(blk<void>& block);
	blk<void> cache_alloc(msize size);

	template <typename T>
	blk<T> cache_alloc(u32 count);
	template <typename T>
	void cache_free(blk<T>& block);

	allocator create_alloc(alloc_t type,msize size,msize blockSize=0);
	void destroy_alloc(allocator& alloc);
}


#include "dggt_mem.inl"
#define _DGGT_MEM_H_
#endif
