#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "dggt_mem_page.h"
#include "dggt_mem_defines.h"

namespace dggt
{
	typedef msize stack_state;
	static constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	struct allocator;

	struct alloc_func_table
	{
		void* (*malloc)(allocator*,msize);                    // 1
		vpage (*malloc_vpage)(allocator*,msize);              // 2
		b32 (*free)(allocator*,void*,msize);                  // 3
		b32 (*free_vpage)(allocator*,vpage& pge);             // 4
		b32 (*clear)(allocator*);                             // 5
		b32 (*owns)(const allocator*,const void*,msize);      // 6
		b32 (*owns_vpage)(const allocator*,const vpage& pge); // 7
		stack_state (*save_stack)(allocator*);                // 8
		b32 (*restore_stack)(allocator*,stack_state);         // 9
		b32 (*is_stack_balanced)(const allocator*);           // 10
		msize (*get_used)(const allocator*);                  // 11
		msize (*get_available)(const allocator*);             // 12
		msize (*get_capacity)(const allocator*);              // 13
		vpage (*get_buff)(allocator*);                        // 14
		const vpage (*get_buff_const)(const allocator*);      // 15
		void* (*get_buff_ptr)(allocator*);                    // 16
		const void* (*get_buff_ptr_const)(const allocator*);  // 17
	};

	struct allocator
	{
		alloc_func_table* vtbl;

		allocator();
		allocator(alloc_func_table* vtbl);
	};

	namespace internal_
	{
		void* allocator_malloc(allocator* a,msize size);
		vpage allocator_malloc_vpage(allocator* a,msize size);
		b32 allocator_free(allocator* a,void* ptr,msize size);
		b32 allocator_free(allocator* a,vpage& pge);
		b32 allocator_clear(allocator* a);
		b32 allocator_owns(const allocator* a,const void* ptr,msize size);
		b32 allocator_owns(const allocator* a,const vpage& pge);
		stack_state allocator_save_stack(allocator* a);
		b32 allocator_restore_stack(allocator* a,stack_state state);
		b32 allocator_is_stack_balanced(const allocator* a);
		msize allocator_get_used(const allocator* a);
		msize allocator_get_available(const allocator* a);
		msize allocator_get_capacity(const allocator* a);
		vpage allocator_get_buff(allocator* a);
		const vpage allocator_get_buff(const allocator* a);
		void* allocator_get_buff_ptr(allocator* a);
		const void* allocator_get_buff_ptr(const allocator* a);
	}

	void* malloc(allocator* a,msize size);

	vpage malloc_vpage(allocator* a,msize size);

	b32 free(allocator* a,void* ptr,msize size);

	b32 free(allocator* a,vpage& pge);

	b32 clear(allocator* a);

	b32 owns(const allocator* a,const void* ptr,msize size);

	b32 owns(const allocator* a,const vpage& pge);

	stack_state save_stack(allocator* a);

	b32 restore_stack(allocator* a,stack_state state);

	b32 is_stack_balanced(const allocator* a);

	msize get_used(const allocator* a);

	msize get_available(const allocator* a);

	msize get_capacity(const allocator* a);

	vpage get_buff(allocator* a);

	const vpage get_buff(const allocator* a);

	void* get_buff_ptr(allocator* a);

	const void* get_buff_ptr(const allocator* a);

	template <typename T>
	T* malloc(allocator* a,msize size=1);

	template <typename T>
	page<T> malloc_page(allocator* a,msize size);

	template <typename T>
	b32 free(allocator* a,T* ptr,msize size=1);

	template <typename T>
	b32 free(allocator* a,page<T>& pge);
	
	template <typename T>
	b32 owns(const allocator* a,const T* ptr,msize size);

	template <typename T>
	b32 owns(const allocator* a,page<T>& pge);
}

#include "dggt_mem_allocator.inl"

#define _DGGT_MEM_ALLOCATOR_H_
#endif
