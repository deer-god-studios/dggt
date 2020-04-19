#include "dggt_mem_utils.h"

namespace dggt
{
	void mem_cpy(void* dest,void* src,msize size)
	{
		for (msize b=0;b<size;++b)
		{
			*((ubyte*)dest+b)=*((ubyte*)src+b);
		}
	}

	void zero_mem(void* mem,msize size)
	{
		for (msize b=0;b<size;++b)
		{
			*((ubyte*)mem+b)=0;
		}
	}
	void* malloc(msize size)
	{
		return mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,0,0);
	}

	b32 free(void* mem,msize size)
	{
		munmap(mem,size);
		return true;
	}
}
