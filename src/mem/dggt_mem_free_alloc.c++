#include "dggt_mem_free_alloc.h"

namespace dggt
{
	namespace internal_
	{
		void* free_alloc_malloc(allocator* a,msize size)
		{
			void* result=0;
			free_alloc* freeAlloc=(free_alloc*)a;
			if (freeAlloc)
			{
				if (size<sizeof(free_block)) // adjust size
				{
					size=sizeof(free_block);
				}
				free_block* current=(free_block*)freeAlloc->freeList; // grab head.
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
						// split and hook up.
						free_block* newBlock=(free_block*)ptr_add(result,size);
						newBlock->next=bestFit->next;
						newBlock->size=minDiff;
						if (bestFitPrev)
							bestFitPrev->next=newBlock;
						else
							freeAlloc->freeList=newBlock;
					}
					else if (minDiff>0)
					{
						size+=minDiff; // adjust size.
					}
					freeAlloc->used+=size;
				}
			}
			return result;
		}

		vpage free_alloc_malloc_vpage(allocator* a,msize size)
		{
			return vpage(free_alloc_malloc(a,size),size);
		}

		b32 free_alloc_free(allocator* a,void* ptr,msize size)
		{
			b32 result=false;
			free_alloc* freeAlloc=(free_alloc*)a;
			if (freeAlloc&&owns(freeAlloc,ptr,size))
			{
				result=true;
				if (size<sizeof(free_block)) // adjust size.
				{
					size=sizeof(free_block);
				}
				free_block* newBlock=(free_block*)ptr;
				newBlock->size=size;
				free_block* current=freeAlloc->freeList;
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
						freeAlloc->freeList=newBlock;
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
						freeAlloc->freeList=newBlock;
					}
				}
				freeAlloc->used-=size;
			}
			return result;
		}

		b32 free_alloc_free(allocator* a,vpage& pge)
		{
			return free_alloc_free(a,pge.ptr,pge.size);
		}

		b32 free_alloc_clear(allocator* a)
		{
			b32 result=false;
			free_alloc* freeAlloc=(free_alloc*)a;
			if (freeAlloc)
			{
				freeAlloc->freeList=(free_block*)get_buff_ptr(freeAlloc);
				freeAlloc->freeList->next=0;
				freeAlloc->freeList->size=get_capacity(freeAlloc);
				freeAlloc->used=0;
			}
			return result;
		}

		global alloc_func_table FREE_ALLOC_TABLE=
		{
			free_alloc_malloc,
			free_alloc_malloc_vpage,
			free_alloc_free,
			free_alloc_free,
			free_alloc_clear,
			buff_alloc_owns,
			buff_alloc_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			lin_alloc_get_used,
			lin_alloc_get_available,
			buff_alloc_get_capacity,
			buff_alloc_get_buff,
			buff_alloc_get_buff,
			buff_alloc_get_buff_ptr,
			buff_alloc_get_buff_ptr
		};
	}

	free_alloc::free_alloc(alloc_func_table* tbl,vpage buff)
		:lin_alloc(tbl,buff),freeList((free_block*)buff.ptr)
	{
		if (freeList)
		{
			freeList->size=buff.size;
			freeList->next=0;
		}
	}

	free_alloc::free_alloc()
		:free_alloc(&internal_::FREE_ALLOC_TABLE,vpage()) { }

	free_alloc::free_alloc(void* ptr,msize size)
		:free_alloc(&internal_::FREE_ALLOC_TABLE,vpage(ptr,size)) { }

	free_alloc::free_alloc(vpage buff)
		:free_alloc(buff.ptr,buff.size) { }
}
