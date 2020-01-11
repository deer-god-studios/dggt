#ifndef _DGGT_MEM_H_

// TODO: add set_block functions to allocators.
// TODO: comments and docs!

#include "dggt_mem_alloc.h"

void dggt_mem_init(msize cacheSize);
void dggt_mem_free();
void dggt_mem_reinit(msize cacheSize);
msize dggt_mem_available();
msize dggt_mem_used();
msize dggt_mem_cache_size();
void dggt_mem_cache_clear();
void dggt_mem_cache_free(blk<void>& block);
b32 dggt_mem_is_initialized();
blk<void> dggt_mem_cache_alloc(msize size);

template <typename T>
blk<T> dggt_mem_cache_alloc(u32 count);
template <typename T>
void dggt_mem_cache_free(blk<T>& block);

allocator dggt_mem_create_alloc(alloc_t type,msize size,msize blockSize=0);
void dggt_mem_free_alloc(allocator& alloc);


#include "dggt_mem.inl"
#define _DGGT_MEM_H_
#endif
