#include "dggt_mem_blk.h"


namespace dggt
{
	blk<void>::blk(void* mem,size_t size)
	{
		this->mem=mem;
		this->size=size;
	}


	blk<void>::blk()
		: blk(0,0) { }


	blk<void>::blk(const blk<void>& other)
		: blk(other.mem,other.size) { }


	blk<void> blk<void>::operator+(uint32_t offset) const
	{
		return blk<void>(ptr_add(mem,offset),size-offset);
	}


	blk<void> blk<void>::operator-(uint32_t offset) const
	{
		return blk<void>(ptr_sub(mem,offset),size+offset);
	}


	blk<void>& blk<void>::operator=(const blk<void>& rhs)
	{
		if (this!=&rhs)
		{
			mem=rhs.mem;
			size=rhs.size;
		}
		return *this;
	}


	uint32_t blk<void>::operator==(const blk<void>& rhs) const
	{
		return this==&rhs||(mem==rhs.mem&&size==rhs.size);
	}


	uint32_t blk<void>::operator!=(const blk<void>& rhs) const
	{
		return this!=&rhs&&(mem!=rhs.mem||size!=rhs.size);
	}


	blk<void>::operator void*()
	{
		return mem;
	}

	blk<void> blk_alloc(msize size)
	{
		void* ptr=mem_alloc(size);
		if (ptr==0)
		{
			size=0;
		}
		return blk<void>(ptr,size);
	}

	void blk_free(blk<void>& block)
	{
		mem_free(block.mem,block.size);
	}
}
