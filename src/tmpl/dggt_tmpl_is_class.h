#ifndef _DGGT_TMPL_IS_CLASS_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename T>
	struct is_class
	{
		static constexpr bool32 val=__is_class(T);
	};
}

#define _DGGT_TMPL_IS_CLASS_H_
#endif
