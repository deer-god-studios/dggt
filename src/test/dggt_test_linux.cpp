#include <cstdio>
#include "dggt.h"

using namespace dggt;

int main(int argc, char* argv[])
{
	cache_init(MB(100));

	PTR_TO(allocator<alloc_t::LINEAR>,linAlloc);
	*linAlloc=create_alloc<alloc_t::LINEAR>(KB(2));

	destroy_alloc(linAlloc);
	cache_shutdown();

	return 0;
}
