#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::STACK>
	{
		static const alloc_t TYPE=alloc_t::STACK;
		blk<void> buff;
		msize used;
		u32 stateCount;
		stack_state prevState;

		allocator(blk<void> buffer);
		allocator(void* buffPtr,msize buffSize);

		blk<void> alloc(msize size=4);
		void* alloc(msize* size=0);
		template <typename T>
		blk<T> alloc(u32 count=1);
		template <typename T>
		T* alloc(u32* count=0);
		b32 free(blk<void> block);
		b32 free(void* ptr,msize size);
		template <typename T>
		b32 free(blk<T> block);
		template <typename T>
		b32 free(T* ptr,u32 count);

		stack_state save_stack();
		b32 restore_stack(stack_state state);
		b32 is_stack_balanced() const;

		void clear();

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(blk<T> block) const;

		msize available_mem() const;
		msize used_mem() const;

		allocator();
	};
}

#include "dggt_mem_stack_alloc.inl"
#define _DGGT_MEM_STACK_ALLOC_H_
#endif
