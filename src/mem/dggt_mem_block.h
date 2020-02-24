#ifndef _DGGT_MEM_BLOCK_H_

namespace dggt
{
	struct mem_block
	{
		mem_block* next;
	};

	struct sized_block
	{
		msize size;
		sized_block* next;
	};
}

#define _DGGT_MEM_BLOCK_H_
#endif
