#include "dggt_mem_linear_alloc.h"

allocator<alloc_t::LINEAR>::allocator()
{
	block=blk<void>();
	used=0;
}

allocator<alloc_t::LINEAR>::allocator(blk<void>& block)
{
	this->block=block;
	used=0;
}

allocator<alloc_t::LINEAR>::allocator(void* ptr,msize size)
{
	block=blk<void>(ptr,size);
	used=0;
}

blk<void> allocator<alloc_t::LINEAR>::alloc(msize size)
{
	blk<void> result;
	if (used+size<=block.size)
	{
		result=blk<void>(ptr_add(block.mem,used),size);
		used+=size;
	}
	return result;
}

void allocator<alloc_t::LINEAR>::clear()
{
	used=0;
}

b32 allocator<alloc_t::LINEAR>::owns(const blk<void>& block) const
{
	return block.mem>=this->block.mem&&
		ptr_add(block.mem,block.size)<=ptr_add(this->block.mem,this->block.size);
}

msize allocator<alloc_t::LINEAR>::available() const
{
	return block.size-used;
}
