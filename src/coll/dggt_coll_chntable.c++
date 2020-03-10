#include "dggt_coll_chntable.h"

namespace dggt
{
	template <>
	u32 prehash(const u32& key)
	{
		return key;
	}
}
