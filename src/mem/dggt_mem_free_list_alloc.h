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

		allocator();
		allocator(void* ptr,msize size);
		allocator(blk<void> buffer);

		void* alloc(msize* size=0);
		blk<void> alloc(msize size=4);
		template <typename T>
		T* alloc(u32* count=0);
		template <typename T>
		blk<T> alloc(u32 count=1);

		b32 free(void* ptr,msize size);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr,u32 count);
		template <typename T>
		b32 free(blk<T> block);

		b32 clear();

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;
		
		msize available_mem() const;
		msize used_mem() const;
	};

	template <u32 SIZE>
	struct allocator<alloc_t::FREE_LIST,SIZE>
	{
		static const alloc_t TYPE=alloc_t::FREE_LIST;
		static const u32 S=SIZE;
		ubyte buff[SIZE];
		allocator<alloc_t::FREE_LIST> internalAlloc;

		allocator() { internalAlloc=allocator<alloc_t::FREE_LIST>((void*)buff,SIZE); }

		void* alloc(msize* size=0) { return internalAlloc.alloc(size); }
		blk<void> alloc(msize size=4) { return internalAlloc.alloc(size); }
		template <typename T>
		T* alloc(u32* count=0) { return internalAlloc.alloc<T>(count); }
		template <typename T>
		blk<T> alloc(u32 count=1) { return internalAlloc.alloc<T>(count); }

		b32 free(void* ptr,msize size) { return internalAlloc.free(ptr,size); }
		b32 free(blk<void> block) { return internalAlloc.free(block); }
		template <typename T>
		b32 free(T* ptr,u32 count) { return internalAlloc.free(ptr,count); }
		template <typename T>
		b32 free(blk<T> block) { return internalAlloc.free(block); }

		b32 clear() { return internalAlloc.clear(); }

		b32 owns(const void* ptr) const { return internalAlloc.owns(ptr); }
		b32 owns(const blk<void> block) const { return internalAlloc.owns(block); }
		template <typename T>
		b32 owns(const T* ptr) const { return internalAlloc.owns(ptr); }
		template <typename T>
		b32 owns(const blk<T> block) const { return internalAlloc.owns(block); }
		
		msize available_mem() const { return internalAlloc.available_mem(); }
		msize used_mem() const { return internalAlloc.used_mem(); }
	};
}

#include "dggt_mem_free_list_alloc.inl"

#define _DGGT_MEM_FREE_LIST_ALLOC_H_
#endif
