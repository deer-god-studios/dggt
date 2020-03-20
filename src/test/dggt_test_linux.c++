// TODO: test stallocator
// TODO: test autostack
// TODO: test queue

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

template <typename A>
void print_alloc_info(A* allocator)
{
	line_break();

	printf("used_mem: %d\n",used_mem(allocator));
	printf("available_mem: %d\n",available_mem(allocator));
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

template <typename K,typename V,typename A>
void test_chntable(chntable<K,V>* table,A* a)
{
	chntable<u32,float32> floatTable=create_chntable<u32,float32>(a);
	insert(&floatTable,0U,3.14f,a);
	insert(&floatTable,50U,77.1f,a);

	printf("%f\n",get(floatTable[0U]).get_val());

	remove(&floatTable,0U,a);

	printf("%f\n",get(floatTable[50U]).get_val());

}

void test_stallocator()
{
	stallocator<4096,free_alloc> freeStalloc;
	int* intMem=alloc<int>(&freeStalloc,4);
	intMem[0]=40;
	intMem[1]=1;
	intMem[2]=4;
	intMem[4]=6;

	for (u32 i=0;i<5;++i)
	{
		printf("intMem[%d]: %d\n",i,intMem[i]);
	}
}

int main(int argc, char* argv[])
{
	printf("cache_init\n");
	cache_init(GB(2));

	free_alloc a_=free_alloc(cache_alloc(KB(8)),KB(8));
	free_alloc* a=&a_;
	//test_stallocator();
	//test_cache();

	oatable<u32,float64> float64ChnTable=create_oatable<u32,float64>(a);

	insert(&float64ChnTable,5U,4.5d,a);

	printf("%d,%F\n",
			get(float64ChnTable[5U]).get_key(),
			get(float64ChnTable[5U]).get_val());

	printf("cache_shutdown\n");
	cache_shutdown();

	return 0;
}
