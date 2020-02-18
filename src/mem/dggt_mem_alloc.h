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
	static const u32 NO_BLOCKSIZE=0;
	static const u32 DEF_BLOCKSIZE=BYTES(4);
	static const u32 DEF_BUFFSIZE=KB(10);
 
	static const u32 ALLOC_T_NULL=0;
	static const u32 ALLOC_T_LINEAR=1;
	static const u32 ALLOC_T_STACK=2;
	static const u32 ALLOC_T_AUTOSTACK=3;
	static const u32 ALLOC_T_FREE=4;
	static const u32 ALLOC_T_POOL=5;
	static const u32 ALLOC_T_FALLBACK=6;

	static const u32 ALLOC_T_LIB_END=ALLOC_T_FALLBACK;
	static const u32 ALLOC_T_BEGIN=ALLOC_T_LIB_END+1;

	template <u32 ALLOC_T,u32... S,typename... Ts> 
	struct allocator
	{
		static const u32 TYPE=ALLOC_T; 
	};

	template <u32 ALLOC_T,u32... S,typename... Ts>
	blkv alloc(allocator<ALLOC_T,S...,Ts...>* a,msize size=4);
	
	template <u32 ALLOC_T,u32... S,typename... Ts>
	void* alloc(allocator<ALLOC_T,S...,Ts...>* a,msize* size=0);

	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	blk<T> alloc(allocator<ALLOC_T,S...,Ts...>* a,u32 count=1);

	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	T* alloc(allocator<ALLOC_T,S...,Ts...>* a,u32* count=0);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 free(allocator<ALLOC_T,S...,Ts...>* a,void* ptr,msize size);
	
	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 free(allocator<ALLOC_T,S...,Ts...>* a,blkv block);

	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	b32 free(allocator<ALLOC_T,S...,Ts...>* a,T* ptr,u32 count);

	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	b32 free(allocator<ALLOC_T,S...,Ts...>* a,blk<T> block);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 clear(allocator<ALLOC_T,S...,Ts...>* a);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 owns(const allocator<ALLOC_T,S...,Ts...>* a,const void* ptr,msize size);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 owns(const allocator<ALLOC_T,S...,Ts...>* a,const blkv block);

	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	b32 owns(const allocator<ALLOC_T,S...,Ts...>* a,const blk<T> block);
	
	template <typename T,u32 ALLOC_T, u32... S,typename... Ts>
	b32 owns(const allocator<ALLOC_T,S...,Ts...>* a,const T* ptr,u32 count);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	stack_state save_stack(allocator<ALLOC_T,S...,Ts...>* a);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 restore_stack(allocator<ALLOC_T,S...,Ts...>* a,stack_state state);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	b32 is_stack_balanced(allocator<ALLOC_T,S...,Ts...>* a);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	msize used_mem(allocator<ALLOC_T,S...,Ts...>* a);

	template <u32 ALLOC_T,u32... S,typename... Ts>
	msize available_mem(allocator<ALLOC_T,S...,Ts...>* a);
}

//#include "dggt_mem_alloc.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond  */
