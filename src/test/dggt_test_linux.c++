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

template <typename A>
void test_array(A* a)
{
	array<int> intArr=create_array<int>(a);

	for (u32 i=0;i<16;++i)
	{
		push(intArr,(int)i,a);
	}
	pop(intArr,a);
	u32 i=0;
	for (array<int>::iter it=peek(intArr);!it.is_begin();--it)
	{
		int arrVal=*it;
		printf("intArr[%d]: %d\n",i,arrVal);
		++i;
	}
	destroy_array(intArr,a);
}

template <typename A>
void test_sllist(A* a)
{
	sllist<float32> floatList=create_sllist<float32>(a);
	printf("count: %d\n",get_count(floatList));
	for (u32 i=0;i<16;++i)
	{
		push(floatList,i/7.6f,a);
	}

	pop(floatList,a);

	u32 i=0;
	for (sllist<float32>::iter it=get_iter(floatList);!it.is_end();++it)
	{
		printf("floatList[%d]: %f\n",i,*it);
		++i;
	}
	destroy_sllist(floatList,a);
}

void test_starray()
{
	starray<float64,32> fl64Starr=create_starray<float64,32>();

	for (u32 i=0;i<32;++i)
	{
		push(fl64Starr,i/3.14);
	}
	u32 i=0;
	for (starray<float64,32>::iter it=get_iter(fl64Starr);!it.is_end();++it)
	{
		printf("fl64Starr[%d]: %f\n",i,*it);
		++i;
	}
}

int main(int argc, char* argv[])
{
	printf("cache_init\n");
	cache_init(GB(2));

	free_alloc a_=free_alloc(cache_malloc(KB(8)),KB(8));
	free_alloc* a=&a_;

//	test_array(a);
//	test_sllist(a);
//	test_starray();

	dllist<ubyte> ubytList=create_dllist<ubyte>(a);

	for (u32 i=0;i<5;++i)
	{
		push(ubytList,(ubyte)4,a);
	}

	for (dllist<ubyte>::iter it=get_iter(ubytList);!it.is_end();++it)
	{
		printf("%d\n",*it);
	}

	destroy_dllist(ubytList,a);

	printf("cache_shutdown\n");
	cache_shutdown();

	return 0;
}
