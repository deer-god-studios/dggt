#ifndef _DGGT_MEM_STALLOC_H_

#include "dggt_mem_alloc.h"
#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	global const msize DEF_BUFFSIZE=KB(10);

	template <msize BUFFSIZE=DEF_BUFFSIZE,typename A=stack_alloc>
	struct stallocator
	{
		A a_;
		ubyte buff[BUFFSIZE];
		stallocator();
	};

	template <msize BUFFSIZE,typename A>
	void* alloc(stallocator<BUFFSIZE,A>& a,msize size=4)
	{
		return alloc(&a->a_,size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	T* alloc(stallocator<BUFFSIZE,A>& a,u32 count=1)
	{
		return alloc(&a->a_,count);
	}

	template <msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>& a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <typename T,msize BUFFSIZE,typename A>
	b32 free(stallocator<BUFFSIZE,A>& a,T* ptr,u32 count)
	{
		return free(&a->a_,ptr,count);
	}

	template <msize BUFFSIZE,typename A>
	b32 clear(stallocator<BUFFSIZE,A>& a)
	{
		return clear(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>& a,const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <typename T,msize BUFFSIZE,typename A>
	b32 owns(const stallocator<BUFFSIZE,A>& a,const T* ptr,u32 count)
	{
		return owns(&a->a_,ptr,count);
	}

	template <msize BUFFSIZE,typename A>
	stack_state save_stack(stallocator<BUFFSIZE,A>& a)
	{
		return save_stack(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	b32 restore_stack(stallocator<BUFFSIZE,A>& a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <msize BUFFSIZE,typename A>
	b32 is_stack_balanced(stallocator<BUFFSIZE,A>& a)
	{
		return is_stack_balanced(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	msize used_mem(stallocator<BUFFSIZE,A>& a)
	{
		return used_mem(&a->a_);
	}

	template <msize BUFFSIZE,typename A>
	msize available_mem(stallocator<BUFFSIZE,A>& a)
	{
		return available_mem(&a->a_);
	}
}

#define _DGGT_MEM_STALLOC_H_
#endif
