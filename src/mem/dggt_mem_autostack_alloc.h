#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	struct autostack_alloc
	{
		allocator baseAlloc;
		stack_alloc* stackAlloc;
		stack_state savedState;

		autostack_alloc()
			: baseAlloc(allocator(ALLOC_T_AUTOSTACK)),
			stackAlloc((stack_alloc*)0),
			savedState(0) { }

		autostack_alloc(stack_alloc* stackAllocator)
			: autostack_alloc(),
			stackAlloc(stackAllocator),
			savedState(save_stack(stackAlloc)) { }

		autostack_alloc(stack_alloc& other)
			: autostack_alloc(&other) { }

		template <msize BUFFSIZE>
		autostack_alloc(stallocator<BUFFSIZE>* stackStallocator)
			: autostack_alloc(stackStallocator->a_) { }

		template <msize BUFFSIZE>
		autostack_alloc(stallocator<BUFFSIZE>& stackStallocator)
			: autostack_alloc(&stackStallocator) { }

		autostack_alloc& operator=(autostack_alloc& other)
		{
			if (this!=&other)
			{
				stackAlloc=other.stackAlloc;
				savedState=save_stack(stackAlloc);
			}
			return *this;
		}

		autostack_alloc& operator=(stack_alloc& other)
		{
			stackAlloc=&other;
			savedState=save_stack(stackAlloc);
			return *this;
		}

		~allocator()
		{
			savedState=restore_stack(stackAlloc);
		}
	};

	void* alloc(auto_stack_alloc* a,msize size=4)
	{
		return alloc(a->stackAlloc,size);
	}

	template <typename T>
	T* alloc(auto_stack_alloc* a,u32 count=1)
	{
		return alloc(a->stackAlloc,count);
	}

	b32 free(auto_stack_alloc* a,void* ptr,msize size)
	{
		return free(a->stackAlloc,ptr,size);
	}

	template <typename T>
	b32 free(auto_stack_alloc* a,T* ptr,u32 count)
	{
		return free(a->stackAlloc,ptr,count);
	}

	b32 clear(auto_stack_alloc* a)
	{
		return clear(a->stackAlloc);
	}

	b32 owns(const auto_stack_alloc* a,const void* ptr,msize size)
	{
		return owns(a->stackAlloc,ptr,size);
	}

	template <typename T>
	b32 owns(const auto_stack_alloc* a,const T* ptr,u32 count)
	{
		return owns(a->stackAlloc,ptr,count);
	}

	msize available_mem(const auto_stack_alloc* a)
	{
		return available_mem(a->stackAlloc);
	}
	
	msize used_mem(const auto_stack_alloc* a)
	{
		return used_mem(a->stackAlloc);
	}

	stack_state save_stack(auto_stack_alloc* a)
	{
		return save_stack(a->stackAlloc);
	}

	b32 restore_stack(auto_stack_alloc* a,stack_state state)
	{
		return restore_stack(a->stackAlloc,state);
	}

	b32 is_stack_balanced(auto_stack_alloc* a)
	{
		return is_stack_balanced(a->stackAlloc);
	}
}

#define _DGGT_MEM_AUTOSTACK_H_
#endif
