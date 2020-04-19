#include "dggt_mem_store_alloc.h"

namespace dggt
{
	namespace internal_
	{
		void* store_alloc_malloc(allocator* a,msize size)
		{
			void* result=0;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc&&storeAlloc->bCount&&
					(size==0||size==storeAlloc->bSize))
			{
				result=storeAlloc->store;
				storeAlloc->store=storeAlloc->store->next;
				--storeAlloc->bCount;
			}
			return result;
		}

		vpage store_alloc_malloc_vpage(allocator* a,msize size)
		{
			return vpage(store_alloc_malloc(a,size),size);
		}

		b32 store_alloc_free(allocator* a,void* ptr,msize size)
		{
			b32 result=false;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc&&
					(size==0||size==storeAlloc->bSize))
			{
				store_block* newBlock=(store_block*)ptr;
				newBlock->next=storeAlloc->store;
				storeAlloc->store=newBlock;
				++storeAlloc->bCount;
				result=true;
			}
			return result;
		}

		b32 store_alloc_free(allocator* a,vpage& pge)
		{
			return free(a,pge.ptr,pge.size);
		}

		b32 store_alloc_clear(allocator* a)
		{
			b32 result=false;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc)
			{
				storeAlloc->store=0;
				storeAlloc->bCount=0;
				result=true;
			}
			return result;
		}

		b32 store_alloc_owns(const allocator* a,const void* ptr,msize size)
		{
			b32 result=false;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc)
			{
				result=(size==storeAlloc->bSize);
			}
			return result;
		}

		b32 store_alloc_owns(const allocator* a,const vpage& pge)
		{
			return store_alloc_owns(a,pge.ptr,pge.size);
		}

		msize store_alloc_get_used(const allocator* a)
		{
			msize result=MAX_MSIZE;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc&&get_available(a))
			{
				result=0;
			}
			return result;
		}

		msize store_alloc_get_available(const allocator* a)
		{
			msize result=0;
			store_alloc* storeAlloc=(store_alloc*)a;
			if (storeAlloc)
			{
				result=storeAlloc->bCount*storeAlloc->bSize;
			}
			return result;
		}

		msize store_alloc_get_capacity(const allocator* a)
		{
			return MAX_MSIZE;
		}

		global alloc_func_table STORE_ALLOC_TABLE=
		{
			store_alloc_malloc,
			store_alloc_malloc_vpage,
			store_alloc_free,
			store_alloc_free,
			store_alloc_clear,
			store_alloc_owns,
			store_alloc_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			store_alloc_get_used,
			store_alloc_get_available,
			store_alloc_get_capacity,
			allocator_get_buff,
			allocator_get_buff,
			allocator_get_buff_ptr,
			allocator_get_buff_ptr
		};
	}

	store_alloc::store_alloc(alloc_func_table* tbl,msize blockSize)
		:allocator(tbl),bSize(blockSize),bCount(0),store(0) { }

	store_alloc::store_alloc(msize blockSize)
		: store_alloc(&internal_::STORE_ALLOC_TABLE,blockSize) { }

	store_alloc::store_alloc()
		:store_alloc(sizeof(store_block)) { }
}
