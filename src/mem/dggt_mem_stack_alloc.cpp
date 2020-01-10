#include "dggt_mem_stack_alloc.h"

allocator<alloc_t::STACK>::allocator()
{
	block=blk<void>();
	used=0;
	savedCount=0;
	zero_struct<stack_state>(&prevSaved);
}

allocator<alloc_t::STACK>::allocator(void* ptr,msize size)
{
	block=blk<void>(ptr,size);
	used=0;
	savedCount=0;
	zero_struct<stack_state>(&prevSaved);
}

allocator<alloc_t::STACK>::allocator(blk<void>& block)
	: allocator(block.mem,block.size) { }

blk<void> allocator<alloc_t::STACK>::alloc(msize size)
{
	blk<void> result;
	if (used+size<=block.size)
	{
		result.mem=ptr_add(block.mem,used);
		result.size=size;
		used+=size;
	}
	return result;
}

void allocator<alloc_t::STACK>::clear()
{
	used=0;
	savedCount=0;
	zero_struct(&prevSaved);
}

b32 allocator<alloc_t::STACK>::owns(const blk<void>& block) const
{
	return block.mem>=this->block.mem&&
		ptr_add(block.mem,block.size)<=ptr_add(this->block.mem,this->block.size);
}

stack_state allocator<alloc_t::STACK>::save_state()
{
	stack_state result;
	result.used=used;
	prevSaved=result;
	++savedCount;
	return result;
}

b32 allocator<alloc_t::STACK>::restore_state(stack_state& state)
{
	b32 result=state.used==prevSaved.used;
	if (result)
	{
		used=state.used;
		--savedCount;
	}
	return result;
}

b32 allocator<alloc_t::STACK>::is_stack_balanced() const
{
	return savedCount==0;
}

msize allocator<alloc_t::STACK>::available() const
{
	return block.size-used;
}
