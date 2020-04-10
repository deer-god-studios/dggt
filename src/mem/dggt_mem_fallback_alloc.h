#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	template <typename P,typename F>
	struct fallback_alloc
	{
		P* p;
		F* f;

		fallback_alloc();
		fallback_alloc(P* primary,F* fallback);
	};

	template <typename P,typename F>
	void* malloc(fallback_alloc<P,F>* a,msize size);

	template <typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,void* ptr,msize size);
	
	template <typename P,typename F>
	b32 clear(fallback_alloc<P,F>* a);

	template <typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,
			const void* ptr,msize size);

	template <typename P,typename F>
	stack_state save_stack(fallback_alloc<P,F>* a);

	template <typename P,typename F>
	b32 restore_stack(fallback_alloc<P,F>* a,
			stack_state state);

	template <typename P,typename F>
	b32 is_stack_balanced(const fallback_alloc<P,F>* a);

	template <typename P,typename F>
	msize used_mem(const fallback_alloc<P,F>* a);

	template <typename P,typename F>
	msize available_mem(const fallback_alloc<P,F>* a);

	template <typename T,typename P,typename F>
	T* malloc(fallback_alloc<P,F>* a,msize size=1);

	template <typename T,typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,T* ptr,msize size=1);

	template <typename T,typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,
			const T* ptr,msize size=1);

 
}

#include "dggt_mem_fallback_alloc.inl"

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
