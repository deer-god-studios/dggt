#ifndef _DGGT_MEM_STORE_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::STORE>
	{
		static const alloc_t TYPE=alloc_t::STORE;
		msize blockSize;
		store_block* head;
		u32 blockCount;

		allocator();
		allocator(msize blockSize);

		blk<void> alloc();
		template <typename T>
		blk<T> alloc();

		b32 free(void* ptr,msize size=0);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr,u32 count=0);
		template <typename T>
		b32 free(blk<T> block);

		b32 owns(const void* ptr) const;
		b32 owns(const blk<void> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;

		msize available_mem() const;
		msize used_mem() const;
		u32 available_blocks() const;
		u32 used_blocks() const;

	};

	template <u32 BLOCKSIZE>
	struct allocator<alloc_t::STORE,BLOCKSIZE>
	{
		static const alloc_t TYPE=alloc_t::STORE;
		static const u32 S=BLOCKSIZE;
		allocator<alloc_t::STORE> a;

		allocator() { a=allocator<alloc_t::STORE>(BLOCKSIZE); }

		blk<void> alloc() { return a.alloc(); }
		template <typename T>
		blk<T> alloc() { return a.alloc<T>(); }

		b32 free(void* ptr,msize size=BLOCKSIZE) { return a.free(ptr,size); }
		b32 free(blk<void> block) { return a.free(block); }
		template <typename T>
		b32 free(T* ptr,u32 count=1) { return a.free(ptr,1); }
		template <typename T>
		b32 free(blk<T> block) { return a.free(block); }

		b32 owns(const void* ptr) const { return a.owns(ptr); }
		b32 owns(const blk<void> block) const { return a.owns(block); }
		template <typename T>
		b32 owns(const T* ptr) const { return a.owns(ptr); }
		template <typename T>
		b32 owns(const blk<T> block) const { return a.owns(block); }

		msize available_mem() const { return a.available_mem(); }
		msize used_mem() const { return a.used_mem(); }
		u32 available_blocks() const { return a.available_blocks(); }
		u32 used_blocks() const { return a.used_blocks(); }
	};
}
#include "dggt_mem_store_alloc.inl"

#define _DGGT_MEM_STORE_ALLOC_H_
#endif
