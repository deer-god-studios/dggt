#include <cstdio>
#include "defines/dggt_defines.h"
#include "types/dggt_types.h"
#include "math/dggt_math.h"
#include "mem/dggt_mem.h"
#include "coll/dggt_coll.h"

using namespace dggt;

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

void test_cache()
{
	msize buffSize=KB(50);
	printf("cache_alloc\n");
	void* buff=cache_alloc(buffSize);
	printf("available_cache_mem: %d\n",available_cache_mem());

	free_alloc* cacheAlloc=get_cache_alloc();
	printf("cacheAlloc.buff: %X\n",cacheAlloc->buff);
	printf("cacheAlloc.buffSize: %d\n",cacheAlloc->buffSize);
	printf("cacheAlloc.used: %d\n",cacheAlloc->used);
	printf("cacheAlloc.freeList: %d\n",cacheAlloc->freeList);
	printf("lin_alloc\n");
	lin_alloc linAlloc=lin_alloc(buff,buffSize);
	printf("linAlloc.buff: %X\n",linAlloc.buff);
	printf("linAlloc.buffSize: %d\n",linAlloc.buffSize);
	printf("linAlloc.used: %d\n",linAlloc.used);
	u32 floatCount=50;
	printf("alloc\n");
	float* floatArr=alloc<float>(&linAlloc,floatCount);
	for (u32 i=0;i<floatCount;++i)
	{
		floatArr[i]=(float)i/7.0f;
	}
	for (u32 i=0;i<floatCount;++i)
	{
		printf("%f\n",floatArr[i]);
	}

	cache_free(buff,buffSize);
}

int main(int argc, char* argv[])
{
	printf("cache_init\n");
	cache_init(GB(2));

	free_alloc a_=free_alloc(cache_alloc(KB(8)),KB(8));
	free_alloc* a=&a_;

	linked_list<real32> real32List=create_linked_list<real32>();

	array<u32> u32Arr=create_array<u32>(2,a);

	for (u32 i=0;i<20;++i)
	{
		push(&u32Arr,i%3,a);
		printf("%d\n",*(peek(&u32Arr)));
	}

	while (!is_end(pop(&u32Arr,a))) { }

	printf("%d\n",get_count(&u32Arr));

	printf("%d\n",a->freeList->size);
	printf("%d\n",KB(8));
	printf("cache_shutdown\n");
	cache_shutdown();

	return 0;
}
