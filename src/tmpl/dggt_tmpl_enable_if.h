#ifndef _DGGT_TMPL_ENABLE_IF_H_

namespace dggt
{
	template <bool B,typename T=void>
	struct enable_if
	{
	};

	template <typename T=void>
	struct enable_if<false,T>
	{
		typedef T val;
	};

	template <bool B,u32 VAL=0>
	struct enable_u32_if
	{
	};

	template <u32 VAL=0>
	{
		static const u32 VAL;
	};
}

#define _DGGT_TMP_ENABLE_IF_H_
#endif
