#ifndef _DGGT_COLL_STARRAY_KEY_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T,msize S>
	struct starray_key
	{
		T* ptr;
		msize offset;

		starray_key() : ptr(0),offset(0) { }
		starray_key(T* ptr,msize offset) : ptr(ptr),offset(offset) { }

		b32 operator==(const starray_key<T,S>& rhs) const
		{
			return this==&rhs||
				(ptr==rhs.ptr&&offset==rhs.offset);
		}

		b32 operator!=(const starray_key<T,S>& rhs) const
		{
			return !(this->operator==(rhs));
		}

		starray_key<T,S>& operator++()
		{
			if (!is_end())
			{
				++offset;
				++ptr;
			}
			return *this;
		}

		starray_key<T,S> operator++(int)
		{
			starray_key<T,S> result=*this;
			this->operator++();
			return result;
		}

		b32 is_end() const
		{
			return offset>=S;
		}

		T& operator*()
		{
			return *ptr;
		}

		const T& operator*() const
		{
			return *ptr;
		}

		explicit operator T*() { return ptr; }
		explicit operator const T*() const { return ptr; }
	};
}

#define _DGGT_COLL_STARRAY_KEY_H_
#endif
