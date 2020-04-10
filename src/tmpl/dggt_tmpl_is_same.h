#ifndef _DGGT_TMPL_IS_SAME_H_

#include "dggt_tmpl_bool_types.h"

namespace dggt
{
	template <typename T,typename U>
	struct is_same : false_type { }

	template <typename T>
	struct is_same<T,T> : true_type { }
}

#define _DGGT_TMPL_IS_SAME_H_
#endif
