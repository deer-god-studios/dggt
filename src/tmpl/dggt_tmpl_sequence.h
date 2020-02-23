#ifndef _DGGT_TMPL_SEQUENCE_H_

namespace dggt
{
	template <u32... S>
	struct sequence { };

	template <u32... S>
	struct make_sequence
	{
		using type=sequence<S...>;
	};

	template <typename seq,u32 NEW>
	struct sequence_push;

	template <u32... REST,u32 NEW>
	struct sequence_push<sequence<REST...>,NEW>
	{
		using type=sequence<NEW,REST...>;
	};

	template <typename seq>
	struct sequence_pop;

	template <u32 HEAD,u32... REST>
	struct sequence_pop<sequence<HEAD,REST...>>
	{
		using type=sequence<REST...>;
	};

	template <u32 I,typename seq>
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
