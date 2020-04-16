#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	template <typename P,typename F>
	struct fallback_alloc:
		allocator<fallback_alloc<P,F>>
	{
		P& p;
		F& f;

		fallback_alloc(P& primary,F& fallback)
			:allocator<fallback_alloc<P,F>>(this),
			p(primary),f(fallback) { }
	};

	template <typename P,typename F>
	void* malloc(fallback_alloc<P,F>* a,msize size=0);
	
	template <typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,void* ptr,msize size=0);
	
	template <typename P,typename F>
	b32 clear(fallback_alloc<P,F>* a);
	
	template <typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,const void* ptr,msize size);

	template <typename P,typename F>
	stack_state save_stack(fallback_alloc<P,F>* a);

	template <typename P,typename F>
	b32 restore_stack(fallback_alloc<P,F>* a,stack_state state);
	
	template <typename P,typename F>
	b32 is_stack_balanced(const fallback_alloc<P,F>* a);
	
	template <typename P,typename F>
	msize get_used(const fallback_alloc<P,F>* a);
	
	template <typename P,typename F>
	msize get_available(const fallback_alloc<P,F>* a);

	template <typename P,typename F>
	msize get_capacity(const fallback_alloc<P,F>* a);
}

#include "dggt_mem_fallback_alloc.inl"

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
