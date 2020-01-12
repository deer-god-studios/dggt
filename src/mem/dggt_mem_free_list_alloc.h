#ifndef _DGGT_MEM_FREE_LIST_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::FREE_LIST>
	{
		static const alloc_t TYPE=alloc_t::FREE_LIST;

		blk<void> buff;
		msize used;
		free_block* freeList;

		allocator(void* ptr,msize size);
		allocator(blk<void> buffer);

		void* alloc(msize* size);
		blk<void> alloc(msize size);
		template <typename T>
		T* alloc(u32* count);
		template <typename T>
		blk<T> alloc(u32 count);

		b32 free(void* ptr,msize size);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr,u32 count);
		template <typename T>
		b32 free(blk<T> block);

		void clear();

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;
		
		msize available_mem() const;
		msize used_mem() const;
		private:
		allocator();
	};
}

#include "dggt_mem_free_list_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
