#ifndef _DGGT_TMPL_IS_TYPE_H_

#include "dggt_tmpl_is_same.h"
#include "dggt_tmpl_is_base_of.h"

namespace dggt
{
	template <typename B,typename D>
	struct is_type:
		integral_constant<bool32,is_same<B,D>::val||is_base_of<B,D>::val> { };

}

#define _DGGT_TMPL_IS_TYPE_H_
#endif
