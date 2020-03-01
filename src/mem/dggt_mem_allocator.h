#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "types/dggt_types.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	typedef u32 alloc_t;
	typedef msize stack_state;

	global constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	global const alloc_t ALLOC_T_NULL=0;
	global const alloc_t ALLOC_T_LIN=1;
	global const alloc_t ALLOC_T_STACK=2;
	global const alloc_t ALLOC_T_FREE=4;
	global const alloc_t ALLOC_T_POOL=5;
	global const alloc_t ALLOC_T_FALLBACK=6;
	global const alloc_t ALLOC_T_STORE=7;
	global const alloc_t ALLOC_T_TABLE=8;

	global const alloc_t ALLOC_T_LIB_END=ALLOC_T_TABLE;
	global const alloc_t ALLOC_T_BEGIN=ALLOC_T_LIB_END+1;

	template <msize... SizeArgs>
	struct allocator
	{
		alloc_t type;

		allocator() { type=ALLOC_T_NULL; }
		allocator(alloc_t allocType)
			: type(allocType) { }
	};

	template <msize... SizeArgs>
	void* alloc(allocator<SizeArgs...>* a,msize size);

	template <msize... SizeArgs>
	b32 free(allocator<SizeArgs...>* a,void* ptr,msize size);
	
	template <msize... SizeArgs>
	b32 clear(allocator<SizeArgs...>* a);

	template <msize... SizeArgs>
	b32 owns(const allocator<SizeArgs...>* a,const void* ptr,msize size);

	template <msize... SizeArgs>
	stack_state save_stack(allocator<SizeArgs...>* a);

	template <msize... SizeArgs>
	b32 restore_stack(allocator<SizeArgs...>* a,stack_state state);

	template <msize... SizeArgs>
	b32 is_stack_balanced(const allocator<SizeArgs...>* a);

	template <msize... SizeArgs>
	msize used_mem(const allocator<SizeArgs...>* a);

	template <msize... SizeArgs>
	msize available_mem(const allocator<SizeArgs...>* a);

	template <typename T,msize... SizeArgs>
	T* alloc(allocator<SizeArgs...>* a,u32 count);

	template <typename T,msize... SizeArgs>
	b32 free(allocator<SizeArgs...>* a,T* ptr,u32 count);

	template <typename T,msize... SizeArgs>
	b32 owns(const allocator<SizeArgs...>* a,const T* ptr,u32 count);
}

#define _DGGT_MEM_ALLOCATOR_H_
#endif
