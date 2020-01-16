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

		allocator();
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

		b32 clear();

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(blk<T> block) const;

		msize available_mem() const;
		msize used_mem() const;

	};

	template <u32 SIZE>
	struct allocator<alloc_t::STACK,SIZE>
	{
		static const alloc_t TYPE=alloc_t::STACK;
		static const u32 S=SIZE;
		ubyte buff[SIZE];
		allocator<alloc_t::STACK> internalAlloc;

		allocator() { internalAlloc=allocator<alloc_t::STACK>((void*)buff,SIZE); }
		blk<void> alloc(msize size=4) { return internalAlloc.alloc(size); }
		void* alloc(msize* size=0) { return internalAlloc.alloc(size); }
		template <typename T>
		blk<T> alloc(u32 count=1) { return internalAlloc.alloc<T>(count); }
		template <typename T>
		T* alloc(u32* count=0) { return internalAlloc.alloc<T>(count); }
		b32 free(blk<void> block) { return internalAlloc.free(block); }
		b32 free(void* ptr,msize size) { return internalAlloc.free(ptr,size); }
		template <typename T>
		b32 free(blk<T> block) { return internalAlloc.free(block); }
		template <typename T>
		b32 free(T* ptr,u32 count) { return internalAlloc.free(ptr,count); }

		stack_state save_stack() { return internalAlloc.save_stack(); }
		b32 restore_stack(stack_state state) { return internalAlloc.restore_stack(state); }
		b32 is_stack_balanced() const { return internalAlloc.is_stack_balanced(); }

		b32 clear() { return internalAlloc.clear(); }

		b32 owns(const void* ptr) const { return internalAlloc.owns(ptr); }
		b32 owns(const blk<void> block) const { return internalAlloc.owns(block); }
		template <typename T>
		b32 owns(const T* ptr) const { return internalAlloc.owns(ptr); }
		template <typename T>
		b32 owns(blk<T> block) const { return internalAlloc.owns(block); }

		msize available_mem() const { return internalAlloc.available_mem(); }
		msize used_mem() const { return internalAlloc.used_mem(); }
	};
}

#include "dggt_mem_stack_alloc.inl"
#define _DGGT_MEM_STACK_ALLOC_H_
#endif
