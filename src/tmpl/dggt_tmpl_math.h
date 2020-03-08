#ifndef _DGGT_TMPL_MATH_H_

namespace dggt
{
	template <u32 Val>
	struct pow2
	{
		static constexpr const u32 val=2*pow2<Val-1>::val;
	};

	template <typename T>
	struct pow2<0,typename T>
	{
		static constexpr const u32 val=1;
	};
}

#define _DGGT_TMPL_MATH_H_
#endif
