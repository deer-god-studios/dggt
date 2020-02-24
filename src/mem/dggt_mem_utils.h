#ifndef _DGGT_MEM_UTILS_H_

#include "types/dggt_types.h"

namespace dggt
{
	inline void* ptr_add(const void* ptr,msize offset);

	inline void* ptr_sub(const void* ptr,msize offset);

	inline void* end_addr(const void* ptr,msize size);

	inline msize size_diff(const void* addr0,const void* addr1);

	void* alloc(msize size);

	b32 free(void* ptr,msize size);

	void mem_cpy(void* dest,void* src,msize size);

	void zero_mem(void* mem,msize size);

	template <typename T>
	void zero_struct(T* ptr);
}

#include "dggt_mem_utils.inl"

#define _DGGT_MEM_UTILS_H_
#endif
