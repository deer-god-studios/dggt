#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	struct autostack_alloc
	{
		stack_alloc* a;
		stack_state prevState;

		autostack_alloc();
//		autostack_alloc(void* ptr,msize size); TODO: this?
		autostack_alloc(const autostack_alloc& other);
		autostack_alloc(const stack_alloc& other);

		autostack_alloc& operator=(const autostack_alloc& rhs);
		autostack_alloc& operator=(const stack_alloc& rhs);
		~autostack_alloc();
	};

	void* malloc(autostack_alloc* a,msize size);

	b32 free(autostack_alloc* a,void* ptr,msize size);
	
	b32 clear(autostack_alloc* a);

	b32 owns(const autostack_alloc* a,const void* ptr,msize size);

	stack_state save_stack(autostack_alloc* a);

	b32 restore_stack(autostack_alloc* a,stack_state state);

	b32 is_stack_balanced(const autostack_alloc* a);

	msize used_mem(const autostack_alloc* a);

	msize available_mem(const autostack_alloc* a);

	template <typename T>
	T* malloc(autostack_alloc* a,msize size=1);

	template <typename T>
	b32 free(autostack_alloc* a,T* ptr,msize size=1);

	template <typename T>
	b32 owns(const autostack_alloc* a,const T* ptr,msize size=1);
}

#include "dggt_mem_autostack_alloc.inl"

#define _DGGT_MEM_AUTOSTACK_H_
#endif
