#ifndef _DGGT_COLL_DLLIST_KEY_H_

#include "dggt_coll_dlnode.h"

namespace dggt
{
	template <typename T>
	struct dllist_key
	{
		dlnode<T>* node;
		dlpair<T> pair;

		dllist_key(dlnode<T>* node,dlpair<T> pair) :
			node(node),pair(pair) { }
		dllist_key() : dllist_key(0,dlpair<T>()) { }

		b32 operator==(const dllist_key<T>& rhs) const
		{
			return this==&rhs||
				(node==rhs.node);
		}

		b32 operator!=(const dllist_key<T>& rhs) const
		{
			return !(this->operator==(rhs));
		}

		dllist_key<T>& operator++()
		{
			if (!is_end())
			{
				node=node->next;
			}
			return *this;
		}

		dllist_key<T> operator++(int)
		{
			dllist_key<T> result=*this;
			this->operator++();
			return result;
		}

		dllist_key<T>& operator--()
		{
			if (!is_end())
			{
				node=node->next;
			}
			return *this;
		}

		dllist_key<T> operator--(int)
		{
			dllist_key<T> result=*this;
			this->operator++();
			return result;
		}

		b32 is_end() const
		{
			return node==0;
		}

		b32 is_begin() const
		{
			return node==pair.get_head();
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

#define _DGGT_COLL_DLLIST_KEY_H_
#endif
