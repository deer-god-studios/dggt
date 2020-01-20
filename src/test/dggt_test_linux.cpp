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

	linked_list<float32> list=create_linked_list<float32>();
	push(&list,1.24f,linAlloc);
	push(&list,2.354f,linAlloc);
	push(&list,5.24f,linAlloc);

	for (list_iter<float32> it=get_iter(&list);!it.is_end();it.next())
	{
		printf("\n%f\n",it.get());
	}

	while (get_count(&list))
	{
		list_iter<float32> popResult=pop(&list,storeTableAlloc);
		printf("\nis_mem_valid(): %d\n",is_mem_valid(popResult));
		if (is_mem_valid(popResult))
		{
			if (!is_end(popResult))
			{
				printf("\nnext to pop: %f\n",popResult.get());
			}
			else
			{
				printf("\niterator points to nothing.\n");
			}
		}
	}

	stack<float32> stackF32=create_stack<float32>(linAlloc);

	push(&stackF32,2.5f,linAlloc);
	push(&stackF32,70.25f,linAlloc);
	while (get_count(&stackF32))
	{
		printf("\n%f\n",peek(&stackF32).get());
		pop(&stackF32,(lin_alloc<>*)0);
	}

	queue<float32> queueF32=create_queue<float32>(linAlloc);
	enqueue(&queueF32,75.0f,linAlloc);
	enqueue(&queueF32,5.5f,linAlloc);

	printf("\n%f\n",queueF32[0]);
	printf("\n%f\n",queueF32[1]);

	cache_shutdown();

	return 0;
}
