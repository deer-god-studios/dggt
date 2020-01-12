#include "dggt_mem_free_list_alloc.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	struct free_block
	{
		msize size;
		free_block* next;
	};

	namespace dggt_internal_
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
		buff=blk<void>();
		used=0;
		freeList=0;
	}

	allocator<alloc_t::FREE_LIST>::allocator(void* ptr,msize size)
		: allocator()
	{
		ASSERT(size>=sizeof(free_block));
		if (ptr&&size)
		{
			buff.mem=ptr;
			buff.size=size;
			freeList=(free_block*)ptr;
			freeList->next=0;
			freeList->size=size;
		}
	}

	allocator<alloc_t::FREE_LIST>::allocator(blk<void> buffer)
		: allocator(buffer.mem,buffer.size) { }

	void* allocator<alloc_t::FREE_LIST>::alloc(msize* size)
	{
		void* result=0;
		if (size&&*size)
		{
			if (*size<sizeof(free_block))
			{
				*size=sizeof(free_block);
			}
			if (used+*size<=buff.size)
			{
				dggt_internal_::best_fit_result bestFit=
					dggt_internal_::best_fit(freeList,*size);
				if (bestFit.best)
				{

					free_block* best=bestFit.best;
					free_block* prev=bestFit.prev;

					msize sizeDiff=best->size-*size;
					if (sizeDiff<sizeof(free_block))
					{
						*size+=sizeDiff;
						sizeDiff=0;
					}
					if (sizeDiff>=sizeof(free_block))
					{
						msize newSize=sizeDiff;
						free_block* newBlock=
							(free_block*)ptr_add(best,*size);
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
					result=best;
					used+=*size;
				}
			}
		}
		else
		{
			*size=0;
		}
		return result;
	}

	blk<void> allocator<alloc_t::FREE_LIST>::alloc(msize size)
	{
		blk<void> result;
		if (size)
		{
			result.mem=alloc(&size);
			result.size=size;
		}
		return result;
	}

	b32 allocator<alloc_t::FREE_LIST>::free(void* ptr,msize size)
	{
		b32 result=0;
		free_block* toFree=(free_block*)ptr;
		toFree->size=size;
		if (toFree->size<sizeof(free_block))
		{
			toFree->size=sizeof(free_block);
		}
		if (owns(blk<void>(ptr,size)))
		{
			free_block* current=freeList;
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
				msize distP2C=size_diff(prevEnd,toFree);
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
				freeList=toFree;
			}

			if (current) // not adding to end of list?
			{
				void* toFreeEnd=end_addr(toFree,toFree->size);
				msize distF2C=size_diff(toFreeEnd,current);
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
			used-=sizeToFree;
		}
		return result;
	}

	b32 allocator<alloc_t::FREE_LIST>::free(blk<void> block)
	{
		return free(block.mem,block.size);
	}

	void allocator<alloc_t::FREE_LIST>::clear()
	{
		freeList=(free_block*)buff.mem;
		freeList->size=buff.size;
		used=0;
	}

	b32 allocator<alloc_t::FREE_LIST>::owns(const void* ptr) const
	{
		return ptr>=buff.mem&&ptr<=ptr_add(buff.mem,buff.size);
	}

	b32 allocator<alloc_t::FREE_LIST>::owns(const blk<void> block) const
	{
		return owns(block.mem)&&
			ptr_add(block.mem,block.size)<=ptr_add(buff.mem,buff.size);
	}

	msize allocator<alloc_t::FREE_LIST>::available_mem() const
	{
		return buff.size-used;
	}

	msize allocator<alloc_t::FREE_LIST>::used_mem() const
	{
		return used;
	}
}
