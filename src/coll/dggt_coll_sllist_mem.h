#ifndef _DGGT_MEM_SLLIST_MEM_H_

#include "dggt_coll_slnode.h"

namespace dggt
{
	template <typename T>
	struct slchain
	{
		slnode<T>* head;
		b32 valid;

		b32 operator==(const slchain<T>& rhs) const
		{
			return this==&rhs||
				(head==rhs.head&&valid==rhs.valid);
		}

		b32 operator!=(const slchain<T>& rhs) const
		{
			return !(this->operator==(rhs));
		}

		explicit operator slnode<T>*() { return head; }
	};

	template <typename T>
	using sllist_mem=slchain<T>;

	template <typename T,typename A>
	sllist_mem<T> malloc_sllist_mem(A* a)
	{
		sllist_mem<T> result={};
		result.valid=true;
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,sllist_mem<T>& mem)
	{
		mem.valid=false;
		return free(a,mem.head);
	}
}

#define _DGGT_MEM_SLLIST_MEM_H_
#endif
