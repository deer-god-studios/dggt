#include "dggt_coll_hash_table.h"

namespace dggt
{
	template <>
	u32 prehash(const u32& key)
	{
		return key;
	}
}
