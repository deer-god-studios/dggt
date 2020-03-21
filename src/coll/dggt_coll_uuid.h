#ifndef _DGGT_COLL_UUID_H_

#include "types/dggt_types.h"

namespace dggt
{
	global const uuid NULL_UUID=0;

	template <typename A=free_alloc>
	uuid32 create_uuid(A* allocator=0);

	template <typename A=free_alloc>
	b32 destroy_uuid(uuid32 id,A* allocator=0);
}

#include "dggt_coll_uuid.inl"

#define _DGGT_COLL_UUID_H_
#endif
