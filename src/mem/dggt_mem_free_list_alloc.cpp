#include "dggt_mem_free_list_alloc.h"

struct free_block
{
	msize size;
	free_block* next;
};


namespace
{
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
}

allocator<alloc_t::FREE_LIST>::allocator()
{
	block.mem=0;
	block.size=0;
	freeList=0;
	used=0;
}

allocator<alloc_t::FREE_LIST>::allocator(blk<void>& block)
{
	this->block.mem=block.mem;
	this->block.size=block.size;

	freeList=(::free_block*)block.mem;
	freeList->next=0;
	freeList->size=block.size;
	used=0;
}

allocator<alloc_t::FREE_LIST>::allocator(void* ptr,msize size)
{
	block.mem=ptr;
	block.size=size;
	freeList=(::free_block*)block.mem;
	freeList->next=0;
	freeList->size=block.size;
	used=0;
}

blk<void> allocator<alloc_t::FREE_LIST>::alloc(msize size)
{
	if (size<sizeof(::free_block))
	{
		size=sizeof(::free_block);
	}
	blk<void> result;
	if (used+size<=block.size)
	{
		::best_fit_result bestFit=best_fit(freeList,size);
		if (bestFit.best)
		{

			::free_block* best=bestFit.best;
			::free_block* prev=bestFit.prev;

			msize sizeDiff=best->size-size;
			if (sizeDiff<sizeof(::free_block))
			{
				size+=sizeDiff;
				sizeDiff=0;
			}
			if (sizeDiff>=sizeof(::free_block))
			{
				msize newSize=sizeDiff;
				::free_block* newBlock=
					(::free_block*)ptr_add(best,size);
				newBlock->size=sizeDiff;
				newBlock->next=best->next;
				if (prev)
				{
					prev->next=newBlock;
				}
				else
				{
					freeList=newBlock;
				}
			}
			result.mem=best;
			result.size=size;
			used+=size;
		}
	}
	return result;
}

void allocator<alloc_t::FREE_LIST>::free(blk<void>& blockToFree)
{
	::free_block* toFree=(::free_block*)blockToFree.mem;
	toFree->size=blockToFree.size;
	if (toFree->size<sizeof(::free_block))
	{
		toFree->size=sizeof(::free_block);
	}
	if (owns(block))
	{
		::free_block* current=freeList;
		::free_block* prev=0;
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
			if (distP2C<sizeof(::free_block)) // small gap?
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
			freeList=toFree;
		}

		if (current) // not adding to end of list?
		{
			void* toFreeEnd=end_addr(toFree,toFree->size);
			msize distF2C=mem_size(toFreeEnd,current);
			if (distF2C<sizeof(::free_block)) // small gap?
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

		used-=sizeToFree;
	}
}

void allocator<alloc_t::FREE_LIST>::clear()
{
	freeList=(::free_block*)block.mem;
	freeList->size=block.size;
	used=0;
}

b32 allocator<alloc_t::FREE_LIST>::owns(const blk<void>& block) const
{
	return block.mem>=this->block.mem&&
		end_addr(block.mem,block.size)<=
		end_addr(this->block.mem,this->block.size);
}

msize allocator<alloc_t::FREE_LIST>::available() const
{
	return block.size-used;
}

//allocator<alloc_t::FREE_LIST>::
