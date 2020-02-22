#ifndef _DGGT_TMPL_SEQUENCE_H_

namespace dggt
{
	template <u32... S>
	struct sequence { };

	template <u32... S>
	struct make_sequence
	{
		typedef sequence<S...> type;
	};

	template <u32 NEW,template <u32...> seq>
	struct sequence_push;

	template <u32 NEW,u32... REST>
	struct sequence_push<NEW,sequence<REST...>>
	{
		using type=sequence<NEW,REST...>;
	};

	template <template <u32...> seq>
	struct sequence_pop;

	template <u32 HEAD,u32... REST>
	struct sequence_pop<sequence<HEAD,REST...>>
	{
		using type=sequence<REST...>;
	};

	template <u32 I,template <u32...> seq>
	struct sequence_get;

	template <u32 HEAD,u32... REST>
	struct sequence_get<0,sequence<HEAD,REST...>>
	{
		static constexpr const u32 value=HEAD;
	};

	template <u32 I,u32 HEAD,u32... REST>
	struct sequence_get<I,sequence<HEAD,REST...>>
	{
		static constexpr const u32 value=
			sequence_get<I-1,sequence<REST...>>::value;
	};
}

#define _DGGT_TMPL_SEQUENCE_H_
#endif
