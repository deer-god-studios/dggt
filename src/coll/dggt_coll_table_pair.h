#ifndef _DGGT_COLL_TABLE_PAIR_H_

#include "types/dggt_types.h"

namespace dggt
{
	template <typename K,typename V>
	struct table_pair
	{
		K key_;
		V val_;

		table_pair() { }
		table_pair(K key,V val)
			: key_(key),val_(val) { }

		const K& get_key() { return key_; }
		V& get_val() { return val_;}
		const V& get_val() const { return val_;}

		b32 operator==(const table_pair& other)
		{
			return key_==other.key_;
		}
	};
}

#define _DGGT_COLL_TABLE_PAIR_H_
#endif
