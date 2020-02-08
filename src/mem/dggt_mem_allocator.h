/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_ALLOC_H_
/*! @endcond */

// TODO: implement is_valid(block) to check if a block has already 
// 		been 'freed'.
// TODO: allow pool allocs to free multiple blocks. 

#include "dggt_mem_blk.h"

namespace dggt
{
	struct pool_block;
	struct store_block;
	struct free_block;

	template <typename D>
	struct allocator
	{
		D* derived;
		allocator(D* derivedAlloc);
	};

	template <typename D>
	vblk alloc(allocator<D>* a,msize size=4);

	template <typename D>
	void* alloc(allocator<D>* a,msize* size=0);

	template <typename D,typename T>
	blk<T> alloc(allocator<D>* a,u32 count=1);

	template <typename D,typename T>
	T* alloc(allocator<D>* a,u32* count=0);

	template <typename D>
	b32 free(allocator<D>* a,void* ptr,msize size);

	template <typename D>
	b32 free(allocator<D>* a,vblk block);

	template <typename D,typename T>
	b32 free(allocator<D>* a,T* ptr,u32 count);

	template <typename D,typename T>
	b32 free(allocator<D>* a,blk<T> block);

	template <typename D>
	b32 clear(allocator<D>* a);

	template <typename D>
	b32 owns(const allocator<D>* a,const void* ptr,msize size);

	template <typename D,typename T>
	b32 owns(const allocator<D>* a,const blk<T> block);
	
	template <typename D,typename T>
	b32 owns(const allocator<D>* a,const T* ptr,u32 count);
}

#include "dggt_mem_alloc.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond  */
