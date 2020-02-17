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
		static T val;
	};
}

#define _DGGT_TMP_ENABLE_IF_H_
#endif
