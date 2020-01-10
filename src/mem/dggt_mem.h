#ifndef _DGGT_MEM_H_

// TODO: add set_block functions to allocators.
// TODO: comments and docs!

#include "dggt_mem_alloc.h"
#include "dggt_mem_linear_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_free_list_alloc.h"
#include "dggt_mem_pool_alloc.h"

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

template <alloc_t A>
allocator<A> create_alloc(msize size);
template <alloc_t A>
void free_alloc(allocator<A>& alloc);

allocator<alloc_t::POOL> create_alloc(msize size,msize blockSize);

#include "dggt_mem.inl"
#define _DGGT_MEM_H_
#endif
