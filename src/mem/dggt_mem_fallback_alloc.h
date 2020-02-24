#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	template <msize PrimaryArg,msize FallbackArg>
	struct fallback_alloc
	{
		allocator<> baseAlloc;
		allocator<PrimaryArg>* p;
		allocator<FallbackArg>* f;

		fallback_alloc();
		fallback_alloc(allocator<PrimaryArg>* primary,
				allocator<FallbackArg>* fallback);
	};

	template <msize PrimaryArg,msize FallbackArg>
	void* alloc(fallback_alloc<PrimaryArg,FallbackArg>* a,msize size);

	template <msize PrimaryArg,msize FallbackArg>
	b32 free(fallback_alloc<PrimaryArg,FallbackArg>* a,void* ptr,msize size);
	
	template <msize PrimaryArg,msize FallbackArg>
	b32 clear(fallback_alloc<PrimaryArg,FallbackArg>* a);

	template <msize PrimaryArg,msize FallbackArg>
	b32 owns(const fallback_alloc<PrimaryArg,FallbackArg>* a,
			const void* ptr,msize size);

	template <msize PrimaryArg,msize FallbackArg>
	stack_state save_stack(fallback_alloc<PrimaryArg,FallbackArg>* a);

	template <msize PrimaryArg,msize FallbackArg>
	b32 restore_stack(fallback_alloc<PrimaryArg,FallbackArg>* a,
			stack_state state);

	template <msize PrimaryArg,msize FallbackArg>
	b32 is_stack_balanced(const fallback_alloc<PrimaryArg,FallbackArg>* a);

	template <msize PrimaryArg,msize FallbackArg>
	msize used_mem(const fallback_alloc<PrimaryArg,FallbackArg>* a);

	template <msize PrimaryArg,msize FallbackArg>
	msize available_mem(const fallback_alloc<PrimaryArg,FallbackArg>* a);

	template <typename T,msize PrimaryArg,msize FallbackArg>
	T* alloc(fallback_alloc<PrimaryArg,FallbackArg>* a,u32 count);

	template <typename T,msize PrimaryArg,msize FallbackArg>
	b32 free(fallback_alloc<PrimaryArg,FallbackArg>* a,T* ptr,u32 count);

	template <typename T,msize PrimaryArg,msize FallbackArg>
	b32 owns(const fallback_alloc<PrimaryArg,FallbackArg>* a,
			const T* ptr,u32 count);
}

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
