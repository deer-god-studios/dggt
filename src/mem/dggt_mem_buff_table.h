#ifndef _DGGT_MEM_BUFF_TABLE_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	struct buff_alloc
		: allocator
	{
		vpage buff;

		buff_alloc();
		buff_alloc(vpage buffer);
		buff_alloc(void* buffer,msize size);
	};
}

#define _DGGT_MEM_BUFF_TABLE_H_
#endif
