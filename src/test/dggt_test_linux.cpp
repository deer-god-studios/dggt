#include <cstdio>
#include "dggt.h"

using namespace dggt;

int main(int argc, char* argv[])
{
	cache_init(MB(100));

	PTR_TO(lin_alloc<>,linAlloc);
	*linAlloc=create_alloc<alloc_t::LINEAR>(KB(2));

	destroy_alloc(linAlloc);

	PTR_TO(lin_alloc<KB(2)>,linArrAlloc);
	*linArrAlloc=create_alloc<alloc_t::LINEAR,KB(2)>();

	printf("\n%d\n",sizeof(*linArrAlloc));

	u32 realCount=40;
	real32* realPtr=linArrAlloc->alloc<real32>(&realCount);

	PTR_TO(store_table_alloc<2048>,storeTableAlloc);
	*storeTableAlloc=create_alloc<alloc_t::STORE_TABLE,2048>();

	printf("\n%x, %d\n",realPtr,realCount);
	cache_shutdown();

	return 0;
}
