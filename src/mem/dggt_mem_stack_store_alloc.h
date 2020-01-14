#ifndef _DGGT_MEM_STACK_STORE_ALLOC_H_

#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_store_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::STACK_STORE>
	{
		static const alloc_t TYPE=alloc_t::STACK_STORE;
		allocator<alloc_t::STORE>* store;
		allocator<alloc_t::STACK>* stk;

		allocator(allocator<alloc_t::STACK>* stk,
				allocator<alloc_t::STORE>* store);

		blk<void> alloc(msize size=4);
		void* alloc(msize* size=0);
		template <typename T>
		blk<T> alloc(u32 count=1);
		template <typename T>
		T* alloc(u32* count=0);

		b32 free(void* ptr,msize size=4);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr,u32 count=1);
		template <typename T>
		b32 free(blk<T> block);

		void clear();

		msize available_mem() const;
		msize used_mem() const;

		b32 owns(const blk<void> block) const;
		b32 owns(const void* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;

		stack_state save_stack();
		b32 restore_stack(stack_state state);
		b32 is_stack_balanced() const;

		allocator();
	};

}

#include "dggt_mem_stack_store_alloc.inl"

#define _DGGT_MEM_STACK_STORE_ALLOC_H_
#endif
