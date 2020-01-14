#include "dggt_mem_linear_store_alloc.h"

namespace dggt
{

	allocator<alloc_t::LINEAR_STORE>::allocator()
	{
		store=0;
		linear=0;
	}

	allocator<alloc_t::LINEAR_STORE>::allocator(
			allocator<alloc_t::LINEAR>* linear,
			allocator<alloc_t::STORE>* store)
		: allocator()
	{
		this->store=store;
		this->linear=linear;
	}

	blk<void> allocator<alloc_t::LINEAR_STORE>::alloc(msize size)
	{
		blk<void> result=NULL_BLK<void>;

		if (store&&store->available_mem()&&
				size==store->blockSize)
		{
			result=store->alloc();
		}
		if (result==NULL_BLK<void>&&linear)
		{
			result=linear->alloc(size);
		}
		return result;
	}
	
	void* allocator<alloc_t::LINEAR_STORE>::alloc(msize* size)
	{
		void* result=0;
		msize s=size?*size:4;
		blk<void> b=alloc(s);
		result=b.mem;
		if (size)
		{
			*size=s;
		}
		return result;
	}

	b32 allocator<alloc_t::LINEAR_STORE>::free(void* ptr,msize size)
	{
		return free(blk<void>(ptr,size));
	}

	b32 allocator<alloc_t::LINEAR_STORE>::free(blk<void> block)
	{
		b32 result=0;
		if (store&&store->owns(block))
		{
			result=store->free(block);
		}
		return result;
	}

	void allocator<alloc_t::LINEAR_STORE>::clear()
	{
		if (linear)
		{
			linear->clear();
			if (store)
			{
				store->head=0;
				store->blockCount=0;
			}
		}
	}

	msize allocator<alloc_t::LINEAR_STORE>::available_mem() const
	{
		msize result=0;
		if (store)
		{
			result+=store->available_mem();
		}
		if (linear)
		{
			result+=linear->available_mem();
		}
		return result;
	}

	msize allocator<alloc_t::LINEAR_STORE>::used_mem() const
	{
		msize result=0;
		if (store)
		{
			result+=store->used_mem();
		}
		if (linear)
		{
			result+=linear->used_mem();
		}
		return result;
	}
	
	b32 allocator<alloc_t::LINEAR_STORE>::owns(const blk<void> block) const
	{
		b32 result=1;
		if (store)
		{
			result=result&&store->owns(block);
		}
		if (linear)
		{
			result=result&&linear->owns(block);
		}
		return result;
	}

	b32 allocator<alloc_t::LINEAR_STORE>::owns(const void* ptr) const
	{
		b32 result=1;
		if (store)
		{
			result=result&&store->owns(ptr);
		}
		if (linear)
		{
			result=result&&linear->owns(ptr);
		}
		return result;
	}

	//allocator<alloc_t::LINEAR_STORE>::
	//allocator<alloc_t::LINEAR_STORE>::
	//allocator<alloc_t::LINEAR_STORE>::
}
