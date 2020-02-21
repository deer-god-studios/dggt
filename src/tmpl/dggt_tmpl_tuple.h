#ifndef _DGGT_TMPL_TUPLE_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename... Ts>
	struct tuple;

	template <typename T>
	struct tuple<T>
	{
		T val;
	};

	template <typename T,typename... TRest>
	struct tuple<T,TRest...>:tuple<TRest...>
	{
		T val;

		tuple(T firstVal,TRest ...vals)
			:tuple(vals...)
		{
			val=firstVal;
		}
	};

	template <typename T>
	struct tuple<T>
	{
		T val;

		tuple(T firstValue)
		{
			val=firstValue;
		}
	};

	template <typename... Ts>
	tuple<Ts...> make_tuple(Ts ...vals)
	{
		return tuple<Ts...>(vals...);
	}

	template <u32 I,typename... Ts>
	auto& get(tuple<Ts...>& tpl);

	template <typename T,typename... Ts>
	T& get<0>(tuple<T,Ts...>& tpl)
	{
		return tpl.val;
	}

	template <u32 I,typename T,typename... Ts>
	auto& get(tuple<T,Ts...>& tpl)
	{
		return get<I-1>((tuple<Ts...>&)tpl);
	}
}

#define _DGGT_TMPL_TUPLE_H_
#endif
