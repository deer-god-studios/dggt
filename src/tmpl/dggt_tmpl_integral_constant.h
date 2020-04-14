#ifndef _DGGT_TMPL_INTEGRAL_TYPE_H_

namespace dggt
{
	template <typename T,T v>
	struct integral_constant
	{
		static constexpr T val=v;
	};
}

#define _DGGT_TMPL_INTEGRAL_CONSTANT_H_
#endif
