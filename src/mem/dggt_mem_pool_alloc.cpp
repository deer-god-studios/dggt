#include "dggt_mem_pool_alloc.h"

namespace dggt
{
	struct pool_block
	{
		pool_block* next;
	};

	allocator<alloc_t::POOL>::allocator()
	{
		buff=blk<void>();
		used=0;
		blockSize=0;
		pool=0;
		blockCount=0;
		blocksUsed=0;
	}

	allocator<alloc_t::POOL>::allocator(void* ptr,
			msize size,msize blockSize)
		: allocator()
	{
		if (blockSize<sizeof(pool_block))
		{
			blockSize=sizeof(pool_block);
		}
		buff.mem=ptr;
		this->blockSize=blockSize;
		blockCount=(u32)(size/blockSize);
		pool=(pool_block*)ptr;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block* current=pool+i;
			current->next=
				i==blockCount-1?0:current+1;
		}
	}

	allocator<alloc_t::POOL>::allocator(blk<void> buffer,msize blockSize)
		: allocator(buffer.mem,buffer.size,blockSize) { }

	blk<void> allocator<alloc_t::POOL>::alloc()
	{
		blk<void> result;
		if (pool)
		{
			result=blk<void>(pool,blockSize);
			pool=pool->next;
			used+=blockSize;
			++blocksUsed;
		}
		return result;
	}

	b32 allocator<alloc_t::POOL>::free(void* ptr)
	{
		b32 result=0;
		if (owns(ptr))
		{
			pool_block* newBlock=(pool_block*)ptr;
			newBlock->next=pool;
			pool=newBlock;
			used-=blockSize;
			--blocksUsed;
			result=1;
		}
		return result;
	}

	b32 allocator<alloc_t::POOL>::free(blk<void> block)
	{
		b32 result=0;
		if (owns(block))
		{
			result=free(block.mem);
		}
		return result;
	}

	void allocator<alloc_t::POOL>::clear()
	{
		pool=(pool_block*)buff.mem;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block* current=pool+i;
			pool->next=i==blockCount-1?0:current+1;

		}
		used=0;
		blocksUsed=0;
	}

	b32 allocator<alloc_t::POOL>::owns(const void* ptr) const
	{
		return ptr>=buff.mem&&ptr<=ptr_add(buff.mem,buff.size);
	}

	b32 allocator<alloc_t::POOL>::owns(const blk<void> block) const
	{
		return owns(block.mem)&&
			ptr_add(block.mem,block.size)<=
			ptr_add(buff.mem,buff.size);
	}

	msize allocator<alloc_t::POOL>::available_mem() const
	{
		return buff.size-used;
	}

	msize allocator<alloc_t::POOL>::used_mem() const
	{
		return used;
	}

	u32 allocator<alloc_t::POOL>::available_blocks() const
	{
		return blockCount-blocksUsed;
	}

	u32 allocator<alloc_t::POOL>::used_blocks() const
	{
		return blocksUsed;
	}
}
