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
			msize minDiff=MAX_MSIZE;
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

	free_list_alloc_::free_list_alloc_()
	{
		buff=vblk();
		used=0;
		freeList=0;
	}

	free_list_alloc_::free_list_alloc_(void* ptr,msize size)
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

	free_list_alloc_::free_list_alloc_(vblk block)
		: free_list_alloc_(block.mem,block.size)
	{
	}

	void* alloc(free_list_alloc* a,msize* size)
	{
		void* result=0;
		msize s=size?*size:4;
		if (s<sizeof(free_block))
		{
			s=sizeof(free_block);
		}
		if (a->used+s<=a->buff.size)
		{
			dggt_internal_::best_fit_result bestFit=
				dggt_internal_::best_fit(a->freeList,s);
			if (bestFit.best)
			{

				free_block* best=bestFit.best;
				free_block* prev=bestFit.prev;

				msize sizeDiff=best->size-s;
				if (sizeDiff<sizeof(free_block))
				{
					s+=sizeDiff;
					sizeDiff=0;
				}
				if (sizeDiff>=sizeof(free_block))
				{
					msize newSize=sizeDiff;
					free_block* newBlock=
						(free_block*)ptr_add(best,s);
					newBlock->size=sizeDiff;
					newBlock->next=best->next;
					if (prev)
					{
						prev->next=newBlock;
					}
					else
					{
						a->freeList=newBlock;
					}
				}
				result=best;
				a->used+=s;
				if (size)
				{
					*size=s;
				}
			}
		}
		return result;
	}

	vblk alloc(free_list_alloc* a,msize size)
	{
		vblk result;
		result.mem=alloc(a,&size);
		result.size=size;
		return result;
	}

	b32 free(free_list_alloc* a,msize size)
	{
		b32 result=0;
		free_block* toFree=(free_block*)ptr;
		toFree->size=size;
		if (toFree->size<sizeof(free_block))
		{
			toFree->size=sizeof(free_block);
		}
		if (owns(a,ptr,size))
		{
			free_block* current=a->freeList;
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
				a->freeList=toFree;
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
			a->used-=sizeToFree;
		}
		return result;
	}

	b32 free(free_list_alloc* a,vblk block)
	{
		return free(a,block.mem,block.size);
	}

	b32 clear(free_list_alloc* a)
	{
		a->freeList=(free_block*)a->buff.mem;
		a->freeList->size=a->buff.size;
		a->used=0;
		return 1;
	}

	b32 owns(const free_list_alloc* a,const void* ptr,msize size)
	{
		return ptr>=a->buff.mem&&
			ptr_add(ptr,size)<=ptr_add(a->buff.mem,a->buff.size);
	}

	b32 owns(const free_list_alloc* a,const vblk block)
	{
		return owns(a,block.mem,block.size);
	}

	msize available_mem(const free_list_alloc* a)
	{
		return a->buff.size-a->used;
	}

	msize used_mem(const free_list_alloc* a)
	{
		return a->used;
	}
}
