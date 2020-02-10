#ifndef _DGGT_MEM_BLK_H_

#include "dggt_mem_mem.h"

namespace dggt
{
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

		T* operator->();
		const T* operator->() const;
		T& operator*();
		const T& operator*() const;

		T& operator[](uint32_t index);
		const T& operator[](uint32_t index) const;

		operator T*();
		bool32 operator==(const blk<T>& rhs)
		{
			return rhs.mem==mem&&rhs.count==count;
		}
		bool32 operator!=(const blk<T>& rhs)
		{
			return !(*this==rhs);
		}
		template <typename S>
		explicit operator blk<S>();
		explicit operator blk<void>();
	};

	template <typename T>
	blk<T> blk_alloc(u32 count);

	template <typename T>
	void blk_free(blk<T>& block);


	template <>
	struct blk<void>
	{
		void* mem;
		msize size;

		blk();
		blk(void* mem,msize size);
		blk(const blk& other);
		template <typename T>
			blk(const blk<T>& other)
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

		bool32 operator==(const blk<void>& rhs)
		{
			return mem==rhs.mem&&size==rhs.size;
		}
		bool32 operator!=(const blk<void>& rhs)
		{
			return !(*this==rhs);
		}
	};

	typename blk<void> vblk;

	template <typename T>
	static const blk<T> NULL_BLK=blk<T>();

	template <typename T>
	blk<T> blk_alloc(u32 count);
	template <typename T>
	void blk_free(blk<T> block);

	vblk blk_alloc(msize size);
	void blk_free(vblk block);

	template <typename T>
	void blk_cpy(blk<T> dest,blk<T> src,u32 count);

	void blk_cpy(vblk dest,vblk src,msize size);
}

#include "dggt_mem_blk.inl"
#define _DGGT_MEM_BLK_H_
#endif
