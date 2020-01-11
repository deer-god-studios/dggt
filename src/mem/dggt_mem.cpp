#include "dggt_mem.h"

namespace dggt_internal_
{
	using namespace dggt;
	static b32 isInitialized=0;
	static blk<void> cacheBlock=blk<void>();
	static allocator cache=allocator();
}

namespace dggt
{
	using namespace dggt_internal_;
	void cache_init(msize cacheSize)
	{
		cacheBlock=blk_alloc(cacheSize);
		cache=allocator(alloc_t::FREE_LIST,cacheBlock);
		isInitialized=1;
	}

	b32 cache_is_initialized()
	{
		return isInitialized;
	}

	void cache_shutdown()
	{
		if (isInitialized)
		{
			blk_free(cacheBlock);
			cache.buffer=blk<void>();
			isInitialized=0;
		}
	}

	void cache_reinit(msize cacheSize)
	{
		cache_shutdown();
		cache_init(cacheSize);
	}

	msize available_cache_mem()
	{
		msize result=0;
		if (isInitialized)
		{
			result=cache.available_mem();
		}
		return result;
	}

	msize used_cache_mem()
	{
		msize result=0;
		if (isInitialized)
		{
			result=cache.used;
		}
		return result;
	}

	msize cache_size()
	{
		msize result=0;
		if (isInitialized)
		{
			result=cacheBlock.size;
		}
		return result;
	}

	void cache_clear()
	{
		if (isInitialized)
		{
			cache.clear();
		}
	}

	void cache_free(blk<void>& block)
	{
		if (isInitialized)
		{
			cache.free(block);
		}
	}

	blk<void> cache_alloc(msize size)
	{
		blk<void> result;
		if (isInitialized)
		{
			result=cache.alloc(size);
		}
		return result;
	}

	allocator create_alloc(alloc_t type,msize size,msize blockSize)
	{
		blk<void> block=blk_alloc(size);
		return allocator(type,block,blockSize);
	}

	void destroy_alloc(allocator& alloc)
	{
		blk_free(alloc.buffer);
	}
}
