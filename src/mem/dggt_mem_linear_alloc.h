#ifndef _DGGT_MEM_LINEAR_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <>
	struct allocator<alloc_t::LINEAR>
	{
		static const alloc_t TYPE=alloc_t::LINEAR;
		blk<void> buff;
		msize used;

		allocator();
		allocator(blk<void> buffer);
		allocator(void* buffPtr,msize buffSize);

		blk<void> alloc(msize size=4);
		void* alloc(msize* size=0);
		template <typename T>
		blk<T> alloc(u32 count=1);
		template <typename T>
		T* alloc(u32* count=0);

		b32 free(void* ptr,msize size) { return 0; }
		b32 free(blk<void> block) { return 0; }
		template <typename T>
		b32 free(T* ptr,u32 count) { return 0; }
		template <typename T>
		b32 free(blk<T> block) { return 0; }

		b32 clear();

		msize available_mem() const;
		msize used_mem() const;

		b32 owns(const blk<void> block) const;
		b32 owns(const void* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;
	};

	template <u32 SIZE>
	struct allocator<alloc_t::LINEAR,SIZE>
	{
		static const alloc_t TYPE=alloc_t::LINEAR;
		static const u32 S=SIZE;
		ubyte buff[SIZE];
		allocator<alloc_t::LINEAR> a;

		allocator() { a=allocator<alloc_t::LINEAR>((void*)buff,SIZE); }

		blk<void> alloc(msize size=4) { return a.alloc(size); }
		void* alloc(msize* size=0) { return a.alloc(size); }
		template <typename T>
		blk<T> alloc(u32 count=1) { return a.alloc<T>(count); }
		template <typename T>
		T* alloc(u32* count=0) { return a.alloc<T>(count); }

		b32 free(void* ptr,msize size) { return a.free(ptr,size); }
		b32 free(blk<void> block) { return a.free(block); }
		template <typename T>
		b32 free(T* ptr,u32 count) { return a.free(ptr,count); }
		template <typename T>
		b32 free(blk<T> block) { return a.free(block); }

		b32 clear() { return a.clear(); }

		msize available_mem() const { return a.available_mem(); }
		msize used_mem() const { return a.used_mem(); }

		b32 owns(const blk<void> block) const { return a.owns(block); }
		b32 owns(const void* ptr) const { return a.owns(ptr); }
		template <typename T>
		b32 owns(const blk<T> block) const { return a.owns(block); }
		template <typename T>
		b32 owns(const T* ptr) const { return a.owns(ptr); }
	};
}

#include "dggt_mem_linear_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOC_H_
#endif
