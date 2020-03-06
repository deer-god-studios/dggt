#ifndef _DGGT_MEM_LIN_ALLOC_H_

#include "dggt_mem_allocator.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	struct lin_alloc
	{
		void* buff;
		msize buffSize;
		msize used;

		lin_alloc();
		lin_alloc(void* ptr,msize buffSize);
	};

	void* alloc(lin_alloc* a,msize size);

	b32 free(lin_alloc* a,void* ptr,msize size);
	
	b32 clear(lin_alloc* a);

	b32 owns(const lin_alloc* a,const void* ptr,msize size);

	stack_state save_stack(lin_alloc* a);

	b32 restore_stack(lin_alloc* a,stack_state state);

	b32 is_stack_balanced(const lin_alloc* a);

	msize used_mem(const lin_alloc* a);

	msize available_mem(const lin_alloc* a);

	template <typename T>
	T* alloc(lin_alloc* a,u32 count=1);

	template <typename T>
	b32 free(lin_alloc* a,T* ptr,u32 count=1);

	template <typename T>
	b32 owns(const lin_alloc* a,const T* ptr,u32 count);
}

#include "dggt_mem_lin_alloc.inl"

#define _DGGT_MEM_LIN_ALLOC_H_
#endif
