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
	line_break();
	printf("primary used: %u\n",alloc->p->used_mem());
	printf("primary available: %u\n", alloc->p->available_mem());
	printf("primary available blocks: %u\n", alloc->p->available_blocks());
	new_line();
	printf("fallback used: %d\n",alloc->f->used_mem());
	printf("fallback available: %d\n", alloc->f->available_mem());
	line_break();
}

void init_test()
{
	linAlloc_=create_alloc<alloc_t::LINEAR>(KB(100));
	linAlloc=&linAlloc_;
	storeTableAlloc_=create_alloc<alloc_t::STORE_TABLE,2048>();
	storeTableAlloc=&storeTableAlloc_;
	alloc_=
		create_alloc<alloc_t::STORE_TABLE,2048,alloc_t::LINEAR,0>(
				storeTableAlloc,linAlloc);
	alloc=&alloc_;
}

template <u32 BLOCKS>
void test_alloc()
{
	printf("calling test_alloc<%u>\n", BLOCKS);
	print_alloc_info();
	pause_output();
	blk<float32> blockArr[BLOCKS]={};
	for (u32 i=0;i<ARRAY_COUNT(blockArr);++i)
	{
		u32 floatCount=i+1;
		printf("allocating block of %d floats...\n",floatCount);
		blockArr[i]=alloc->alloc<float32>(floatCount);
		printf("allocated %d floats at %x.\n",
				blockArr[i].count,blockArr[i].mem);
		print_alloc_info();
	}
	pause_output();
	for (u32 i=0;i<ARRAY_COUNT(blockArr);++i)
	{
		printf("freeing a block of %d floats at %x.\n",
				blockArr[i].count,blockArr[i].mem);
		b32 freeResult=alloc->free(blockArr[i]);
		printf("free result: %d\n",freeResult);
		print_alloc_info();
	}
	pause_output();
}

void test_linked_list()
{
	INIT_PTR_TO(linked_list<float32>,float32List,create_linked_list<float32>());
	u32 float32Count=25;
	for (u32 i=0;i<float32Count;++i)
	{
		push(float32List,(float32)i/7.97f,alloc);
	}

	for (list_iter<float32> it=get_iter(float32List);!it.is_end();it.next())
	{
		printf("%f\n",it.get());
	}
	new_line();
	while (!pop(float32List,alloc).is_end())
	{
		printf("pop\n");
	}

	clear(float32List,alloc);
}

void test_stack()
{
	INIT_PTR_TO(stack<float32>,float32Stack,create_stack<float32>(alloc));

	print_alloc_info();
	pause_output();

	u32 stackCount=10;
	for (u32 i=0;i<stackCount;++i)
	{
		push(float32Stack,(float32)i,alloc);

	}

	print_alloc_info();
	pause_output();
	stackCount=get_count(float32Stack);
	printf("stack count: %u\n",stackCount);
	for (stack_iter<float32> it=get_iter(float32Stack);
			!it.is_end();it.next())
	{
		if (it.current==0)
		{
			printf("%f\n",it.get());
		}
		else
		{
			printf("%f, ",it.get());
		}
	}
	print_alloc_info();
	pause_output();
	while (!pop(float32Stack,alloc).is_end())
	{
		printf("pop ");

	}
	print_alloc_info();
	pause_output();
	new_line();
	clear(float32Stack,alloc);
	print_alloc_info();
	pause_output();
}

void test_queue()
{
	INIT_PTR_TO(queue<float32>,float32Queue,create_queue<float32>(alloc));

	u32 queueCount=50;
	for (u32 i=0;i<queueCount;++i)
	{
		enqueue(float32Queue,(float32)i,alloc);
	}
	queueCount=get_count(float32Queue);
	printf("queue count: %u\n",queueCount);
	for (queue_iter<float32> it=get_iter(float32Queue);
			!it.is_end();it.next())
	{
		if (it.current==queueCount-1)
		{
			printf("%f\n",it.get());
		}
		else
		{
			printf("%f, ",it.get());
		}
	}
	while (!dequeue(float32Queue,alloc).is_end())
	{
		printf("dequeue ");
	}
	new_line();
	clear(float32Queue,alloc);
}

void test_hash_table()
{
	PTR_TO(f32_table,float32Table);
	*float32Table=create_hash_table<u32,float32>(alloc);

	u32 tableCount=21;
	for (u32 i=0;i<tableCount;++i)
	{
		insert(float32Table,i,(float32)i/7.0f,alloc);
	}

	printf("table count: %u\n",get_count(float32Table));
	printf("key: 15, val: %f\n",search(float32Table,(u32)15).get().get_val());
	clear(float32Table,alloc);
}

int main(int argc, char* argv[])
{
	cache_init(GB(2));

	init_test();

	test_alloc<1>();
	test_alloc<2>();
	test_alloc<2>();
	test_alloc<3>();
	new_line();
	test_linked_list();
	print_alloc_info();
	pause_output();
	test_stack();
	print_alloc_info();
	pause_output();

	test_queue();
	print_alloc_info();
	pause_output();

	cache_shutdown();

	return 0;
}
