#include "dggt_mem_allocator.h"

namespace dggt
{
	namespace internal_
	{
		void* allocator_malloc(allocator* a,msize size) { return 0; }

		vpage allocator_malloc_vpage(allocator* a,msize size) { return vpage(); }

		b32 allocator_free(allocator* a,void* ptr,msize size) { return false; }

		b32 allocator_free(allocator* a,vpage& pge) { return false; }

		b32 allocator_clear(allocator* a) { return false; }

		b32 allocator_owns(const allocator* a,const void* ptr,msize size) { return false; }

		b32 allocator_owns(const allocator* a,const vpage& pge) { return false; }

		stack_state allocator_save_stack(allocator* a) { return SAVE_STACK_FAIL; }

		b32 allocator_restore_stack(allocator* a,stack_state state) { return false; }

		b32 allocator_is_stack_balanced(const allocator* a) { return true; }

		msize allocator_get_used(const allocator* a) { return 0; }

		msize allocator_get_available(const allocator* a) { return 0; }

		msize allocator_get_capacity(const allocator* a) { return get_available(a); }

		vpage allocator_get_buff(allocator* a) { return vpage(); }

		const vpage allocator_get_buff(const allocator* a) { return vpage(); }

		void* allocator_get_buff_ptr(allocator* a) { return 0; }

		const void* allocator_get_buff_ptr(const allocator* a) { return 0; }

		global alloc_func_table ALLOCATOR_TABLE=
		{
			allocator_malloc,
			allocator_malloc_vpage,
			allocator_free,
			allocator_free,
			allocator_clear,
			allocator_owns,
			allocator_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			allocator_get_used,
			allocator_get_available,
			allocator_get_capacity,
			allocator_get_buff,
			allocator_get_buff,
			allocator_get_buff_ptr,
			allocator_get_buff_ptr
		};
	}

	allocator::allocator(alloc_func_table* tbl)
		:vtbl(tbl) { }

	allocator::allocator()
		:allocator(&internal_::ALLOCATOR_TABLE) { }

	void* malloc(allocator* a,msize size)
	{
		return a?a->vtbl->malloc(a,size):0;
	}

	vpage malloc_vpage(allocator* a,msize size)
	{
		return a?a->vtbl->malloc_vpage(a,size):vpage();
	}

	b32 free(allocator* a,void* ptr,msize size)
	{
		return a?a->vtbl->free(a,ptr,size):false;
	}

	b32 free(allocator* a,vpage& pge)
	{
		return a?a->vtbl->free_vpage(a,pge):false;
	}

	b32 clear(allocator* a)
	{
		return a?a->vtbl->clear(a):false;
	}

	b32 owns(const allocator* a,const void* ptr,msize size)
	{
		return a?a->vtbl->owns(a,ptr,size):false;
	}

	b32 owns(const allocator* a,const vpage& pge)
	{
		return a?a->vtbl->owns_vpage(a,pge):false;
	}

	stack_state save_stack(allocator* a)
	{
		return a?a->vtbl->save_stack(a):SAVE_STACK_FAIL;
	}

	b32 restore_stack(allocator* a,stack_state state)
	{
		return a?a->vtbl->restore_stack(a,state):false;
	}

	b32 is_stack_balanced(const allocator* a)
	{
		return a?a->vtbl->is_stack_balanced(a):true;
	}

	msize get_used(const allocator* a)
	{
		return a?a->vtbl->get_used(a):0;
	}

	msize get_available(const allocator* a)
	{
		return a?a->vtbl->get_available(a):0;
	}

	msize get_capacity(const allocator* a)
	{
		return a?a->vtbl->get_capacity(a):0;
	}

	vpage get_buff(allocator* a)
	{
		return a?a->vtbl->get_buff(a):vpage();
	}

	const vpage get_buff(const allocator* a)
	{
		return a?a->vtbl->get_buff_const(a):vpage();
	}

	void* get_buff_ptr(allocator* a)
	{
		return a?a->vtbl->get_buff_ptr(a):0;
	}

	const void* get_buff_ptr(const allocator* a)
	{
		return a?a->vtbl->get_buff_ptr_const(a):0;
	}
}
