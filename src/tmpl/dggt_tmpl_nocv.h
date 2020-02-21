#ifndef _DGGT_TMPL_NOCV_H_

namespace dggt
{
	template <typename T>
	struct no_cv
	{
		typedef T type;
	};

	template <typename T>
	struct no_cv<const T>
	{
		typedef T type;
	};

	template <typename T>
	struct no_cv<volatile T>
	{
		typedef T type;
	};

	template <typename T>
	struct no_cv<const volatile T>
	{
		typedef T type;
	};
}

#define _DGGT_TMPL_NOCV_H_
#endif
