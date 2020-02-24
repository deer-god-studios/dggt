#include "dggt_mem_utils.h"

namespace dggt
{
	void* ptr_add(const void* ptr,msize offset)
	{
		return (void*)((uint8_t*)ptr+offset);
	}

	void* ptr_sub(const void* ptr,msize offset)
	{
		return (void*)((uint8_t*)ptr-offset);
	}

	void* end_addr(const void* ptr,msize size)
	{
		return ptr_add(ptr,size);
	}

	msize size_diff(const void* addr0,const void* addr1)
	{
		const void* beginAddr=addr0;
		const void* endAddr=addr1;
		msize result=0;
		if (endAddr<beginAddr)
		{
			const void* temp=beginAddr;
			beginAddr=endAddr;
			endAddr=temp;
		}

		if (endAddr==beginAddr)
		{
			result=0;
		}
		else
		{
			result=(msize)((uintptr_t)endAddr-(uintptr_t)beginAddr);
		}
		return result;
	}

	void mem_cpy(void* dest,void* src,msize size)
	{
		for (msize b=0;b<size;++b)
		{
			*((ubyte*)dest+b)=*((ubyte*)src+b);
		}
	}

	void zero_mem(void* mem,msize size)
	{
		for (msize b=0;b<size;++b)
		{
			*((ubyte*)mem+b)=0;
		}
	}
}
