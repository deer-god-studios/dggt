#include "dggt_mem_stack_store_alloc.h"

namespace dggt
{
	allocator<alloc_t::STACK_STORE>::allocator()
	{
		stk=0;
		store=0;
	}

	allocator<alloc_t::STACK_STORE>::allocator(
			allocator<alloc_t::STACK>* stk,
			allocator<alloc_t::STORE>* store)
		: allocator()
	{
		this->stk=stk;
		this->store=store;
	}

	blk<void> allocator<alloc_t::STACK_STORE>::alloc(msize size)
	{
		blk<void> result=NULL_BLK<void>;
		if (store&&store->available_mem()&&
				store->blockSize==size)
		{
			result=store->alloc();
		}
		if (result==NULL_BLK<void>&&stk&&
				stk->available_mem()>=size)
		{
			result=stk->alloc(size);
		}
		return result;
	}

	void* allocator<alloc_t::STACK_STORE>::alloc(msize* size)
	{
		void* result=0;
		msize s=size?*size:4;
		if (store&&store->available_mem()&&
				store->blockSize==s)
		{
			result=store->alloc();
		}
		if (result==NULL_BLK<void>&&stk&&
				stk->available_mem()>=size)
		{
			result=store->alloc(&s);
			if (size)
			{
				*size=s;
			}
		}
		return result;

	}
	
	b32 allocator<alloc_t::STACK_STORE>::free(void* ptr,msize size)
	{
		b32 result=0;
		if (store&&store->blockSize==size)
		{
			result=store->free(ptr);
		}
		if (!result&&stk)
		{
			result=stk->free(ptr,size);
		}
		return result;
	}

	stack_state allocator<alloc_t::STACK_STORE>::save_stack()
	{
		stack_state result=0;
		if (stk)
		{
			result=stk->save_stack();
		}
		return result;
	}
	
	b32 allocator<alloc_t::STACK_STORE>::restore_stack(stack_state state)
	{
		b32 result=0;
		if (stk)
		{
			result=stk->restore_stack(state);
		}
		return result;
	}
	
	b32 allocator<alloc_t::STACK_STORE>::is_stack_balanced() const
	{
		b32 result=0;
		if (stk)
		{
			result=stk->is_stack_balanced();
		}
		return result;
	}

	void allocator<alloc_t::STACK_STORE>::clear()
	{
		if (stk)
		{
			stk->clear();
		}
		if (store)
		{
			store->head=0;
			store->blockCount=0;
		}
	}
	msize allocator<alloc_t::STACK_STORE>::available_mem() const
	{
		msize result=0;
		if (store)
		{
			result+=store->available_mem();
		}
		if (stk)
		{
			result+=stk->available_mem();
		}
		return result;
	}

	msize allocator<alloc_t::STACK_STORE>::used_mem() const
	{
		msize result=0;
		if (store)
		{
			result+=store->used_mem();
		}
		if (stk)
		{
			result+=stk->used_mem();
		}
		return result;
	}
	
	b32 allocator<alloc_t::STACK_STORE>::owns(const blk<void> block) const
	{
		b32 result=1;
		if (store)
		{
			result=result&&store->owns(block);
		}
		if (stk)
		{
			result=result&&stk->owns(block);
		}
		return result;
	}

	b32 allocator<alloc_t::STACK_STORE>::owns(void* ptr) const
	{
		b32 result=1;
		if (store)
		{
			result=result&&store->owns(ptr);
		}
		if (stk)
		{
			result=result&&stk->owns(ptr);
		}
		return result;
	}


	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
	//allocator<alloc_t::STACK_STORE>::
}
