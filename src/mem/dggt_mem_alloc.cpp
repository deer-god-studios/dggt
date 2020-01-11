#include "mem/dggt_mem_alloc.h"

struct pool_block
{
	pool_block* next;
};
struct free_block
{
	msize size;
	free_block* next;
};

namespace
{
	blk<void> alloc_ptr_add(allocator* alloc,msize size)
	{
		blk<void> result;
		if (alloc->used+size<=alloc->buffer.size)
		{
			void* ptr=ptr_add(alloc->buffer.mem,alloc->used);
			result=blk<void>(ptr,size);
			alloc->used+=size;
		}
		return result;
	}

	b32 free_ptr_sub(allocator* alloc,blk<void>& block)
	{
		b32 result=0;
		void* allocEndAddr=ptr_add(
				alloc->buffer.mem,
				alloc->used);
		void* blkEndAddr=ptr_add(block.mem,block.size);
		if (allocEndAddr==blkEndAddr)
		{
			alloc->used-=block.size;
			result=1;
		}
		return result;
	}

	void clear_ptr_offset(allocator* alloc)
	{
		alloc->used=0;
	}

	blk<void> alloc_linear(allocator* alloc,msize size)
	{
		return alloc_ptr_add(alloc,size);
	}

	void clear_linear(allocator* alloc)
	{
		clear_ptr_offset(alloc);
	}

	blk<void> alloc_stack(allocator* alloc,msize size)
	{
		return alloc_ptr_add(alloc,size);
	}

	b32 free_stack(allocator* alloc,blk<void>& block)
	{
		return free_ptr_sub(alloc,block);
	}
	stack_state save_stack(allocator* alloc)
	{
		stack_state result=alloc->used;
		alloc->prevState=result;
		++alloc->stateCount;
		return result;
	}
	b32 restore_stack(allocator* alloc,stack_state state)
	{
		b32 result=state==alloc->prevState;
		if (result)
		{
			alloc->used=state;
			--alloc->stateCount;
		}
		return result;
	}
	b32 is_stack_balanced(const allocator* alloc)
	{
		return alloc->stateCount==0;
	}
	void clear_stack(allocator* alloc)
	{
		clear_ptr_offset(alloc);
	}

	void init_pool(allocator* alloc,
			blk<void>& block,msize blockSize)
	{
		if (blockSize<sizeof(pool_block))
		{
			blockSize=sizeof(pool_block);
		}
		alloc->buffer=block;
		alloc->blockSize=blockSize;
		alloc->blockCount=(u32)(block.size/blockSize);
		alloc->pool=(pool_block*)block.mem;
		for (u32 i=0;i<alloc->blockCount;++i)
		{
			pool_block* current=alloc->pool+i;
			current->next=
				i==alloc->blockCount-1?0:current+1;

		}
	}
	blk<void> alloc_pool(allocator* alloc)
	{
		blk<void> result;
		if (alloc->pool)
		{
			result=blk<void>(alloc->pool,
					alloc->blockSize);
			alloc->pool=alloc->pool->next;
			alloc->used+=alloc->blockSize;
		}
		return result;
	}
	b32 free_pool(allocator* alloc,blk<void>& block)
	{
		b32 result=0;
		if (alloc->owns(block))
		{
			pool_block* newBlock=(pool_block*)block.mem;
			newBlock->next=alloc->pool;
			alloc->pool=newBlock;
			alloc->used-=alloc->blockSize;
			result=1;
		}
		return result;
	}
	void clear_pool(allocator* alloc)
	{
		alloc->pool=(pool_block*)alloc->buffer.mem;
		for (u32 i=0;i<alloc->blockCount;++i)
		{
			pool_block* current=alloc->pool+i;
			current->next=i==alloc->blockCount-1?0:current+1;

		}
		alloc->used=0;
	}
	struct best_fit_result
	{
		free_block* prev;
		free_block* best;
	};
	best_fit_result best_fit(free_block* freeList,msize size)
	{
		best_fit_result result={};
		free_block* best=0;
		free_block* bestPrev=0;
		msize minDiff=0xFFFFFFFFFFFFFFFF;
		free_block* current=freeList;
		free_block* prev=0;
		while (current)
		{
			if (current->size<size)
			{
				continue;
			}
			msize sizeDiff=current->size-size;
			if (sizeDiff==0)
			{
				best=current;
				minDiff=sizeDiff;
				break;
			}
			else if (sizeDiff<minDiff)
			{
				best=current;
				bestPrev=prev;
				minDiff=sizeDiff;
			}
			prev=current;
			current=current->next;
		}
		if (best)
		{
			result.best=best;
			result.prev=bestPrev;
		}
		return result;
	}

	void init_free_list(allocator* alloc, blk<void>& block)
	{
		alloc->buffer=block;

		alloc->freeList=(free_block*)block.mem;
		alloc->freeList->next=0;
		alloc->freeList->size=block.size;
		alloc->used=0;
	}
	blk<void> alloc_free_list(allocator* alloc,msize size)
	{
		if (size<sizeof(free_block))
		{
			size=sizeof(free_block);
		}
		blk<void> result;
		if (alloc->used+size<=alloc->buffer.size)
		{
			best_fit_result bestFit=
				best_fit(alloc->freeList,size);
			if (bestFit.best)
			{

				free_block* best=bestFit.best;
				free_block* prev=bestFit.prev;

				msize sizeDiff=best->size-size;
				if (sizeDiff<sizeof(free_block))
				{
					size+=sizeDiff;
					sizeDiff=0;
				}
				if (sizeDiff>=sizeof(free_block))
				{
					msize newSize=sizeDiff;
					free_block* newBlock=
						(free_block*)ptr_add(best,size);
					newBlock->size=sizeDiff;
					newBlock->next=best->next;
					if (prev)
					{
						prev->next=newBlock;
					}
					else
					{
						alloc->freeList=newBlock;
					}
				}
				result.mem=best;
				result.size=size;
				alloc->used+=size;
			}
		}
		return result;
	}
	b32 free_free_list(allocator* alloc,
			blk<void>& blockToFree)
	{
		b32 result=0;
		free_block* toFree=(free_block*)blockToFree.mem;
		toFree->size=blockToFree.size;
		if (toFree->size<sizeof(free_block))
		{
			toFree->size=sizeof(free_block);
		}
		if (alloc->owns(blockToFree))
		{
			free_block* current=alloc->freeList;
			free_block* prev=0;
			msize sizeToFree=toFree->size;

			while (current&&current<toFree)
			{
				prev=current;
				current=current->next;
			}
			if (prev) // not adding block to the beginning?
			{
				void* prevEnd=end_addr(prev,prev->size);
				msize distP2C=mem_size(prevEnd,toFree);
				if (distP2C<sizeof(free_block)) // small gap?
				{
					// no gap!
					prev->size+=distP2C;
					distP2C=0;
				}
				if (distP2C==0) // no gap?
				{
					// merge!
					prev->size=prev->size+toFree->size;
					toFree=prev;
				}
				else // gap
				{
					// link prev node up
					prev->next=toFree;
				}
			}
			else // adding to beginning?
			{
				// set freeList head
				alloc->freeList=toFree;
			}

			if (current) // not adding to end of list?
			{
				void* toFreeEnd=end_addr(toFree,toFree->size);
				msize distF2C=mem_size(toFreeEnd,current);
				if (distF2C<sizeof(free_block)) // small gap?
				{
					// no gap!
					toFree->size+=distF2C;
					sizeToFree+=distF2C;
					distF2C=0;
				}
				if (distF2C==0) // no gap?
				{
					// merge!
					toFree->size=toFree->size+current->size;
					toFree->next=current->next;
				}
				else // gap?
				{
					// link up
					toFree->next=current;
					if (prev)
					{
						prev->next=toFree;
					}
				}
			}
			else // adding to end of list?
			{
				if (prev)
				{
					prev->next=toFree; // not necessary...?
				}
			}

			result=1;
			alloc->used-=sizeToFree;
		}
		return result;
	}
	void clear_free_list(allocator* alloc)
	{
		alloc->freeList=(free_block*)alloc->buffer.mem;
		alloc->freeList->size=alloc->buffer.size;
		alloc->used=0;
	}
}

allocator::allocator()
{
	type=alloc_t::NONE;
	buffer=blk<void>();
	used=0;
	stateCount=0;
	prevState=0;
	blockSize=0;
	blockCount=0;
	pool=0;
	freeList=0;
}

allocator::allocator(alloc_t type,msize blockSize)
	: allocator()
{
	this->type=type;
	this->blockSize=blockSize;
}

allocator::allocator(alloc_t type,void* ptr,msize size,
		msize blockSize)
	: allocator(type,blockSize)
{
	blk<void> block=blk<void>(ptr,size);
	switch (type)
	{
		case alloc_t::POOL:
			{
				::init_pool(this,block,blockSize);
			} break;
		case alloc_t::FREE_LIST:
			{
				::init_free_list(this,block);
			} break;
		default:
			{
				this->buffer=block;
			} break;
	}
}


allocator::allocator(alloc_t type,blk<void>& block,
		msize blockSize)
	: allocator(type,block.mem,block.size,blockSize)
{

}

msize allocator::available_mem() const
{
	return buffer.size-used;
}

msize allocator::used_mem() const
{
	return used;
}

blk<void> allocator::alloc(msize size)
{
	blk<void> result=NULL_BLK<void>;
	switch (type)
	{
		case alloc_t::LINEAR:
			{
				result=::alloc_linear(this,size);
			} break;
		case alloc_t::STACK:
			{
				result=::alloc_stack(this,size);
			} break;
		case alloc_t::POOL:
			{
				result=::alloc_pool(this);
			} break;
		case alloc_t::FREE_LIST:
			{
				result=::alloc_free_list(this,size);
			} break;
	}
	return result;
}

b32 allocator::free(blk<void>& block)
{
	b32 result=owns(block);
	switch (type)
	{
		case alloc_t::LINEAR:
			{
				result=false;
			} break;
		case alloc_t::STACK:
			{
				result=::free_stack(this,block);
			} break;
		case alloc_t::POOL:
			{
				result=::free_pool(this,block);
			} break;
		case alloc_t::FREE_LIST:
			{
				result=::free_free_list(this,block);
			} break;
	}
	return result;
}

void allocator::clear()
{
	switch (type)
	{
		case alloc_t::LINEAR:
			{
				::clear_linear(this);
			} break;
		case alloc_t::STACK:
			{
				::clear_stack(this);
			} break;
		case alloc_t::POOL:
			{
				::clear_pool(this);
			} break;
		case alloc_t::FREE_LIST:
			{
				::clear_free_list(this);
			} break;
	}
}

b32 allocator::owns(const blk<void>& block) const
{
	return block.mem>=this->buffer.mem&&
		block.mem<=this->buffer.mem;
}

stack_state allocator::save_stack()
{
	stack_state result=0;
	if (type==alloc_t::STACK)
	{
		result=::save_stack(this);
	}
	return result;
}

b32 allocator::restore_stack(stack_state state)
{
	b32 result=0;
	if (type==alloc_t::STACK)
	{
		result==::restore_stack(this,state);
	}
	return result;
}

b32 allocator::is_stack_balanced() const
{
	b32 result=0;
	if (type==alloc_t::STACK)
	{
		result==::is_stack_balanced(this);
	}
	return result;
}
