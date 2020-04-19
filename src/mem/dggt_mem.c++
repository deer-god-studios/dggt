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
		void* cacheMem=malloc(size);
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
		free(internal_::cacheAlloc_.buff.ptr,
				internal_::cacheAlloc_.buff.size);
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

	msize get_available_cache()
	{
		return get_available(internal_::cacheAlloc);
	}

	msize get_used_cache()
	{
		return get_used(internal_::cacheAlloc);
	}

	free_alloc* get_cache_alloc()
	{
		return internal_::cacheAlloc;
	}
}
