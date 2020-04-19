#ifndef _DGGT_MEM_UTILS_H_

#include "sys/mman.h"
#include "types/dggt_types.h"

namespace dggt
{
	inline void* ptr_add(const void* ptr,msize offset)
	{
		return (void*)((uint8_t*)ptr+offset);
	}

	inline void* ptr_sub(const void* ptr,msize offset)
	{
		return (void*)((uint8_t*)ptr-offset);
	}

	inline void* end_addr(const void* ptr,msize size)
	{
		return ptr_add(ptr,size);
	}

	inline msize size_diff(const void* addr0,const void* addr1)
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

	void* malloc(msize size);

	b32 free(void* ptr,msize size);

	void mem_cpy(void* dest,void* src,msize size);

	void zero_mem(void* mem,msize size);

	template <typename T>
	void zero_struct(T* ptr);
}

#include "dggt_mem_utils.inl"

#define _DGGT_MEM_UTILS_H_
#endif
