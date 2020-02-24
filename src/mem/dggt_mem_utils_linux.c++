#include "dggt_mem_utils.h"

namespace dggt
{
	void* mem_alloc(msize size)
	{
		return mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	}

	void mem_free(void* mem,msize size)
	{
		munmap(mem,size);
	}
}
