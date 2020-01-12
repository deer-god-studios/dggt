#include <cstdio>
#include "dggt.h"

using namespace dggt;

int main(int argc, char* argv[])
{
	printf("cache_init\n");
	cache_init(MEGABYTES(100));

	printf("%d\n",available_cache_mem());
	printf("create_alloc\n");
	allocator<alloc_t::LINEAR>* linAlloc=
		create_alloc<alloc_t::LINEAR>(1024);

	printf("linAlloc->alloc<real32>\n");
	u32 realCount=10;
	real32* realBlock=linAlloc->alloc<real32>(&realCount);
	for (u32 i=0;i<realCount;++i)
	{
		realBlock[i]=(real32)i/21.43f;
	}

	for (u32 i=0;i<realCount;++i)
	{
		printf("%f\n",realBlock[i]);
	}

	printf("destroy_alloc\n");
	destroy_alloc(linAlloc);
	cache_shutdown();

	return 0;
}
