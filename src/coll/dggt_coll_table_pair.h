#ifndef _DGGT_COLL_TABLE_PAIR_H_

#include "dggt_coll_pair.h"

namespace dggt
{
	template <typename K,typename V>
	struct table_pair:pair<K,V>
	{
		table_pair() { }
		table_pair(K key,V val)
			: first(key),second(val) { }

		const K& get_key() const { return first; }
		V& get_val() { return second;}
		const V& get_val() const { return second;}

		b32 operator==(const table_pair& other)
		{
			return first==other.first;
		}
	};
}

#define _DGGT_COLL_TABLE_PAIR_H_
#endif
