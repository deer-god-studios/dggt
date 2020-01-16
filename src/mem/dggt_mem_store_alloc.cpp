#include "dggt_mem_store_alloc.h"
#include "math/dggt_math_utils.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	struct store_block
	{
		store_block* next;
	};

	allocator<alloc_t::STORE>::allocator()
	{
		blockSize=0;
		head=0;
		blockCount=0;
	}

	allocator<alloc_t::STORE>::allocator(msize blockSize)
		: allocator()
	{
		this->blockSize=max<msize>(blockSize,sizeof(store_block));
	}

	blk<void> allocator<alloc_t::STORE>::alloc()
	{
		blk<void> result=NULL_BLK<void>;
		if (head)
		{
			result=blk<void>(head,blockSize);
			head=head->next;
			--blockCount;
		}
		return result;
	}

	b32 allocator<alloc_t::STORE>::free(blk<void> block)
	{
		b32 result=0;
		if (owns(block))
		{
			store_block* newBlock=(store_block*)block.mem;
			newBlock->next=head;
			head=newBlock;
			++blockCount;
		}
		return result;
	}

	b32 allocator<alloc_t::STORE>::free(void* ptr,msize size)
	{
		b32 result=1;
		if (size)
		{
			u32 blockCount=size/blockSize;
			for (u32 i=0;i<blockCount;++i)
			{
				result=result&&free(blk<void>(ptr,blockSize));
			}
		}
		else
		{
			result=free(blk<void>(ptr,blockSize));
		}
		return result;
	}

	b32 allocator<alloc_t::STORE>::owns(const void* ptr) const
	{
		return 1;
	}
	b32 allocator<alloc_t::STORE>::owns(const blk<void> block) const
	{
		return owns(block)&&
			block.size==blockSize;
	}

	msize allocator<alloc_t::STORE>::available_mem() const
	{
		return blockCount*blockSize;
	}

	msize allocator<alloc_t::STORE>::used_mem() const
	{
		if (blockCount)
		{
			return 0;
		}
		else
		{
			return MAX_MSIZE;
		}
	}

	u32 allocator<alloc_t::STORE>::available_blocks() const
	{
		return blockCount;
	}

	u32 allocator<alloc_t::STORE>::used_blocks() const
	{
		if (blockCount)
		{
			return 0;
		}
		else
		{
			return MAX_UINT32;
		}
	}
}
