#ifndef _DGGT_MEM_NULL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t_args<ALLOC_T_NULL>>
	{
		static const u32 TYPE=ALLOC_T_NULL;
	};

	typedef allocator<alloc_t_args<ALLOC_T_NULL>> null_alloc;

	blkv alloc(null_alloc* a,msize size=4);

	void* alloc(null_alloc* a,msize* size=0);

	template <typename T>
	T* alloc(null_alloc* a,u32* count=0);

	template <typename T>
	blk<T> alloc(null_alloc* a,u32 count=1);

	b32 free(null_alloc* a,void* ptr,msize size);

	b32 free(null_alloc* a,blkv block);

	template <typename T>
	b32 free(null_alloc* a,T* ptr,u32 count);

	template <typename T>
	b32 free(null_alloc* a,blk<T> block);

	b32 clear(null_alloc* a);
	
	b32 owns(const null_alloc* a,const void* ptr,msize size);

	b32 owns(const null_alloc* a,const blkv block);

	template <typename T>
	b32 owns(const null_alloc* a,const T* ptr,u32 count);

	template <typename T>
	b32 owns(const null_alloc* a,const blk<T> block);

	stack_state save_stack(null_alloc* a);

	b32 restore_stack(null_alloc* a,stack_state state);

	b32 is_stack_balanced(null_alloc* a);

	msize used_mem(null_alloc* a);

	msize available_mem(null_alloc* a);
}

#include "dggt_mem_null_alloc.inl"

#define _DGGT_MEM_NULL_ALLOC_H_
#endif
