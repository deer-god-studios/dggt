#ifndef _DGGT_MEM_MEM_H_

#include <stdint.h>
#include <cstddef>
#include <sys/mman.h>
#include "types/dggt_types.h"
#include "dggt_mem_types.h"

namespace dggt
{
	inline void* ptr_add(const void* ptr,uint32_t offset)
	{
		return (void*)((uint8_t*)ptr+offset);
	}

	inline void* ptr_sub(const void* ptr,uint32_t offset)
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

	void* mem_alloc(msize size);
	void mem_free(void* mem,msize size);

	void mem_cpy(void* dest,void* src,msize size);

	void zero_mem(void* mem,msize size);

	template <typename T>
	void zero_struct(T* ptr)
	{
		zero_mem(ptr,sizeof(T));
	}
}
#define _DGGT_MEM_MEM_H_
#endif
