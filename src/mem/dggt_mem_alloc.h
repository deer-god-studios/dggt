/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_ALLOC_H_
/*! @endcond */

// TODO: implement is_valid(block) to check if a block has already 
// 		been 'freed'.
// TODO: allow pool allocs to free multiple blocks. 

#include "dggt_mem_blk.h"

 // TODO: fix allocators!  This enumerator shit sucks.

namespace dggt
{
	/*!
	 * @addtogroup mem
	 * @{
	 * */

	global const alloc_t ALLOC_T_NULL=0;
	global const alloc_t ALLOC_T_LINEAR=1;
	global const alloc_t ALLOC_T_STACK=2;
	global const alloc_t ALLOC_T_AUTOSTACK=3;
	global const alloc_t ALLOC_T_FREE=4;
	global const alloc_t ALLOC_T_POOL=5;
	global const alloc_t ALLOC_T_FALLBACK=6;
	global const alloc_t ALLOC_T_STORE=7;
	global const alloc_t ALLOC_T_STORE_TABLE=8;

	global const alloc_t ALLOC_T_LIB_END=ALLOC_T_STORE_TABLE;
	global const alloc_t ALLOC_T_BEGIN=ALLOC_T_LIB_END+1;

	template <alloc_t ALLOC_T,u32... S> 
	struct allocator
	{
		static const u32 TYPE=ALLOC_T; 
	};

	template <alloc_t ALLOC_T,u32... S>
	blkv alloc(allocator<ALLOC_T,S...>* a,msize size=4);
	
	template <alloc_t ALLOC_T,u32... S>
	void* alloc(allocator<ALLOC_T,S...>* a,msize* size=0);

	template <typename T,alloc_t ALLOC_T, u32... S>
	blk<T> alloc(allocator<ALLOC_T,S...>* a,u32 count=1);

	template <typename T,alloc_t ALLOC_T, u32... S>
	T* alloc(allocator<ALLOC_T,S...>* a,u32* count=0);

	template <alloc_t ALLOC_T,u32... S>
	b32 free(allocator<ALLOC_T,S...>* a,void* ptr,msize size);
	
	template <alloc_t ALLOC_T,u32... S>
	b32 free(allocator<ALLOC_T,S...>* a,blkv block);

	template <typename T,alloc_t ALLOC_T, u32... S>
	b32 free(allocator<ALLOC_T,S...>* a,T* ptr,u32 count);

	template <typename T,alloc_t ALLOC_T, u32... S>
	b32 free(allocator<ALLOC_T,S...>* a,blk<T> block);

	template <alloc_t ALLOC_T,u32... S>
	b32 clear(allocator<ALLOC_T,S...>* a);

	template <alloc_t ALLOC_T,u32... S>
	b32 owns(const allocator<ALLOC_T,S...>* a,const void* ptr,msize size);

	template <alloc_t ALLOC_T,u32... S>
	b32 owns(const allocator<ALLOC_T,S...>* a,const blkv block);

	template <typename T,alloc_t ALLOC_T, u32... S>
	b32 owns(const allocator<ALLOC_T,S...>* a,const blk<T> block);
	
	template <typename T,alloc_t ALLOC_T, u32... S>
	b32 owns(const allocator<ALLOC_T,S...>* a,const T* ptr,u32 count);

	template <alloc_t ALLOC_T,u32... S>
	stack_state save_stack(allocator<ALLOC_T,S...>* a);

	template <alloc_t ALLOC_T,u32... S>
	b32 restore_stack(allocator<ALLOC_T,S...>* a,stack_state state);

	template <alloc_t ALLOC_T,u32... S>
	b32 is_stack_balanced(allocator<ALLOC_T,S...>* a);

	template <alloc_t ALLOC_T,u32... S>
	msize used_mem(allocator<ALLOC_T,S...>* a);

	template <alloc_t ALLOC_T,u32... S>
	msize available_mem(allocator<ALLOC_T,S...>* a);

	template <alloc_t ALLOC_T,u32... S>
	u32 get_block_size(allocator<ALLOC_T,S...>* a);
}

//#include "dggt_mem_alloc.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond  */
