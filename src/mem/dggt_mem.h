#ifndef _DGGT_MEM_H_

#include "dggt_mem_defines.h"
#include "dggt_mem_utils.h"
#include "dggt_mem_blk.h"
#include "dggt_mem_null_alloc.h"
#include "dggt_mem_lin_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_autostack_alloc.h"
#include "dggt_mem_pool_alloc.h"
#include "dggt_mem_free_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_table_alloc.h"
#include "dggt_mem_fallback_alloc.h"
#include "dggt_mem_stallocator.h"

namespace dggt
{
	global const msize DEF_BUFFSIZE=GB(2);
	global const msize DEF_BLOCK_SIZE=8;

	void cache_init(msize size);

	b32 cache_is_initialized();

	void cache_shutdown();

	void cache_reinit(msize cacheSize);

	msize available_cache_mem();
	
	msize used_cache_mem();

	free_alloc* get_cache_alloc();

	void* cache_alloc(msize size=DEF_BLOCK_SIZE);

	template <typename T>
	T* cache_alloc(u32 count=1);

	b32 cache_free(void* ptr,msize size=DEF_BLOCK_SIZE);

	template <typename T>
	b32 cache_free(T* ptr,u32 count=1);
}

#include "dggt_mem.inl"

#define _DGGT_MEM_H_
#endif
