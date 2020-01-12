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

		allocator(blk<void> buffer);
		allocator(void* buffPtr,msize buffSize);

		blk<void> alloc(msize size=4);
		void* alloc(msize* size);
		template <typename T>
		blk<T> alloc(u32 count=1);
		template <typename T>
		T* alloc(u32* count);

		void clear();

		msize available_mem() const;
		msize used_mem() const;

		b32 owns(const blk<void> block) const;
		b32 owns(const void* ptr) const;
		template <typename T>
		b32 owns(const blk<T> block) const;
		template <typename T>
		b32 owns(const T* ptr) const;

		private:
		allocator();
	};
}
#include "dggt_mem_linear_alloc.inl"

#define _DGGT_MEM_LINEAR_ALLOC_H_
#endif
