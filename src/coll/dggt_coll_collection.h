#ifndef _DGGT_COLL_COLLECTION_H_

#include "dggt_coll_iterator.h"

namespace dggt
{
	template <typename T,typename M,typename C,typename I>
	struct coll_settings
	{
		typedef T val_type;
		typedef M mem_type;
		typedef C coll_type;
		typedef I iter;
	};

	template <typename Settings>
	struct collection
	{
		typedef typename Settings::iter iter;
		typedef typename Settings::mem_type mem_type;

		mem_type mem;

		collection() : mem(mem_type()) { }
	};
}

#define _DGGT_COLL_COLLECTION_H_
#endif
