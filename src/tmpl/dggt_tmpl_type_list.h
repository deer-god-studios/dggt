#ifndef _DGGT_TMPL_TYPE_LIST_H_

namespace dggt
{
	template <typename... Ts>
	struct type_list { }

	template <typename T,typename... TRest>
	type_list<T,TRest...> push(type_list<TRest...>& typeList)
	{
		return type_list<T,TRest...>();
	}

	template <typename T,typename... TRest>
	type_list<TRest...> pop(type_list<T,TRest...>& typeList)
	{
		return type_list<TRest...>();
	}

	template <typename... Ts>
	type_list<Ts...> make_type_list()
	{
		return type_list<Ts...>();
	}
}

#define _DGGT_TMPL_TYPE_LIST_H_
#endif
