#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	// NOTE: here the size arg is being used for the primary allocator type.
	template <u32 P,u32 F>
	struct allocator<alloc_t::FALLBACK,P,F>
	{
		static const alloc_t TYPE=alloc_t::FALLBACK;
		typedef allocator<(alloc_t)P> palloc;
		typedef allocator<(alloc_t)F> falloc;

		palloc* p;
		falloc* f;

		allocator() : p(0),f(0) { }
		allocator(palloc* primaryAlloc,
				falloc* fallbackAlloc) 
			: p(primaryAlloc),f(fallbackAlloc) { }

		void* alloc(msize* size=0);
		blk<void> alloc(msize size=4);
		template <typename T>
		T* alloc(u32* count=0);
		template <typename T>
		blk<T> alloc(u32 count=1);

		b32 free(void* ptr,msize size=4);
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

	template <u32 P,u32 SIZE,u32 F>
	struct allocator<alloc_t::FALLBACK,P,SIZE,F>
	{
		static const alloc_t TYPE=alloc_t::FALLBACK;
		static const u32 S=SIZE;
		typedef allocator<(alloc_t)P,SIZE> palloc;
		typedef allocator<(alloc_t)F> falloc;

		palloc* p;
		falloc* f;

		allocator() : p(0),f(0) { }
		allocator(palloc* primaryAlloc,
				falloc* fallbackAlloc) 
			: p(primaryAlloc),f(fallbackAlloc) { }

		void* alloc(msize* size=0);
		blk<void> alloc(msize size=4);
		template <typename T>
		T* alloc(u32* count=0);
		template <typename T>
		blk<T> alloc(u32 count=1);

		b32 free(void* ptr,msize size=4);
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

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	struct allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>
	{
		static const alloc_t TYPE=alloc_t::FALLBACK;
		static const u32 PS=PSIZE;
		static const u32 FS=FSIZE;
		typedef allocator<(alloc_t)P,PSIZE> palloc;
		typedef allocator<(alloc_t)F,FSIZE> falloc;

		palloc* p;
		falloc* f;

		allocator() : p(0),f(0) { }
		allocator(palloc* primaryAlloc,
				falloc* fallbackAlloc) 
			: p(primaryAlloc),f(fallbackAlloc) { }

		void* alloc(msize* size=0);
		blk<void> alloc(msize size=4);
		template <typename T>
		T* alloc(u32* count=0);
		template <typename T>
		blk<T> alloc(u32 count=1);

		b32 free(void* ptr,msize size=4);
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
}

#include "dggt_mem_fallback_alloc.inl"

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
