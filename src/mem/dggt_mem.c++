#include "dggt_mem.h"

namespace dggt
{
	namespace dggt_internal_
	{
		global free_alloc cacheAlloc_=free_alloc(); // global cache.  allocated off the heap at startup, available on request.
		global free_alloc* cacheAlloc=&cacheAlloc_;
		global b32 isInitialized=false;
	}

	void cache_init(msize size)
	{
		void* cacheMem=alloc(size);
		if (cacheMem)
		{
			dggt_internal_::cacheAlloc_=free_alloc(
					cacheMem,size);
			dggt_internal_::cacheAlloc=&dggt_internal_::cacheAlloc_;
			dggt_internal_::isInitialized=true;

		}
	}

	void cache_shutdown()
	{
		clear(dggt_internal_::cacheAlloc);
		free(dggt_internal_::cacheAlloc_.buff,
				dggt_internal_::cacheAlloc_.buffSize);
		dggt_internal_::isInitialized=false;
	}

	b32 cache_is_initialized()
	{
		return dggt_internal_::isInitialized;
	}

	void cache_reinit(msize cacheSize)
	{
		cache_shutdown();
		cache_init(cacheSize);
	}

	void* cache_alloc(msize size)
	{
		return cache_is_initialized()?alloc(dggt_internal_::cacheAlloc,size):0;
	}

	b32 cache_free(void* ptr,msize size)
	{
		return cache_is_initialized()?free(dggt_internal_::cacheAlloc,ptr,size):false;
	}

	msize available_cache_mem()
	{
		return available_mem(dggt_internal_::cacheAlloc);
	}

	msize used_cache_mem()
	{
		return used_mem(dggt_internal_::cacheAlloc);
	}

	free_alloc* get_cache_alloc()
	{
		return dggt_internal_::cacheAlloc;
	}
}
