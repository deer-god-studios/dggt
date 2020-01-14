#include <cstdio>
#include "dggt.h"

using namespace dggt;

template <u32 S>
using lin_array_alloc=allocator<alloc_t::LINEAR,S>;

int main(int argc, char* argv[])
{
	cache_init(MB(100));

	PTR_TO(allocator<alloc_t::LINEAR>,linAlloc);
	*linAlloc=create_alloc<alloc_t::LINEAR>(KB(2));

	destroy_alloc(linAlloc);

	PTR_TO(lin_array_alloc<KB(2)>,linArrAlloc);
	*linArrAlloc=create_alloc<alloc_t::LINEAR,KB(2)>();

	printf("\n%d\n",sizeof(*linArrAlloc));

	u32 realCount=40;
	real32* realPtr=linArrAlloc->alloc<real32>(&realCount);

	printf("\n%x, %d\n",realPtr,realCount);
	cache_shutdown();

	return 0;
}
