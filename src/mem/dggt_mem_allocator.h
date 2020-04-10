#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "defines/dggt_defines.h"
#include "types/dggt_types.h"
#include "dggt_mem_defines.h"

namespace dggt
{
	template <typename T>
	struct page;

	struct mblock
	{
		mblock* next;
	};

	struct smblock
	{
		msize size;
		smblock* next;
	};

	typedef msize stack_state;
	static constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	template <typename A>
	void* malloc(A* a,msize size);

	template <typename A>
	b32 free(A* a,void* ptr,msize size);
	
	template <typename A>
	b32 clear(A* a);

	template <typename A>
	b32 owns(const A* a,const void* ptr,msize size);

	template <typename A>
	stack_state save_stack(A* a);

	template <typename A>
	b32 restore_stack(A* a,stack_state state);

	template <typename A>
	b32 is_stack_balanced(const A* a);

	template <typename A>
	msize used_mem(const A* a);

	template <typename A>
	msize available_mem(const A* a);

	template <typename T,typename A>
	T* malloc(A* a,msize size);

	template <typename T,typename A>
	b32 free(A* a,T* ptr,msize size);

	template <typename T,typename A>
	b32 owns(const A* a,const T* ptr,msize size);

	template <typename T,typename A>
	page<T> malloc_page(A* a,msize size);
}

#define _DGGT_MEM_ALLOCATOR_H_
#endif
