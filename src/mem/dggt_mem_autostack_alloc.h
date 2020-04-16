#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	struct autostack_alloc;
	stack_state save_stack(autostack_alloc* a);

	struct autostack_alloc
		:allocator<autostack_alloc>
	{
		stack_alloc& a;
		stack_state prevState;

		autostack_alloc(autostack_alloc& other)
			:allocator<autostack_alloc>(this),
			a(other.a),prevState(dggt::save_stack(&other.a)) { }
		autostack_alloc(stack_alloc& other)
			:allocator<autostack_alloc>(this),
			a(other),prevState(dggt::save_stack(&other)) { }

		autostack_alloc& operator=(const autostack_alloc& rhs)
		{
			if (this!=&rhs)
			{
				a=rhs.a;
				prevState=dggt::save_stack(&rhs);
			}
			return *this;
		}
		autostack_alloc& operator=(const stack_alloc& rhs)
		{
			a=rhs;
			prevState=dggt::save_stack(&rhs);
			return *this;
		}
		~autostack_alloc() { restore_stack(&a,prevState); }
	};

	void* malloc(autostack_alloc* a,msize size) { return malloc(&a->a,size); }
	
	b32 free(autostack_alloc* a,void* ptr,msize size) { return free(&a->a,ptr,size); }
	
	b32 clear(autostack_alloc* a) { return clear(&a->a); }
	
	b32 owns(const autostack_alloc* a,const void* ptr,msize size) { return owns(&a->a,ptr,size); }

	stack_state save_stack(autostack_alloc* a) { return save_stack(&a->a); }

	b32 restore_stack(autostack_alloc* a,stack_state state) { return restore_stack(&a->a,state); }
	
	b32 is_stack_balanced(const autostack_alloc* a) { return is_stack_balanced(&a->a); }
	
	msize get_used(const autostack_alloc* a) { return get_used(&a->a); }
	
	msize get_available(const autostack_alloc* a) { return get_available(&a->a); }

	msize get_capacity(const autostack_alloc* a) { return get_capacity(&a->a); }

	void* get_buff_ptr(autostack_alloc* a) { return get_buff_ptr(&a->a); }

	const void* get_buff_ptr(const autostack_alloc* a) { return get_buff_ptr(&a->a); }
}

#define _DGGT_MEM_AUTOSTACK_H_
#endif
