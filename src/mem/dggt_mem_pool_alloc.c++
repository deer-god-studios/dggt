#include "dggt_mem_pool_alloc.h"

namespace dggt
{
	namespace internal_
	{
		void pool_alloc_init(pool_alloc* a)
		{
			if (a)
			{
				msize blockCount=get_capacity((lin_alloc*)a)/a->store.bSize;
				for (msize i=0;i<blockCount;++i)
				{
					store_alloc_free((store_alloc*)a,
							lin_alloc_malloc((lin_alloc*)a,a->store.bSize),
							a->store.bSize);
				}
			}
		}

		void* pool_alloc_malloc(allocator* a,msize size)
		{
			void* result=0;
			pool_alloc* poolAlloc=(pool_alloc*)a;
			if (poolAlloc)
			{
				return store_alloc_malloc(&poolAlloc->store,size);
			}
			return result;
		}

		vpage pool_alloc_malloc_vpage(allocator* a,msize size)
		{
			return vpage(pool_alloc_malloc(a,size),size);
		}

		b32 pool_alloc_free(allocator* a,void* ptr,msize size)
		{
			b32 result=false;
			pool_alloc* poolAlloc=(pool_alloc*)a;
			if (poolAlloc)
			{
				return store_alloc_free(&poolAlloc->store,ptr,size);
			}
			return result;
		}

		b32 pool_alloc_free(allocator* a,vpage& pge)
		{
			return pool_alloc_free(a,pge.ptr,pge.size);
		}

		b32 pool_alloc_clear(allocator* a)
		{
			b32 result=false;
			lin_alloc_clear(a);
			pool_alloc* poolAlloc=(pool_alloc*)a;
			if (poolAlloc)
			{
				store_alloc_clear(&poolAlloc->store);
				pool_alloc_init(poolAlloc);
				result=true;
			}
			return result;

		}

		msize pool_alloc_get_used(const allocator* a)
		{
			return buff_alloc_get_capacity(a)-store_alloc_get_available(a);
		}

		msize pool_alloc_get_available(const allocator* a)
		{
			msize result=0;
			pool_alloc* poolAlloc=(pool_alloc*)a;
			if (poolAlloc)
			{
				result=store_alloc_get_available(&poolAlloc->store);
			}
			return result;
		}

		global alloc_func_table POOL_ALLOC_TABLE=
		{
			pool_alloc_malloc,
			pool_alloc_malloc_vpage,
			pool_alloc_free,
			pool_alloc_free,
			pool_alloc_clear,
			buff_alloc_owns,
			buff_alloc_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			pool_alloc_get_used,
			pool_alloc_get_available,
			buff_alloc_get_capacity,
			buff_alloc_get_buff,
			buff_alloc_get_buff,
			buff_alloc_get_buff_ptr,
			buff_alloc_get_buff_ptr
		};
	}

	pool_alloc::pool_alloc(alloc_func_table* tbl,vpage buff,msize blockSize)
		:lin_alloc(tbl,buff),store(store_alloc(blockSize))
	{ 
		if (buff!=NULL_VPAGE)
		{
			internal_::pool_alloc_init(this);
		}
	}

	pool_alloc::pool_alloc()
		:pool_alloc(&internal_::POOL_ALLOC_TABLE,vpage(),sizeof(pool_block)) { }

	pool_alloc::pool_alloc(vpage buff,msize blockSize)
		:pool_alloc(&internal_::POOL_ALLOC_TABLE,buff,blockSize) { }

	pool_alloc::pool_alloc(void* buff,msize size,msize blockSize)
		:pool_alloc(vpage(buff,size),blockSize) { }
}
