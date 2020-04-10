#ifndef _DGGT_MEM_STALLOCATOR_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	template <msize BUFFSIZE,typename A=stack_alloc>
	struct stallocator
	{
		A a_;
		ubyte buff[BUFFSIZE];

		stallocator() { a_=A((void*)buff,BUFFSIZE); }
	};

	template <msize BuffSize,typename A>
	void* malloc(stallocator<BuffSize,A>* a,msize size)
	{
		return malloc(&a->a_,size);
	}

	template <msize BuffSize,typename A>
	b32 free(stallocator<BuffSize,A>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <msize BuffSize,typename A>
	b32 clear(stallocator<BuffSize,A>* a)
	{
		return clear(&a->a_);
	}

	template <msize BuffSize,typename A>
	b32 owns(const stallocator<BuffSize,A>* a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <msize BuffSize,typename A>
	stack_state save_stack(stallocator<BuffSize,A>* a)
	{
		return save_stack(&a->a_);
	}

	template <msize BuffSize,typename A>
	b32 restore_stack(stallocator<BuffSize,A>* a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <msize BuffSize,typename A>
	b32 is_stack_balanced(const stallocator<BuffSize,A>* a)
	{
		return is_stack_balanced(&a->a_);
	}

	template <msize BuffSize,typename A>
	msize used_mem(const stallocator<BuffSize,A>* a)
	{
		return used_mem(&a->a_);
	}

	template <msize BuffSize,typename A>
	msize available_mem(const stallocator<BuffSize,A>* a)
	{
		return available_mem(&a->a_);
	}

	template <typename T,msize BuffSize,typename A>
	T* malloc(stallocator<BuffSize,A>* a,msize size=1)
	{
		return malloc<T>(&a->a_,size);
	}

	template <typename T,msize BuffSize,typename A>
	b32 free(stallocator<BuffSize,A>* a,T* ptr,msize size=1)
	{
		return free(&a->a_,ptr,size);
	}

	template <typename T,msize BuffSize,typename A>
	b32 owns(const stallocator<BuffSize,A>* a,const T* ptr,msize size=1)
	{
		return owns(&a->a_,ptr,size);
	}
}

#define _DGGT_MEM_STALLOCATOR_H_
#endif
