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

		page(T* memPtr,msize memCount) : ptr(memPtr), size(memCount) { }
		page() : page(0,0) { }

		T* operator->() { return ptr; }
		const T* operator->() const { return ptr; }
		T& operator*() { return *ptr; }
		const T& operator*() const { return *ptr; }
		T& operator[] (msize index) { return ptr[index]; }
		const T& operator[] (msize index) const { return ptr[index]; }

		page<T> operator+(msize offset)
		{
			return offset<size?page<T>(ptr+offset,size-offset):page<T>();
		}

		const page<T> operator+(msize offset) const
		{
			return page<T>(ptr+offset,size-offset):page<T>();
		}

		page<T>& operator++() { return this->operator+(1); }

		page<T> operator++(int)
		{
			page<T> result=*this;
			this->operator++();
			return result;
		}

		explicit operator T*() { return ptr; }
	};

	template <typename T>
	global constexpr const page<T> NULL_PAGE=page<T>();

	template <typename T,typename A>
	page<T> malloc_page(A* a,msize size)
	{
		return page<T>(malloc(a,size),size);
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
