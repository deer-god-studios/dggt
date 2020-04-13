#ifndef _DGGT_COLL_SLLIST_KEY_H_

#include "dggt_coll_slnode.h"

namespace dggt
{
	template <typename T>
	struct sllist_key
	{
		slnode<T>* node;

		sllist_key(slnode<T>* node) : node(node) { }
		sllist_key() : sllist_key(0) { }

		b32 operator==(const sllist_key<T>& rhs)
		{
			return this==&rhs||
				(node=rhs.node);
		}

		b32 operator!=(const sllist_key<T>& rhs)
		{
			return !(this->operator==(rhs));
		}

		sllist_key<T>& operator++()
		{
			if (!is_end())
			{
				node=node->next;
			}
			return *this;
		}

		sllist_key<T> operator++(int)
		{
			sllist_key<T> result=*this;
			this->operator++();
			return result;
		}

		b32 is_end() const
		{
			return node==0;
		}

		T& operator*()
		{
			return node->val;
		}

		const T& operator*() const
		{
			return node->val;
		}

		explicit operator T*() { return (T*)node; }
		explicit operator const T*() const { return (T*)node; }
	};
}

#define _DGGT_COLL_SLLIST_KEY_H_
#endif
