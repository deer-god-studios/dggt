#ifndef _DGGT_COLL_STARRAY_MEM_H_

#include "mem/dggt_mem_blk.h"

namespace dggt
{
	template <typename T,msize S>
	using starray_mem=blk<T,S>;
}

#define _DGGT_COLL_STARRAY_MEM_H_
#endif
