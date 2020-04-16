#include "dggt_mem_free_alloc.h"

namespace dggt
{
	void* malloc(free_alloc* a,msize size)
	{
		void* result=0;
		if (a)
		{
			if (size<sizeof(free_block)) // adjust size
			{
				size=sizeof(free_block);
			}
			free_block* current=(free_block*)a->freeList; // grab head.
			free_block* prev=0;
			msize minDiff=MAX_MSIZE;
			free_block* bestFit=0;
			free_block* bestFitPrev=0;
			while (current) // find best fit.
			{
				msize blockSize=current->size;
				if (blockSize>=size) // block is big enough.
				{
					msize diff=blockSize-size;
					if (diff<minDiff) // smaller diff
					{
						minDiff=diff;
						bestFit=current;
						bestFitPrev=prev;
						if (diff==0) // perfect fit.
						{
							break;
						}
					}
				}
				// increment.
				prev=current;
				current=current->next;
			}
			if (bestFit) // found one.
			{
				result=bestFit; // set result.
				if (minDiff>=sizeof(free_block)) // needs splitting.
				{
					size+=minDiff; // adjust size.
					// split and hook up.
					free_block* newBlock=(free_block*)ptr_add(result,size);
					newBlock->next=bestFit->next;
					newBlock->size=minDiff;
					if (prev)
						prev->next=newBlock;
				}
				a->linAlloc.used+=size;
			}
		}
		return result;
	}
	
	b32 free(free_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a&&owns(a,ptr,size))
		{
			result=true;
			if (size<sizeof(free_block)) // adjust size.
			{
				size=sizeof(free_block);
			}
			free_block* newBlock=(free_block*)ptr;
			newBlock->size=size;
			free_block* current=a->freeList;
			free_block* prev=0;
			while (current&&current<newBlock) // find where newBlock fits.
			{
				ASSERT(current!=newBlock); // can't free a block twice.
				prev=current;
				current=current->next;
			}

			// ... prev newBlock current ...
			if (current)
			{
				if (prev)
				{
					void* prevEnd=ptr_add(prev,prev->size);
					msize rightDiff=size_diff(prevEnd,newBlock);

					if (rightDiff<sizeof(free_block)) // merge right.
					{
						size+=rightDiff; // adjust size.
						prev->size=prev->size+rightDiff+newBlock->size;
						newBlock=prev;
					}
					else // hook prev to newBlock
					{
						prev->next=newBlock;
					}
				}
				else // newBlock is at the beginning.
				{
					a->freeList=newBlock;
				}
				void* newBlockEnd=ptr_add(newBlock,newBlock->size);
				msize leftDiff=size_diff(newBlockEnd,current);
				if (leftDiff<sizeof(free_block)) // merge left.
				{
					size+=leftDiff; // adjust size.
					newBlock->next=current->next;
					newBlock->size=newBlock->size+current->size+leftDiff;
				}
				else // hook newBlock to current
				{
					newBlock->next=current;
				}
			}
			else // newBlock is at the end.
			{
				if (prev)
				{
					void* prevEnd=ptr_add(prev,prev->size);
					msize rightDiff=size_diff(prevEnd,newBlock);

					if (rightDiff<sizeof(free_block)) // merge right.
					{
						size+=rightDiff;
						prev->size=prev->size+rightDiff+newBlock->size;
						newBlock=prev;
					}
					else // hook prev to newBlock
					{
						prev->next=newBlock;
					}
				}
				else // newBlock is the only block.
				{
					a->freeList=newBlock;
				}
			}
			a->linAlloc.used-=size;
		}
		return result;
	}
	
	b32 clear(free_alloc* a)
	{
		b32 result=false;
		if (a)
		{
			a->freeList=(free_block*)get_buff_ptr(a);
			a->freeList->next=0;
			a->freeList->size=get_capacity(a);
			a->linAlloc.used=0;
		}
		return result;
	}
	
	b32 owns(const free_alloc* a,const void* ptr,msize size)
	{
		return owns(&a->linAlloc,ptr,size);
	}

	msize get_used(const free_alloc* a)
	{
		return get_used(&a->linAlloc);
	}
	
	msize get_available(const free_alloc* a)
	{
		return get_available(&a->linAlloc);
	}

	msize get_capacity(const free_alloc* a)
	{
		return get_available(&a->linAlloc);
	}

	void* get_buff_ptr(free_alloc* a)
	{
		return get_buff_ptr(&a->linAlloc);
	}

	const void* get_buff_ptr(const free_alloc* a)
	{
		return get_buff_ptr(&a->linAlloc);
	}
}
