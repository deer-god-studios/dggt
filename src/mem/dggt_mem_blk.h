#ifndef _DGGT_MEM_BLK_H_

#include "dggt_mem_mem.h"

template <typename T>
struct blk
{
	T* mem;
	u32 count; 

	blk();
	blk(T* mem,msize count);
	blk(const blk& other);

	blk operator+(uint32_t offset) const;
	blk operator-(uint32_t offset) const;

	blk& operator=(const blk& rhs);

	uint32_t operator==(const blk& rhs) const;
	uint32_t operator!=(const blk& rhs) const;

	T* data();
	const T* data() const;

	T& operator[](uint32_t index);
	const T& operator[](uint32_t index) const;

	operator T*();

	template <typename S>
	explicit operator blk<S>();
};

template <typename T>
blk<T> blk_alloc(u32 count);

template <typename T>
void blk_free(blk<T>& block);

#include "dggt_mem_blk.inl"

template <>
struct blk<void>
{
	void* mem;
	msize size;

	blk();
	blk(void* mem,msize size);
	blk(const blk& other);
	template <typename T>
	blk(const blk<T> other)
		: blk(other.mem,other.count*sizeof(T)) { }

	blk operator+(uint32_t offset) const;
	blk operator-(uint32_t offset) const;
	blk& operator=(const blk& other);

	uint32_t operator==(const blk& rhs) const;
	uint32_t operator!=(const blk& rhs) const;

	operator void*();

	template <typename S>
	explicit operator blk<S>()
	{
		return blk<S>((S*)mem,size/sizeof(S));
	}
};

blk<void> blk_alloc(msize size);
void blk_free(blk<void>& block);
#define _DGGT_MEM_BLK_H_
#endif
