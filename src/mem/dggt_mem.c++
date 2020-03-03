#include "dggt_mem.h"

namespace dggt
{
	namespace dggt_internal_
	{
		global free_alloc cacheAlloc_=free_alloc();
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

	allocator<>* create_alloc(alloc_t type,void* buff,msize size,
			msize blockSize)
	{
		allocator<>* result=0;
		switch (type)
		{
			case ALLOC_T_NULL:
				{
					null_alloc* a=
						cache_alloc<null_alloc>();
					*a=null_alloc();
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_LIN:
				{
					lin_alloc* a=
						cache_alloc<lin_alloc>();
					*a=lin_alloc(buff,size);
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_STACK:
				{
					stack_alloc* a=
						cache_alloc<stack_alloc>();
					*a=stack_alloc(buff,size);
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_POOL:
				{
					pool_alloc<>* a=
						cache_alloc<pool_alloc<>>();
					*a=pool_alloc<>(buff,size,blockSize);
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_FREE:
				{
					free_alloc* a=
						cache_alloc<free_alloc>();
					*a=free_alloc(buff,size);
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_STORE:
				{
					store_alloc<>* a=
						cache_alloc<store_alloc<>>();
					*a=store_alloc<>(blockSize);
					result=(allocator<>*)a;
				} break;
			case ALLOC_T_TABLE:
				{
					table_alloc<>* a=
						cache_alloc<table_alloc<>>();
					*a=table_alloc<>();
					result=(allocator<>*)a;
				} break;
		}
		return result;
	}

	allocator<>* create_alloc(alloc_t type,msize size,
			msize blockSize)
	{
		allocator<>* result=0;
		if (size)
		{
			void* buff=cache_alloc(size);
			result=create_alloc(type,buff,size,blockSize);
		}
		return result;
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
