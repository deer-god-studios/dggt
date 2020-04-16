#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "dggt_mem_page.h"
#include "dggt_mem_defines.h"

namespace dggt
{
	typedef msize stack_state;
	static constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	template <typename A>
	struct allocator
	{
		using alloc_type=A;
		alloc_type* a;

		allocator(alloc_type* alloc) : a(alloc) { }
	};
	
	template <typename A>
	void* malloc(allocator<A>* a,msize size=0) { return 0; }
	
	template <typename A>
	b32 free(allocator<A>* a,void* ptr,msize size=0) { return false; }
	
	template <typename A>
	b32 clear(allocator<A>* a) { return false; }
	
	template <typename A>
	b32 owns(const allocator<A>* a,const void* ptr,msize size) { return false; }

	template <typename A>
	stack_state save_stack(const allocator<A>* a) { return SAVE_STACK_FAIL; }

	template <typename A>
	b32 restore_stack(allocator<A>* a,stack_state state) { return false; }
	
	template <typename A>
	b32 is_stack_balanced(const allocator<A>* a) { return true; }
	
	template <typename A>
	msize get_used(const allocator<A>* a) { return 0; }
	
	template <typename A>
	msize get_available(const allocator<A>* a) { return 0; }

	template <typename A>
	msize get_capacity(const allocator<A>* a) { return get_available(a); }

	template <typename A>
	void* get_buff_ptr(allocator<A>* a) { return 0; }

	template <typename A>
	const void* get_buff_ptr(const allocator<A>* a) { return 0; }

	template <typename T,typename A>
	T* malloc(allocator<A>* a,msize size=1)
	{
		return (T*)malloc(a->a,sizeof(T)*size);
	}
	template <typename T,typename A>
	page<T> malloc_page(allocator<A>* a,msize size)
	{
		return page<T>(malloc<T>(a->a,size),size);
	}

	template <typename A>
	vpage malloc_vpage(allocator<A>* a,msize size)
	{
		return vpage(malloc(a->a,size),size);
	}

	template <typename T,typename A>
	b32 free(allocator<A>* a,T* ptr,msize size=1)
	{
		return free(a->a,(void*)ptr,sizeof(T)*size);
	}

	template <typename A>
	b32 free(allocator<A>* a,vpage& pge)
	{
		return free(a->a,(void*)pge.ptr,pge.size);
	}

	template <typename T,typename A>
	b32 free(allocator<A>* a,page<T>& pge)
	{
		return free(a->a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
	
	template <typename T,typename A>
	b32 owns(const allocator<A>* a,const T* ptr,msize size)
	{
		return owns(a->a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,typename A>
	b32 owns(allocator<A>* a,page<T>& pge)
	{
		return owns(a->a,(void*)pge.ptr,sizeof(T)*pge.size);
	}

	template <typename A>
	b32 owns(allocator<A>* a,vpage& pge)
	{
		return owns(a->a,(void*)pge.ptr,pge.size);
	}
}

#define _DGGT_MEM_ALLOCATOR_H_
#endif
