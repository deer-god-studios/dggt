#ifndef _DGGT_COLL_ARRAY_KEY_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T>
	struct array_key
	{
		T* ptr;
		msize size;
		msize offset;

		array_key():ptr(0),size(0),offset(0) { }
		array_key(T* ptr,msize size,msize offset)
			: ptr(ptr),size(size),offset(offset) { }

		b32 operator==(const array_key<T>& rhs)
		{
			return this==&rhs||
				(ptr==rhs.ptr&&size==rhs.size&&offset==rhs.offset);
		}

		b32 operator!=(const array_key<T>& rhs)
		{
			return !(this->operator==(rhs));
		}

		array_key<T>& operator++()
		{
			if (!this->is_end())
			{
				++offset;
				++ptr;
			}
			return *this;
		}

		array_key<T> operator++(int)
		{
			array_key<T> result=*this;
			this->operator++();
			return result;
		}

		array_key<T>& operator--()
		{
			if (!this->is_begin())
			{
				--offset;
				--ptr;
			}
			return *this;
		}

		array_key<T> operator--(int)
		{
			array_key<T> result=*this;
			this->operator--();
			return result;
		}


		b32 is_begin() const
		{
			// because of integer underflow,before begin is max 64-bit u64.
			return offset==MAX_MSIZE;
		}

		b32 is_end() const
		{
			return offset>=size;
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

#define _DGGT_COLL_ARRAY_KEY_H_
#endif
