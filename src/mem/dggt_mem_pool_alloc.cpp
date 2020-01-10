#include "dggt_mem_pool_alloc.h"

struct pool_block
{
	pool_block* next;
};

allocator<alloc_t::POOL>::allocator()
{
	block=blk<void>();
	pool=0;
	blockSize=0;
	used=0;
	itemCount=0;
}

allocator<alloc_t::POOL>::allocator(msize blockSize)
{
	if (blockSize<sizeof(pool_block))
	{
		this->blockSize=sizeof(pool_block);
	}
	block=blk<void>();
	pool=0;
	this->blockSize=blockSize;
	used=0;
	itemCount=0;
}

allocator<alloc_t::POOL>::allocator(blk<void>& block,msize blockSize)
{
	if (blockSize<sizeof(pool_block))
	{
		this->blockSize=sizeof(pool_block);
	}
	this->block=block;
	this->blockSize=blockSize;
	itemCount=(u32)(block.size/blockSize);
	pool=(pool_block*)block.mem;
	for (u32 i=0;i<itemCount;++i)
	{
		pool_block* current=pool+i;
		current->next=i==itemCount-1?0:current+1;
		
	}
	this->used=0;
}

blk<void> allocator<alloc_t::POOL>::alloc()
{
	blk<void> result;
	if (pool)
	{
		result=blk<void>(pool,blockSize);
		pool=pool->next;
		used+=blockSize;
	}
	return result;
}

void allocator<alloc_t::POOL>::free(blk<void>& block)
{
	if (owns(block))
	{
		pool_block* newBlock=(pool_block*)block.mem;
		newBlock->next=pool;
		pool=newBlock;
		used-=blockSize;
	}
}

void allocator<alloc_t::POOL>::clear()
{
	pool=(pool_block*)block.mem;
	for (u32 i=0;i<itemCount;++i)
	{
		pool_block* current=pool+i;
		current->next=i==itemCount-1?0:current+1;
		
	}
	this->used=0;
}

msize allocator<alloc_t::POOL>::available() const
{
	return block.size-used;
}

b32 allocator<alloc_t::POOL>::owns(const blk<void>& block) const
{
	return block.size==blockSize&&
		block.mem>=this->block.mem&&
		end_addr(block.mem,block.size)<=
		end_addr(this->block.mem,this->block.size);
}
//allocator<alloc_t::POOL>::
//allocator<alloc_t::POOL>::
