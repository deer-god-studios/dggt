#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	allocator<alloc_t::STACK>::allocator()
	{
		buff=blk<void>();
		used=0;
		stateCount=0;
		prevState=0;
	}
	allocator<alloc_t::STACK>::allocator(void* ptr,msize size)
		: allocator()
	{
		buff.mem=ptr;
		buff.size=size;
	}

	allocator<alloc_t::STACK>::allocator(blk<void> buffer)
		: allocator(buffer.mem,buffer.size) { }

	blk<void> allocator<alloc_t::STACK>::alloc(msize size)
	{
		void* result=alloc(&size);
		return blk<void>(result,size);
	}

	void* allocator<alloc_t::STACK>::alloc(msize* size)
	{
		void* result=0;
		if (size&&*size)
		{
			if (used+*size<=buff.size)
			{
				result=ptr_add(buff.mem,used);
				used+=*size;
			}
			else
			{
				*size=0;
			}
		}
		else
		{
			msize s=sizeof(T);
			if (used+s<=buff.size)
			{
				result=ptr_add(buff.mem,used);
				used+=s;
			}
		}
		return result;
	}

	b32 allocator<alloc_t::STACK>::free(void* ptr,msize size)
	{
		b32 result=0;
		blk<void> b=blk<void>(ptr,size);
		if (owns(b)&&
				used-size>=(msize)prevState)
		{
			void* allocEndAddr=ptr_add(buff.mem,used);
			void* blkEndAddr=ptr_add(ptr,size);
			if (allocEndAddr==blkEndAddr)
			{
				used-=size;
				result=1;
			}
		}
		return result;
	}

	b32 allocator<alloc_t::STACK>::free(blk<void> block)
	{
		return free(block.mem,block.size);
	}

	stack_state allocator<alloc_t::STACK>::save_stack()
	{
		stack_state result=(stack_state)used;
		prevState=result;
		++stateCount;
		return result;
	}

	b32 allocator<alloc_t::STACK>::restore_stack(stack_state state)
	{
		b32 result=state==prevState;
		if (result)
		{
			used=state;
			--stateCount;
		}
		return result;
	}

	void allocator<alloc_t::STACK>::clear()
	{
		used=0;
		stateCount=0;
		prevState=0;
	}

	b32 allocator<alloc_t::STACK>::is_stack_balanced() const
	{
		return stateCount==0;
	}

	b32 allocator<alloc_t::STACK>::owns(const void* ptr) const
	{
		return ptr>=buff.mem&&
			ptr<=ptr_add(buff.mem,buff.size);
	}

	b32 allocator<alloc_t::STACK>::owns(blk<void> block) const
	{
		return owns(block.mem)&&
			ptr_add(block.mem,block.size)<=ptr_add(buff.mem,buff.size);
	}

	msize allocator<alloc_t::STACK>::available_mem() const
	{
		return buff.size-used;
	}

	msize allocator<alloc_t::STACK>::used_mem() const
	{
		return used;
	}
}
