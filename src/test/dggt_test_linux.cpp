#include <cstdio>
#include "dggt.h"

using namespace dggt;

int main(int argc, char* argv[])
{
	printf("cache_init");
	cache_init(4096);

	printf("create_alloc");
	allocator linAlloc=create_alloc(alloc_t::LINEAR,1024);

	printf("linAlloc.alloc<real32>");
	blk<real32> realBlock=linAlloc.alloc<real32>(10);
	for (u32 i=0;i<realBlock.count;++i)
	{
		realBlock[i]=(real32)i/21.43f;
	}

	for (u32 i=0;i<realBlock.count;++i)
	{
		printf("%f\n",realBlock[i]);
	}

	printf("destroy_alloc");
	destroy_alloc(linAlloc);
	cache_shutdown();

	return 0;
}
