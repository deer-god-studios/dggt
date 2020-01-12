#include "dggt_mem_linear_alloc.h"

namespace dggt
{
	allocator<alloc_t::LINEAR>::allocator()
	{
		buff=blk<void>();
		used=0;
	}
	allocator<alloc_t::LINEAR>::allocator(void* ptr,msize size)
		: allocator()
	{
		buff.mem=ptr;
		buff.size=size;
	}
	allocator<alloc_t::LINEAR>::allocator(blk<void> buffer)
		: allocator(buffer.mem,buffer.size) { }

	void* allocator<alloc_t::LINEAR>::alloc(msize* size)
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
		return result;
	}

	blk<void> allocator<alloc_t::LINEAR>::alloc(msize size)
	{
		void* ptr=alloc(&size);
		return blk<void>(ptr,size);
	}

	void allocator<alloc_t::LINEAR>::clear()
	{
		used=0;
	}

	msize allocator<alloc_t::LINEAR>::available_mem() const
	{
		return buff.size-used;
	}

	msize allocator<alloc_t::LINEAR>::used_mem() const
	{
		return used;
	}

	b32 allocator<alloc_t::LINEAR>::owns(const void* ptr) const
	{
		return ptr>=buff.mem&&
			ptr<=ptr_add(buff.mem,buff.size);
	}

	b32 allocator<alloc_t::LINEAR>::owns(const blk<void> block) const
	{
		return owns(block.mem)&&
			// also check block end address (?)
			ptr_add(block.mem,block.size)<=ptr_add(buff.mem,buff.size);
	}
}
