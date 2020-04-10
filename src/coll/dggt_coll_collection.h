#ifndef _DGGT_COLL_COLLECTION_H_

#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T,typename M,typename C,typename I>
	struct collection
	{
		typedef I<T,M,C> iter;
		typedef iter::mem_type mem_type;

		mem_type mem;
	};
}

#define _DGGT_COLL_COLLECTION_H_
#endif
