#ifndef _DGGT_MEM_H_

#include "dggt_mem_defines.h"
#include "dggt_mem_alloc.h"
#include "dggt_mem_linear_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_pool_alloc.h"
#include "dggt_mem_free_list_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_store_table_alloc.h"

namespace dggt
{
	void cache_init(msize cacheSize);
	b32 cache_is_initialized();
	void cache_shutdown();
	void cache_reinit(msize cacheSize);
	msize available_cache_mem();
	msize used_cache_mem();
	msize cache_size();
	void* cache_alloc(msize* size);
	blk<void> cache_alloc(msize size);
	b32 cache_free(void* ptr,msize size);
	b32 cache_free(blk<void> block);
	void cache_clear();

	template <typename T>
	T* cache_alloc(u32* count);
	template <typename T>
	blk<T> cache_alloc(u32 count);
	template <typename T>
	b32 cache_free(blk<T> block);
	template <typename T>
	b32 cache_free(T* ptr,u32 count);

	template <alloc_t A>
	allocator<A> create_alloc(msize size);
	template <alloc_t A,u32 SIZE>
	allocator<A,SIZE> create_alloc();

	allocator<alloc_t::POOL> create_alloc(msize size,msize blockSize);
	allocator<alloc_t::STORE> create_alloc(msize blockSize);

	template <alloc_t A>
	b32 destroy_alloc(allocator<A>* alloc);
}


#include "dggt_mem.inl"
#define _DGGT_MEM_H_
#endif
