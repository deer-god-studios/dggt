#include "dggt_mem.h"

namespace dggt
{
	namespace dggt_internal_
	{
		static b32 isInitialized=0;
		static blk<void> cacheBlock=blk<void>();
		static allocator<alloc_t::FREE_LIST> cache=
			allocator<alloc_t::FREE_LIST>(0,0);
	}

	void cache_init(msize cacheSize)
	{
		dggt_internal_::cacheBlock=blk_alloc(cacheSize);
		dggt_internal_::cache=
			allocator<alloc_t::FREE_LIST>(dggt_internal_::cacheBlock);
		dggt_internal_::isInitialized=1;
	}

	b32 cache_is_initialized()
	{
		return dggt_internal_::isInitialized;
	}

	void cache_shutdown()
	{
		if (dggt_internal_::isInitialized)
		{
			blk_free(dggt_internal_::cacheBlock);
			dggt_internal_::cache.buff=blk<void>();
			dggt_internal_::isInitialized=0;
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
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cache.available_mem();
		}
		return result;
	}

	msize used_cache_mem()
	{
		msize result=0;
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cache.used;
		}
		return result;
	}

	msize cache_size()
	{
		msize result=0;
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cacheBlock.size;
		}
		return result;
	}

	void cache_clear()
	{
		if (dggt_internal_::isInitialized)
		{
			dggt_internal_::cache.clear();
		}
	}

	void* cache_alloc(msize* size)
	{
		return dggt_internal_::cache.alloc(size);
	}

	blk<void> cache_alloc(msize size)
	{
		blk<void> result;
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cache.alloc(size);
		}
		return result;
	}

	b32 cache_free(void* ptr,msize size)
	{
		b32 result=0;
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cache.free(ptr,size);
		}
		return result;
	}

	b32 cache_free(blk<void> block)
	{
		b32 result=0;
		if (dggt_internal_::isInitialized)
		{
			result=dggt_internal_::cache.free(block);
		}
		return result;
	}

	allocator<alloc_t::POOL>* create_alloc(msize size,msize blockSize)
	{
		u32 allocCount=1;
		allocator<alloc_t::POOL>* result=
			cache_alloc<allocator<alloc_t::POOL>>(&allocCount);
		if (result)
		{
			void* buffPtr=cache_alloc(&size);
			if (buffPtr)
			{
				*result=allocator<alloc_t::POOL>(buffPtr,size,blockSize);
			}
		}
		return result;
	}
}
