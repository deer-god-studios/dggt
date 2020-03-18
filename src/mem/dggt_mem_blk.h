#ifndef _DGGT_MEM_BLK_H_

#include "types/dggt_types.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	template <typename T>
	struct blk
	{
		T* ptr;
		u32 count;

		blk() : ptr(0),count(0) { }
		blk(T* memPtr,u32 memCount) : ptr(memPtr),count(memCount) { }

		T& operator*() { return *ptr; }
		const T& operator*() const { return *ptr; }
		T& operator[] (u32 index) { return ptr[index]; }
		const T& operator[] (u32 index) const { return ptr[index]; }
	};

	template <typename T>
	global constexpr const blk<T> NULL_BLK=blk<T>();
}

#define _DGGT_MEM_BLK_H_
#endif
