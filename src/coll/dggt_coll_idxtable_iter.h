#ifndef _DGGT_COLL_IDX_ITER_H_

#include "dggt_coll_membership.h"
#include "dggt_coll_array.h"
#include "dggt_coll_stack.h"
#include "dggt_coll_iterator.h"

namespace dggt
{
	global const fl32 IDX_EMPTY=MEMB_EMPTY;
	global const fl32 IDX_OCCUPIED=MEMB_OCCUPIED;

	template <typename T>
	struct idxtable;

	template <typename T>
	using idxmem=stack_mem<T>;

	template <typename T>
	struct idxtable_mem;

	template <typename T>
	struct idxtable_key
	{
		T* ptr;
		flag32* flag;
		msize size;
		msize offset;

		idxtable_key():ptr(0),flag(0),size(0),offset(0) { }
		idxtable_key(T* ptr,flag32* flag,msize size,msize offset)
			: this->ptr(ptr),this->flag(flag),this->size(size),
			this->offset(offset) { }

		b32 operator==(const idxtable_key<T>& rhs)
		{
			return this==&rhs||
				(ptr==rhs.ptr&&size==rhs.size&&offset==rhs.offset);
		}

		b32 operator!=(const idxtable_key<T>& rhs)
		{
			return !(this->operator==(rhs));
		}

		idxtable_key<T>& operator++()
		{
			if (!is_end())
			{
				do
				{
					++offset;
					++ptr;
					++flag;
				} while (!is_end()&&*flag==IDX_EMPTY)
			}
			return *this;
		}

		idxtable_key<T> operator++(int)
		{
			idxtable_key<T> result=*this;
			this->operator++();
			return result;
		}

		b32 is_end() const
		{
			return offset>size;
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

	template <typename T>
	struct idxtable_iter_settings=
	iter_settings<T,idxtable_mem<T>,idxtable<T>,idxtable_key<T>>;
}

#define _DGGT_COLL_IDX_ITER_H_
#endif
