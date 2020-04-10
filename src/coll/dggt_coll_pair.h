#ifndef _DGGT_COLL_PAIR_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T,typename U=T>
	struct pair
	{
		T first;
		U second;
	};
}

#define _DGGT_COLL_PAIR_H_
#endif
