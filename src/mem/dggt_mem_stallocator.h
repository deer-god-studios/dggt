#ifndef _DGGT_MEM_STALLOCATOR_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	template <msize BUFFSIZE,typename A=stack_alloc>
	struct stallocator:
		allocator
	{
		A a_;
		ubyte buff[BUFFSIZE];

		stallocator():allocator(0) { a_=A((void*)buff,BUFFSIZE); }
	};

	template <msize BUFFSIZE,typename A>
	void* malloc(stallocator<BUFFSIZE,A>* a,msize size)
	{
		return malloc(&a->a_,size);
	}

	template <msize BUFFSIZE,typename A>
	vpage malloc_vpage(stallocator<BUFFSIZE,A>* a,msize size)
	{
		return malloc_vpage(&a->a_,size);
	}

	template <msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}

	template <msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>* a,vpage& pge)
	{
		return free(&a->a_,pge);
	}

	template <msize BUFFSIZE,typename A>
	b32 clear(stallocator<BUFFSIZE,A>* a)
	{
		return clear(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>* a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>* a,const vpage& pge)
	{
		return owns(&a->a_,pge);
	}

	template <msize BUFFSIZE,typename A>
	stack_state save_stack(stallocator<BUFFSIZE,A>* a)
	{
		return save_stack(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	b32 restore_stack(stallocator<BUFFSIZE,A>* a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <msize BUFFSIZE,typename A>
	b32 is_stack_balanced(const stallocator<BUFFSIZE,A>* a)
	{
		return is_stack_balanced(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	msize get_used(const stallocator<BUFFSIZE,A>* a)
	{
		return get_used(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	msize get_available(const stallocator<BUFFSIZE,A>* a)
	{
		return get_available(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	msize get_capacity(const stallocator<BUFFSIZE,A>* a)
	{
		return get_capacity(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	vpage get_buff(stallocator<BUFFSIZE,A>* a)
	{
		return get_buff(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	const vpage get_buff(const stallocator<BUFFSIZE,A>* a)
	{
		return get_buff(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	void* get_buff_ptr(stallocator<BUFFSIZE,A>* a)
	{
		return get_buff_ptr(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	const void* get_buff_ptr(const stallocator<BUFFSIZE,A>* a)
	{
		return get_buff_ptr(&a->a_);
	}

	template <typename T,msize BUFFSIZE,typename A>
	T* malloc(stallocator<BUFFSIZE,A>* a,msize size=1)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	page<T> malloc_page(stallocator<BUFFSIZE,A>* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>* a,T* ptr,msize size=1)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>* a,page<T>& pge)
	{
		return free<T>(a,pge.ptr,pge.size);
	}
	
	template <typename T,msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>* a,page<T>& pge)
	{
		return owns<T>(a,pge.ptr,pge.size);
	}
}

#define _DGGT_MEM_STALLOCATOR_H_
#endif
