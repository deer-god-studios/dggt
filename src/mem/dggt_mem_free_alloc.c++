#include "dggt_mem_free_alloc.h"

namespace dggt
{
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
					current=current->next;
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

		void* free_alloc(free_block** freeList,msize* used,
				msize buffSize,msize size)
		{
			void* result=0;
			if (size<sizeof(free_block))
			{
				size=sizeof(free_block);
			}
			if (*used+size<=buffSize)
			{
				best_fit_result bestFit=
					best_fit(*freeList,size);
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
							*freeList=newBlock;
						}
					}
					result=best;
					*used+=size;
				}
			}
			return result;
		}

		b32 free_owns(void* buff,msize buffSize,
				const void* ptr,msize size)
		{
			return ptr>=buff&&
				ptr_add(ptr,size)<=ptr_add(buff,buffSize);
		}

		b32 free_free(free_block** freeList,void* buff,msize buffSize,
				void* ptr,msize size,msize* used)
		{
			b32 result=0;
			free_block* toFree=(free_block*)ptr;
			toFree->size=size;
			if (toFree->size<sizeof(free_block))
			{
				toFree->size=sizeof(free_block);
			}
			if (free_owns(buff,buffSize,ptr,size))
			{
				free_block* current=*freeList;
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
					*freeList=toFree;
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
				*used-=sizeToFree;
			}
			return result;
		}

		b32 free_clear(free_block** freeList,void* buff,
				msize buffSize,msize* used)
		{
			*freeList=(free_block*)buff;
			(*freeList)->size=buffSize;
			(*freeList)->next=0;
			*used=0;
			return 1;
		}

		stack_state free_save_stack()
		{
			return SAVE_STACK_FAIL;
		}

		b32 free_restore_stack()
		{
			return false;
		}

		b32 free_is_stack_balanced()
		{
			return true;
		}

		msize free_used_mem(msize used)
		{
			return used;
		}

		msize free_available_mem(msize used,msize buffSize)
		{
			return buffSize-used;
		}
	}

	free_alloc::free_alloc()
	{
		buff=0;
		buffSize=0;
		freeList=0;
		used=0;
	}

	free_alloc::free_alloc(void* ptr,msize size)
		:free_alloc()
	{
		ASSERT(size>=sizeof(free_block));
		buff=ptr;
		buffSize=size;
		freeList=(free_block*)buff;
		freeList->size=buffSize;
		freeList->next=0;
	}

	void* alloc(free_alloc* a,msize size)
	{
		if (a)
		{
			return dggt_internal_::free_alloc(&a->freeList,
					&a->used,a->buffSize,size);
		}
		else
		{
			return 0;
		}
	}

	b32 free(free_alloc* a,void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::free_free(&a->freeList,a->buff,
					a->buffSize,ptr,size,&a->used);
		}
		else
		{
			return 0;
		}
	}
	
	b32 clear(free_alloc* a)
	{
		if (a)
		{
			return dggt_internal_::free_clear(&a->freeList,
					a->buff,a->buffSize,&a->used);
		}
		else
		{
			return 0;
		}
	}

	b32 owns(const free_alloc* a,const void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::free_owns(a->buff,a->buffSize,
					ptr,size);
		}
		else
		{
			return 0;
		}
	}

	stack_state save_stack(free_alloc* a)
	{
		return dggt_internal_::free_save_stack();
	}

	b32 restore_stack(free_alloc* a,stack_state state)
	{
		return dggt_internal_::free_restore_stack();
	}

	b32 is_stack_balanced(const free_alloc* a)
	{
		return dggt_internal_::free_is_stack_balanced();
	}

	msize used_mem(const free_alloc* a)
	{
		return dggt_internal_::free_used_mem(a->used);
	}

	msize available_mem(const free_alloc* a)
	{
		if (a)
		{
			return dggt_internal_::free_available_mem(a->used,a->buffSize);
		}
		else
		{
			return 0;
		}
	}
}
