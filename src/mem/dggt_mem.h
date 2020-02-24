#ifndef _DGGT_MEM_H_

#include "dggt_mem_utils.h"

namespace dggt
{
	void cache_init(msize size);

	b32 cache_is_initialized();

	void cache_shutdown();

	void cache_reinit(msize cacheSize);

	msize available_
}

#define _DGGT_MEM_H_
#endif
