#ifndef _DGGT_TMPL_SEQUENCE_H_

namespace dggt
{
	template <u32... S>
	struct sequence { };

	template <u32... S>
	sequence<S...> make_sequence()
	{
		return sequence<S...>();
	}

	template <u32 NEW,u32... REST>
	sequence<NEW,REST...> push(sequence<REST...> seq)
	{
		return sequence<NEW,REST...>(); 
	}

	template <u32 HEAD,u32... REST>
	sequence<REST...> pop(sequence<HEAD,REST...> seq)
	{
		return sequence<REST...>();
	}

	template <u32 I,u32... S>
	constexpr u32 get(sequence<S...> seq);

	template <u32 HEAD,u32... REST>
	constexpr u32 get<0>(sequence<HEAD,REST...>& seq)
	{
		return HEAD;
	}

	template <u32 I,u32 HEAD,u32... REST>
	constexpr u32 get(sequence<HEAD,REST...>& seq)
	{
		return get<I-1>(sequence<REST...>& seq);
	}
}

#define _DGGT_TMPL_SEQUENCE_H_
#endif
