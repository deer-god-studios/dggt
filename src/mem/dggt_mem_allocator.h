/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_ALLOC_H_
/*! @endcond */

// TODO: implement is_valid(block) to check if a block has already been 'freed'.


namespace dggt
{
	/*!
	 * @addtogroup mem
	 * @{
	 * */

	typedef u32 alloc_t;
	typedef msize stack_state;

	global const alloc_t ALLOC_T_NULL=0;
	global const alloc_t ALLOC_T_LIN=1;
	global const alloc_t ALLOC_T_STACK=2;
	global const alloc_t ALLOC_T_AUTOSTACK=3;
	global const alloc_t ALLOC_T_FREE=4;
	global const alloc_t ALLOC_T_POOL=5;
	global const alloc_t ALLOC_T_FALLBACK=6;
	global const alloc_t ALLOC_T_STORE=7;
	global const alloc_t ALLOC_T_STORE_TABLE=8;

	global const alloc_t ALLOC_T_LIB_END=ALLOC_T_STORE_TABLE;
	global const alloc_t ALLOC_T_BEGIN=ALLOC_T_LIB_END+1;

	global const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	global const msize DEF_BLOCKSIZE=BYTES(4);

	global const msize DEF_TABLESIZE=4096;

	struct allocator
	{
		const alloc_t TYPE;

		allocator(alloc_t type):TYPE(type) { }
	};

	void* alloc(allocator* a,msize size=4);

	template <typename T>
	T* alloc(allocator* a,u32 count=1);

	b32 free(allocator* a,void* ptr,msize size=4);
	
	template <typename T>
	b32 free(allocator* a,T* ptr,u32 count=1);

	b32 clear(allocator* a);

	b32 owns(const allocator* a,const void* ptr,msize size=4);

	template <typename T>
	b32 owns(const allocator* a,const T* ptr,u32 count=1);

	stack_state save_stack(allocator* a);

	b32 restore_stack(allocator* a,stack_state state);

	b32 is_stack_balanced(const allocator* a);

	msize used_mem(const allocator* a);

	msize available_mem(const allocator* a);
}

#include "dggt_mem_allocator.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond  */
