#ifndef _DGGT_MEM_PAGE_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T,msize SIZE>
	struct stblk
	{
		T[SIZE] mem;

		stblk();
		stblk(const T& val);
		stblk(T[SIZE] mem);

		T* get_ptr(msize offset=0);
		const T* get_ptr(msize offset=0) const;
		
		void* get_data(msize byteOffset=0);
		const void* get_data(msize byteOffset=0) const;

		T& operator[](msize offset);
		const T& operator[](msize offset) const;

		b32 operator==(const stblk<T,S>& rhs) const;
		b32 operator!=(const stblk<T,S>& rhs) const;
	};
}

#include "dggt_mem_page.inl"

#define _DGGT_MEM_PAGE_H_
#endif
