#ifndef _DGGT_COLL_HASH_H_

namespace dggt
{
	template <typename K>
	u32 prehash(const K& key);

	template <>
	u32 prehash(const u32& key);
}

#define _DGGT_COLL_HASH_H_
#endif
