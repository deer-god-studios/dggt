#ifndef _DGGT_MEM_POOL_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::POOL>
	{
		static const alloc_t TYPE=alloc_t::POOL;

		blk<void> buff;
		msize used;
		msize blockSize;
		u32 blockCount;
		u32 blocksUsed;
		pool_block* pool;

		allocator();
		allocator(void* ptr,msize size,msize blockSize);
		allocator(blk<void> buffer,msize blockSize);

		template <typename T>
		blk<T> alloc();
		blk<void> alloc();

		b32 free(void* ptr);
		b32 free(blk<void> block);
		template <typename T>
		b32 free(T* ptr);
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
		u32 available_blocks() const;
		u32 used_blocks() const;

	};

	template <u32 SIZE>
	struct allocator<alloc_t::POOL,SIZE>
	{
		static const alloc_t TYPE=alloc_t::POOL;
		static const u32 S=SIZE;
		ubyte buff[SIZE];
		allocator<alloc_t::POOL> internalAlloc;

		allocator() { internalAlloc=allocator<alloc_t::POOL>(); }
		allocator(msize blockSize) : allocator() { internalAlloc=allocator<alloc_t::POOL>((void*)buff,SIZE,blockSize); }

		template <typename T>
		blk<T> alloc() { return internalAlloc.alloc<T>(); }
		blk<void> alloc() { return internalAlloc.alloc(); }

		b32 free(void* ptr) { return internalAlloc.free(ptr); }
		b32 free(blk<void> block) { return internalAlloc.free(block); }
		template <typename T>
		b32 free(T* ptr) { return internalAlloc.free<T>(ptr); }
		template <typename T>
		b32 free(blk<T> block) { return internalAlloc.free<T>(block); }

		void clear() { internalAlloc.clear(); }

		b32 owns(const void* ptr) const { return internalAlloc.owns(ptr); }
		b32 owns(const blk<void> block) const { return internalAlloc.owns(block); }
		template <typename T>
		b32 owns(const T* ptr) const { return internalAlloc.owns(ptr); }
		template <typename T>
		b32 owns(const blk<T> block) const { return internalAlloc.owns(block); }

		msize available_mem() const { return internalAlloc.available_mem(); }
		msize used_mem() const { return internalAlloc.used_mem(); }
		u32 available_blocks() const { return internalAlloc.available_blocks(); }
		u32 used_blocks() const { return internalAlloc.used_blocks(); }
	};
}
#include "dggt_mem_pool_alloc.inl"

#define _DGGT_MEM_POOL_ALLOC_H_
#endif
