#ifndef _DGGT_COLL_STACK_KEY_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T>
	struct stack_key
	{
		T* ptr;
		msize size;
		msize offset;

		stack_key():ptr(0),size(0),offset(0) { }
		stack_key(T* ptr,msize size,msize offset)
			: this->ptr(ptr),this->size(size),this->offset(offset) { }

		b32 operator==(const stack_key<T>& rhs)
		{
			return this==&rhs||
				(ptr==rhs.ptr&&size==rhs.size&&offset==rhs.offset);
		}

		b32 operator!=(const stack_key<T>& rhs)
		{
			return !(this->operator==(rhs));
		}

		stack_key<T>& operator++()
		{
			if (!is_end())
			{
				--offset;
				--ptr;
			}
			return *this;
		}

		stack_key<T> operator++(int)
		{
			stack_key<T> result=*this;
			this->operator--();
			return result;
		}

		b32 is_end() const
		{
			return offset==0;
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

#define _DGGT_COLL_STACK_KEY_H_
#endif
