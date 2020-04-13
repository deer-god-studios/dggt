#ifndef _DGGT_COLL_DLLIST_MEM_H_

#include "dggt_coll_dlnode.h"

namespace dggt
{
	template <typename T>
	struct dlchain
	{
		dlpair<T> pair;
		b32 valid;

		b32 operator==(const dlchain<T>& rhs) const
		{
			return this==&rhs||
				(pair==rhs.pair);
		}

		b32 operator!=(const dlchain<T>& rhs) const
		{
			return !(this->operator==(rhs));
		}
	};

	template <typename T>
	using dllist_mem=dlchain<T>;

	template <typename T,typename A>
	dllist_mem<T> malloc_dllist_mem(A* a,msize capacity)
	{
		dllist_mem<T> result={};
		result.pair=malloc_dlpair<T>(a,capacity);
		result.valid=true;
		return result;
	}

	template <typename T,typename A>
	b32 free(A* a,dllist_mem<T>& mem)
	{
		mem.valid=false;
		return free(a,mem.pair);
	}
}

#define _DGGT_COLL_DLLIST_MEM_H_
#endif
