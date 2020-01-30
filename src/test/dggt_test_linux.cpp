#include <cstdio>
#include "dggt.h"

using namespace dggt;

typedef temp_fallback_alloc<alloc_t::STORE_TABLE,2048,alloc_t::LINEAR> lin_store_table;

int main(int argc, char* argv[])
{
	cache_init(MB(100));

	PTR_TO(lin_alloc<>,linAlloc);
	*linAlloc=create_alloc<alloc_t::LINEAR>(KB(2));

	PTR_TO(store_table_alloc<2048>,storeTableAlloc);
	*storeTableAlloc=create_alloc<alloc_t::STORE_TABLE,2048>();

	PTR_TO(lin_store_table,fallbackAlloc);

	*fallbackAlloc=
		create_alloc<alloc_t::STORE_TABLE,2048,alloc_t::LINEAR>(
				storeTableAlloc,linAlloc);

	cache_shutdown();

	return 0;
}
