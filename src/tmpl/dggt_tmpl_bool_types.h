#ifndef _DGGT_TMPL_BOOL_TYPES_H_

#include "types/dggt_types.h"

namespace dggt
{
	struct true_type
	{
		static constexpr bool32 val=true;
	};

	struct false_type
	{
		static constexpr bool32 val=false;
	};
}

#define _DGGT_TMPL_BOOL_TYPES_H_
#endif
