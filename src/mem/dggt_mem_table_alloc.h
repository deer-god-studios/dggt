#ifndef _DGGT_MEM_TABLE_ALLOC_H_

#include "dggt_mem_store_alloc.h"

namespace dggt
{
	global constexpr msize DEF_TABLESIZE=4096;
	global const flag32 STORE_TABLE_EMPTY=0;
	global const flag32 STORE_TABLE_OCCUPIED=1;
	global const flag32 STORE_TABLE_DELETED=2;

	template <msize TABLESIZE=DEF_TABLESIZE>
	struct table_alloc:
		allocator
	{
		flag32 flagTable[TABLESIZE];
		store_alloc storeTable[TABLESIZE];
		msize availableMem;
		u32 storeCount;

		table_alloc():
			allocator(0),availableMem(0),
			storeCount(0)
		{
			for (msize i=0;i<TABLESIZE;++i)
			{
				flagTable[i]=STORE_TABLE_EMPTY;
				storeTable[i]=store_alloc(0);
			}
			availableMem=0;
			storeCount=0;
		}
	};

	template <msize TABLESIZE>
	void* malloc(table_alloc<TABLESIZE>* a,msize size);

	template <msize TABLESIZE>
	vpage malloc_vpage(table_alloc<TABLESIZE>* a,msize size);

	template <msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,void* ptr,msize size);

	template <msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,vpage& pge);

	template <msize TABLESIZE>
	b32 clear(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const void* ptr,msize size);

	template <msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const vpage& pge);

	template <msize TABLESIZE>
	stack_state save_stack(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	b32 restore_stack(table_alloc<TABLESIZE>* a,stack_state state);

	template <msize TABLESIZE>
	b32 is_stack_balanced(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize get_used(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize get_available(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	msize get_capacity(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	vpage get_buff(table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	const vpage get_buff(const table_alloc<TABLESIZE>* a);

	template <msize TABLESIZE>
	void* get_buff_ptr(table_alloc<TABLESIZE>* a);

	const void* get_buff_ptr(const allocator* a);

	template <typename T,msize TABLESIZE>
	T* malloc(table_alloc<TABLESIZE>* a,msize size=1)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,msize TABLESIZE>
	page<T> malloc_page(table_alloc<TABLESIZE>* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T,msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,T* ptr,msize size=1)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,page<T>& pge)
	{
		return free(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
	
	template <typename T,msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,page<T>& pge)
	{
		return owns(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
}

#include "dggt_mem_table_alloc.inl"

#define _DGGT_MEM_TABLE_ALLOC_H_
#endif
