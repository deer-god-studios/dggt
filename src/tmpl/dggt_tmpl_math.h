#ifndef _DGGT_TMPL_MATH_H_

namespace dggt
{
	template <u32 Val>
	struct pow2
	{
		static constexpr const u32 val=2*pow2<Val-1>::val;
	};

	template <>
	struct pow2<0>
	{
		static constexpr const u32 val=1;
	};

	template <u32 Val,u32 Pow>
	struct pow
	{
		static constexpr const u32 val=Val*pow<Val,Pow-1>::val;
	};

	template <u32 Val>
	struct pow<Val,0>
	{
		static constexpr const u32 val=1;
	};
}

#define _DGGT_TMPL_MATH_H_
#endif
