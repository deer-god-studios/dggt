#ifndef _DGGT_MEM_AUTOSTACK_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::AUTO_STACK>
	{
		static const alloc_t TYPE=alloc_t::AUTO_STACK;
		stack_state savedState;
		allocator<alloc_t::STACK>* a;

		allocator() { savedState=0;a=0; }

		allocator(allocator<alloc_t::STACK>* stackAlloc)
		{
			a=stackAlloc;
			savedState=a->save_stack();
		}

		allocator(allocator<alloc_t::AUTO_STACK>& other)
		{
			a=other.a;
			savedState=a->save_stack();
		}

		blk<void> alloc(msize size=4)
		{
			return a?a->alloc(size):blk<void>();
		}

		void* alloc(msize* size=0)
		{
			return a?a->alloc(size):0;
		}
		template <typename T>
		blk<T> alloc(u32 count=1)
		{
			return a?a->alloc(count):blk<T>();
		}
		template <typename T>
		T* alloc(u32* count=0)
		{
			return a?a->alloc<T>(count):0;
		}

		b32 free(blk<void> block)
		{
			return a?a->free(block):0;
		}
		b32 free(void* ptr,msize size)
		{
			return a?a->free(ptr,size):0;
		}
		template <typename T>
		b32 free(blk<T> block)
		{
			return a?a->free(block):0;
		}
		template <typename T>
		b32 free(T* ptr,u32 count)
		{
			return a?a->free(ptr,count):0;
		}

		stack_state save_stack()
		{
			return a?a->save_stack():0;
		}
		b32 restore_stack(stack_state state)
		{
			return a?a->restore_stack(state):0;
		}
		b32 is_stack_balanced() const
		{
			return a?a->is_stack_balanced():1;
		}

		b32 clear()
		{
			return a?a->clear():0;
		}

		b32 owns(const void* ptr) const
		{
			return a?a->owns(ptr):0;
		}
		b32 owns(const blk<void> block) const
		{
			return a?a->owns(block):0;
		}
		template <typename T>
		b32 owns(const T* ptr) const
		{
			return a?a->owns(ptr):0;
		}
		template <typename T>
		b32 owns(blk<T> block) const
		{
			return a?a->owns(block):0;
		}

		msize available_mem() const
		{
			return a?a->available_mem():0;
		}
		msize used_mem() const
		{
			return a?a->used_mem():0;
		}

		allocator<alloc_t::AUTO_STACK>& operator=(
				allocator<alloc_t::AUTO_STACK>& rhs)
		{
			if (this!=&rhs)
			{
				a=rhs.a;
				savedState=a->save_stack();
			}
			return *this;
		}
		allocator<alloc_t::AUTO_STACK>& operator=(
				allocator<alloc_t::STACK>& rhs)
		{

			a=&rhs;
			savedState=a->save_stack();
			return *this;
		}

		~allocator()
		{
			if (a)
			{
				a->restore_stack(savedState);
			}
		}
	};

	template <u32 SIZE>
	struct allocator<alloc_t::AUTO_STACK,SIZE>
	{
		static const alloc_t TYPE=alloc_t::AUTO_STACK;
		static const u32 S=SIZE;
		stack_state savedState;
		allocator<alloc_t::STACK,SIZE>* a;

		allocator() { savedState=0;a=0; }

		allocator(allocator<alloc_t::STACK,SIZE>* stackAlloc)
		{
			a=stackAlloc;
			savedState=a->save_stack();
		}

		allocator(allocator<alloc_t::AUTO_STACK,SIZE>& other)
		{
			a=other.a;
			savedState=a->save_stack();
		}

		blk<void> alloc(msize size=4)
		{
			return a?a->alloc(size):blk<void>();
		}

		void* alloc(msize* size=0)
		{
			return a?a->alloc(size):0;
		}
		template <typename T>
		blk<T> alloc(u32 count=1)
		{
			return a?a->alloc(count):blk<T>();
		}
		template <typename T>
		T* alloc(u32* count=0)
		{
			return a?a->alloc(count):0;
		}

		b32 free(blk<void> block)
		{
			return a?a->free(block):0;
		}
		b32 free(void* ptr,msize size)
		{
			return a?a->free(ptr,size):0;
		}
		template <typename T>
		b32 free(blk<T> block)
		{
			return a?a->free(block):0;
		}
		template <typename T>
		b32 free(T* ptr,u32 count)
		{
			return a?a->free(ptr,count):0;
		}

		stack_state save_stack()
		{
			return a?a->save_stack():0;
		}
		b32 restore_stack(stack_state state)
		{
			return a?a->restore_stack(state):0;
		}
		b32 is_stack_balanced() const
		{
			return a?a->is_stack_balanced():1;
		}

		b32 clear()
		{
			return a?a->clear():0;
		}

		b32 owns(const void* ptr) const
		{
			return a?a->owns(ptr):0;
		}
		b32 owns(const blk<void> block) const
		{
			return a?a->owns(block):0;
		}
		template <typename T>
		b32 owns(const T* ptr) const
		{
			return a?a->owns(ptr):0;
		}
		template <typename T>
		b32 owns(blk<T> block) const
		{
			return a?a->owns(block):0;
		}

		msize available_mem() const
		{
			return a?a->available_mem():0;
		}
		msize used_mem() const
		{
			return a?a->used_mem():0;
		}

		allocator<alloc_t::AUTO_STACK,SIZE>& operator=(
				allocator<alloc_t::AUTO_STACK,SIZE>& rhs)
		{
			if (this!=&rhs)
			{
				a=rhs.a;
				savedState=a->save_stack();
			}
			return *this;
		}
		allocator<alloc_t::AUTO_STACK,SIZE>& operator=(
				allocator<alloc_t::STACK,SIZE>& rhs)
		{

			a=&rhs;
			savedState=a->save_stack();
			return *this;
		}


		~allocator()
		{
			if (a)
			{
				a->restore_stack(savedState);
			}
		}
	};
}

#define _DGGT_MEM_AUTOSTACK_H_
#endif
