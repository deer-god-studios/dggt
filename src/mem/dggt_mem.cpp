#include "dggt_mem.h"

namespace
{
	static b32 isInitialized=0;
	static blk<void> cacheBlock=blk<void>();
	static allocator cache=allocator();
}

void dggt_mem_init(msize cacheSize)
{
	::cacheBlock=blk_alloc(cacheSize);
	::cache=allocator(alloc_t::FREE_LIST,cacheBlock);
	::isInitialized=1;
}

msize dggt_mem_available()
{
	msize result=0;
	if (::isInitialized)
	{
		result=::cache.available_mem();
	}
	return result;
}

msize dggt_mem_used()
{
	msize result=0;
	if (::isInitialized)
	{
		result=::cache.used;
	}
	return result;
}

msize dggt_mem_cache_size()
{
	msize result=0;
	if (::isInitialized)
	{
		result=::cacheBlock.size;
	}
	return result;
}

void dggt_mem_cache_clear()
{
	if (::isInitialized)
	{
		::cache.clear();
	}
}

void dggt_mem_cache_free(blk<void>& block)
{
	if (::isInitialized)
	{
		::cache.free(block);
	}
}

void dggt_mem_free()
{
	if (::isInitialized)
	{
		blk_free(::cacheBlock);
		::cache.buffer=blk<void>();
		::isInitialized=0;
	}
}

void dggt_mem_reinit(msize cacheSize)
{
	dggt_mem_free();
	dggt_mem_init(cacheSize);
}

blk<void> dggt_mem_cache_alloc(msize size)
{
	blk<void> result;
	if (::isInitialized)
	{
		result=::cache.alloc(size);
	}
	return result;
}

b32 dggt_mem_is_initialized()
{
	return ::isInitialized;
}

allocator dggt_mem_create_alloc(alloc_t type,msize size,msize blockSize)
{
	blk<void> block=blk_alloc(size);
	return allocator(type,block,blockSize);
}

void dggt_mem_destroy_alloc(allocator& alloc)
{
	blk_free(alloc.buffer);
}
