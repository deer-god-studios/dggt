#include "dggt_mem.h"

namespace dggt
{
	namespace internal_
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
			internal_::cacheAlloc_=free_alloc(
					cacheMem,size);
			internal_::cacheAlloc=&internal_::cacheAlloc_;
			internal_::isInitialized=true;
		}
	}

	void cache_shutdown()
	{
		clear(internal_::cacheAlloc);
		free(internal_::cacheAlloc_.buff,
				internal_::cacheAlloc_.buffSize);
		internal_::isInitialized=false;
	}

	b32 cache_is_initialized()
	{
		return internal_::isInitialized;
	}

	void cache_reinit(msize cacheSize)
	{
		cache_shutdown();
		cache_init(cacheSize);
	}

	void* cache_malloc(msize size)
	{
		return cache_is_initialized()?malloc(internal_::cacheAlloc,size):0;
	}

	b32 cache_free(void* ptr,msize size)
	{
		return cache_is_initialized()?free(internal_::cacheAlloc,ptr,size):false;
	}

	msize available_cache_mem()
	{
		return available_mem(internal_::cacheAlloc);
	}

	msize used_cache_mem()
	{
		return used_mem(internal_::cacheAlloc);
	}

	free_alloc* get_cache_alloc()
	{
		return internal_::cacheAlloc;
	}
}
