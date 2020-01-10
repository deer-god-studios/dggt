#ifndef _DGGT_MEM_STACK_ALLOC_H_

#include "dggt_mem_alloc.h"

struct stack_state
{
	msize used;
};

template <>
struct allocator<alloc_t::STACK>
{
	blk<void> block;
	msize used;
	u32 savedCount;
	stack_state prevSaved;

	allocator();
	explicit allocator(blk<void>& block);
	allocator(void* ptr,msize size);

	blk<void> alloc(msize size);
	void clear();

	template <typename T>
	blk<T> alloc(u32 count);

	b32 owns(const blk<void>& block) const;
	
	template <typename T>
	b32 owns(const blk<T>& block) const;

	stack_state save_state();
	b32 restore_state(stack_state& state);

	b32 is_stack_balanced() const;

	msize available() const;
};

#include "dggt_mem_stack_alloc.inl"

#define _DGGT_MEM_STACK_ALLOC_H_
#endif
