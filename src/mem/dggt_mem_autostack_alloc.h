#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	template <u32 BUFFSIZE=0>
	struct allocator<ALLOC_T_AUTO_STACK,BUFFSIZE>
	{
		static const bool B=BUFFSIZE==0;
		typedef enable_or<B,stack_alloc,stack_alloc<BUFFSIZE>>::val_t
			alloc_t;

		static const u32 TYPE=ALLOC_T_AUTO_STACK;
		stack_state savedState;
		alloc_t* a;

		allocator() 
			:a((alloc_t*)0)
		{
			savedState=save_stack(a);
		}

		allocator(alloc_t* stackAlloc)
			:allocator(),a(stackAlloc) { }

		allocator(alloc_t& other)
			:allocator(&other) { }

		allocator<ALLOC_T_AUTO_STACK,BUFFSIZE>& operator=(allocator<ALLOC_T_AUTO_STACK,BUFFSIZE>& other)
		{
			a=other.a;
			savedState=save_stack(a);
			return *this;
		}

		~allocator()
		{
			restore_stack(a,savedState);
		}
	};

	typedef auto_stack_alloc allocator<ALLOC_T_AUTO_STACK>;

	template <u32 BUFFSIZE>
	using auto_stack_stalloc=allocator<ALLOC_T_AUTO_STACK,BUFFSIZE>;

	void* alloc(auto_stack_alloc* a,msize* size=0)
	{
		return alloc(a->a,size);
	}

	blkv alloc(auto_stack_alloc* a,msize size=4)
	{
		return alloc(a->a,size);
	}

	template <typename T>
	T* alloc(auto_stack_alloc* a,u32* count=0)
	{
		return alloc(a->a,count);
	}

	template <typename T>
	blk<T> alloc(auto_stack_alloc* a,u32 count=1)
	{
		return alloc(a->a,count);
	}

	b32 free(auto_stack_alloc* a,void* ptr,msize size)
	{
		return free(a->a,ptr,size);
	}

	b32 free(auto_stack_alloc* a,blkv block)
	{
		return free(a->a,block)
	}

	template <typename T>
	b32 free(auto_stack_alloc* a,T* ptr,u32 count)
	{
		return free(a->a,ptr,count);
	}

	template <typename T>
	b32 free(auto_stack_alloc* a,blk<T> block)
	{
		return free(a->a,block);
	}

	b32 clear(auto_stack_alloc* a)
	{
		return clear(a->a);
	}

	b32 owns(const auto_stack_alloc* a,const void* ptr,msize size)
	{
		return owns(a->a,ptr,size);
	}

	b32 owns(const auto_stack_alloc* a,const blkv block)
	{
		return owns(a->a,block);
	}

	template <typename T>
	b32 owns(const auto_stack_alloc* a,const T* ptr,u32 count)
	{
		return owns(a->a,ptr,count);
	}

	template <typename T>
	b32 owns(const auto_stack_alloc* a,const blk<T> block)
	{
		return owns(a->a,block);
	}

	msize available_mem(const auto_stack_alloc* a)
	{
		return available_mem(a->a);
	}
	
	msize used_mem(const auto_stack_alloc* a)
	{
		return used_mem(a->a);
	}

	stack_state save_stack(auto_stack_alloc* a)
	{
		return save_stack(a->a);
	}

	b32 restore_stack(auto_stack_alloc* a,stack_state state)
	{
		return restore_stack(a->a,state);
	}

	b32 is_stack_balanced(auto_stack_alloc* a)
	{
		return is_stack_balanced(a->a);
	}
}

#define _DGGT_MEM_AUTOSTACK_H_
#endif
