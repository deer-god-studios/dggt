#ifndef _DGGT_MEM_H_

#include "dggt_mem_utils.h"
#include "dggt_mem_null_alloc.h"
#include "dggt_mem_lin_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_pool_alloc.h"
#include "dggt_mem_free_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_table_alloc.h"
#include "dggt_mem_fallback_alloc.h"

#include "dggt_mem_allocator.inl"

namespace dggt
{
	void cache_init(msize size);

	b32 cache_is_initialized();

	void cache_shutdown();

	void cache_reinit(msize cacheSize);

	msize available_cache_mem();
	
	msize used_cache_mem();

	void* cache_alloc(msize size);

	template <typename T>
	T* cache_alloc(u32 count=1);

	b32 cache_free(void* ptr,msize size);

	template <typename T>
	b32 cache_free(T* ptr,u32 count=1);

	template <msize... SizeArgs>
	allocator<SizeArgs...>* create_alloc(alloc_t type,msize size);

	template <msize PrimaryArg,msize FallbackArg>
	allocator<PrimaryArg,FallbackArg>* create_alloc(alloc_t type,
			allocator<PrimaryArg>* primary,
			allocator<FallbackArg>* fallback); 

	template <msize PrimaryArg,msize FallbackArg>
	allocator<PrimaryArg,FallbackArg>* create_alloc(alloc_t type,
			alloc_t primaryType,msize primarySize,
			alloc_t fallbackType,msize fallbackSize);

	template <msize... SizeArgs>
	allocator<SizeArgs...>* create_alloc(alloc_t type,
			void* buff,msize size);

	template <msize... SizeArgs>
	b32 destroy_alloc(allocator<SizeArgs...>* a);
}

#include "dggt_mem.inl"

#define _DGGT_MEM_H_
#endif
