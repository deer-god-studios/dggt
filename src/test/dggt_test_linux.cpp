#include <cstdio>
#include "dggt.h"

int main(int argc, char* argv[])
{
	dggt_mem_init(4096);

	allocator linAlloc=dggt_mem_create_alloc(alloc_t::LINEAR,1024);

	blk<real32> realBlock=linAlloc.alloc<real32>(10);
	for (u32 i=0;i<realBlock.count;++i)
	{
		realBlock[i]=(real32)i/21.43f;
	}

	for (u32 i=0;i<realBlock.count;++i)
	{
		printf("%f\n",realBlock[i]);
	}
	dggt_mem_free();
	return 0;
}