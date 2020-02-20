#include <cstdio>
#include "dggt.h"

using namespace dggt;

typedef fallback_alloc<> lin_store_table;
typedef hash_table<u32,float32> f32_table;

static lin_alloc<> linAlloc_;
static lin_alloc<>* linAlloc;
static store_table_alloc<2048> storeTableAlloc_;
static store_table_alloc<2048>* storeTableAlloc;
static lin_store_table alloc_;
static lin_store_table* alloc;

void pause_output()
{
	printf("-- press Enter to continue --\n");
	std::getchar();
}

void new_line()
{
	printf("\n");
}

void line_break()
{
	printf("---------------------------------------------------------------\n");
}

void print_alloc_info()
{

}

void init_test()
{

}

template <u32 BLOCKS>
void test_alloc()
{

}

void test_linked_list()
{

}

void test_stack()
{

}

void test_queue()
{

}

void test_hash_table()
{

}

int main(int argc, char* argv[])
{
	cache_init(GB(2));

	blkv buff=cache_alloc(KB(50));

	lin_alloc linAlloc=lin_alloc(buff);
	cache_shutdown();

	return 0;
}
