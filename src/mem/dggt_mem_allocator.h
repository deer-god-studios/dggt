#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "defines/dggt_defines.h"
#include "types/dggt_types.h"
#include "dggt_mem_defines.h"

namespace dggt
{
	typedef msize stack_state;
	static constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;
}

#define _DGGT_MEM_ALLOCATOR_H_
#endif
