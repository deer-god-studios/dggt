#ifndef _DGGT_TMPL_IS_UNION_H_

#include "types/dggt_types.h"

namespace
{
	template <typename T>
	struct is_union
	{
		static constexpr bool32 val=__is_union(T);
	};

}

#define _DGGT_TMPL_IS_UNION_H_
#endif
