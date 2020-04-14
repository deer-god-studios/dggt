#ifndef _DGGT_TMPL_IS_BASE_OF_H_

#include "dggt_tmpl_integral_constant.h"
#include "dggt_tmpl_is_class.h"
#include "dggt_tmpl_bool_types.h"

namespace dggt
{
	namespace internal_
	{
		template <typename B>
		true_type test_pre_ptr_convertable(const volatile B*);

		template <typename>
		false_type test_pre_ptr_convertable(const volatile void*);

		template <typename,typename>
		auto test_pre_is_base_of(...) -> true_type;
		template <typename B,typename D>
		auto test_pre_is_base_of(int) -> 
			decltype(test_pre_ptr_convertable<B>(static_case<D*>(nullptr)));
	}

	template <typename B,typename D>
	struct is_base_of:
		integral_constant<bool32,
		(is_class<B>::val&&is_class<D>::val&&
		decltype(internal_::test_pre_is_base_of<B,D>(0))::val)> { };
}

#define _DGGT_TMPL_IS_BASE_OF_H_
#endif
