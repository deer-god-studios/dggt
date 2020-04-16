#include "dggt_mem_store_alloc.h"

namespace dggt
{
	void* malloc(store_alloc* a,msize size)
	{
		void* result=0;
		if (a&&(size==a->bSize||
				size==0))
		{
			store_block* h=a->store;
			a->store=a->store->next;
			--a->bCount;
		}
		return result;
	}
	
	b32 free(store_alloc* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a&&(size==0||
				size==a->bSize))
		{
			store_block* h=(store_block*)ptr;
			h->next=a->store;
			a->store=h;
			result=true;
			++a->bCount;
		}
		return result;
	}
	
	b32 clear(store_alloc* a)
	{
		b32 result=false;
		if (a)
		{
			a->store=0;
			a->bCount=0;
		}
		return result;
	}
	
	b32 owns(const store_alloc* a,const void* ptr,msize size)
	{
		return a?ptr&&size==a->bSize:false;
	}

	msize get_used(const store_alloc* a)
	{
		return get_available(a)?0:MAX_MSIZE;
	}
	
	msize get_available(const store_alloc* a)
	{
		return a?a->bCount*a->bSize:0;
	}
}
