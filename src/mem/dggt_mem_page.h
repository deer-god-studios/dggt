#ifndef _DGGT_MEM_PAGE_H_

#include "types/dggt_types.h"
#include "defines/dggt_defines.h"

namespace dggt
{
	template <typename T>
	struct page
	{
		T* ptr;
		msize size;

		page(T* ptr,msize size) : ptr(ptr),size(size) { }
		page() : page(0,0) { }

		T* operator->() { return ptr; }
		const T* operator->() const { return ptr; }
		T& operator*() { return *ptr; }
		const T& operator*() const { return *ptr; }
		T& operator[] (msize index) { return ptr[index]; }
		const T& operator[] (msize index) const { return ptr[index]; }

		explicit operator T*() { return ptr; }

		page<T>& operator=(const page<T>& rhs)
		{
			if (this!=&rhs)
			{
				ptr=rhs.ptr;
				size=rhs.size;
			}
			return *this;
		}

		b32 operator==(const page<T>& rhs) const
		{
			return this==&rhs||
				(ptr==rhs.ptr&&size==rhs.size);
		}

		b32 operator!=(const page<T>& rhs) const
		{
			return !(this->operator==(rhs));
		}
	};

	template <typename T>
	global constexpr const page<T> NULL_PAGE=page<T>();

	template <typename T,typename A>
	page<T> malloc_page(A* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T,typename A>
	b32 free(A* a,page<T>& pge)
	{
		return free(a,pge.ptr,pge.size);
	}

	template <typename T,typename A>
	b32 owns(A* a,page<T>& pge)
	{
		return owns(a,pge.ptr,pge.size);
	}
}

#define _DGGT_MEM_PAGE_H_
#endif
