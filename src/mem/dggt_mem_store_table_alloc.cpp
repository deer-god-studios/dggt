#include "dggt_mem_store_table_alloc.h"

namespace dggt
{
	static const flag32 STORE_TABLE_EMPTY=0;
	static const flag32 STORE_TABLE_OCCUPIED=1;
	static const flag32 STORE_TABLE_DELETED=2;

	namespace dggt_internal_
	{
		template <u32 TABLESIZE>
		u32 store_table_hash0(u32 sizeKey)
		{
			u32 a=5;
			u32 b=11;
			return ((a*sizeKey+b)%LARGE_PRIME32)%TABLESIZE;
		}

		template <u32 TABLESIZE>
		u32 store_table_hash1(u32 sizeKey)
		{
			return (store_table_hash0<TABLESIZE>(sizeKey)>>1)<<1;
		}

		template <u32 TABLESIZE>
		u32 store_table_hash(u32 sizeKey,u32 trial)
		{
			return store_table_hash0<TABLESIZE>(sizeKey)+
				trial*store_table_hash1<TABLESIZE>(sizeKey);
		}

		template <u32 TABLESIZE>
		b32 store_table_hash_insert(
				store_table_alloc<TABLESIZE>* alloc,
				msize size,u32* indexOut)
		{
			b32 result=0;
			ASSERT(alloc&&indexOut);
			u32 sizeKey=(u32)size; // TODO: fix
			u32 trial=0;
			u32 hashTrial=0;
			hashTrial=store_table_hash<TABLESIZE>(sizeKey,trial++);
			if (alloc->flagTable[hashTrial]==STORE_TABLE_EMPTY||
					alloc->flagTable[hashTrial]==STORE_TABLE_DELETED)
			{
				result=1;
				*indexOut=hashTrial;
			}
			while (trial<TABLESIZE&&
					alloc->flagTable[hashTrial]==STORE_TABLE_OCCUPIED)
			{
				if (alloc->flagTable[hashTrial]==STORE_TABLE_EMPTY||
						alloc->flagTable[hashTrial]==STORE_TABLE_DELETED)
				{
					result=1;
					*indexOut=hashTrial;
					break;
				}
				hashTrial=store_table_hash<TABLESIZE>(sizeKey,trial++);
			}
			return result;
		}

		template <u32 TABLESIZE>
		b32 store_table_hash_search(
				store_table_alloc<TABLESIZE>* alloc,
				msize size,u32* indexOut)
		{
			b32 result=0;
			ASSERT(alloc&&indexOut);
			u32 sizeKey=(u32)size; // TODO: fix
			u32 trial=0;
			u32 hashTrial=0;
			for (u32 trial=0;trial<TABLESIZE;++trial)
			{
				hashTrial=store_table_hash<TABLESIZE>(sizeKey,trial);
				if (alloc->flagTable[hashTrial]==STORE_TABLE_OCCUPIED)
				{
					result=1;
					*indexOut=hashTrial;
					break;
				}
				else if (alloc->flagTable[hashTrial]==STORE_TABLE_EMPTY)
				{
					result=0;
					break;
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		store_alloc<>* get_store_alloc(
				store_table_alloc<TABLESIZE>* alloc,u32 index)
		{
			store_alloc<>* result=0;
			if (alloc)
			{
				result=
					(store_alloc<>*)alloc->storeTable+index;
			}
			return result;
		}

		template <u32 TABLESIZE>
		store_alloc<>* search_store_table_alloc(
				store_table_alloc<TABLESIZE>* alloc,
				msize size)
		{
			store_alloc<>* result=0;

			if (alloc&&size)
			{
				u32 i=0;
				if (store_table_hash_search<TABLESIZE>(alloc,size,&i))
				{
					result=get_store_alloc(alloc,i); 
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		b32 insert_store_alloc(
				store_table_alloc<TABLESIZE>* alloc,
				msize size)
		{
			b32 result=0;
			if (alloc)
			{
				u32 i=0;
				if (store_table_hash_insert<TABLESIZE>(alloc,size,&i))
				{
					store_alloc<>* a=
						get_store_alloc(alloc,i);
					*a=store_alloc<>(size);
					++alloc->storeCount;
					alloc->flagTable[i]=STORE_TABLE_OCCUPIED;
					result=1;
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		b32 clear_store_table(store_table_alloc<TABLESIZE>* a)
		{
			b32 result=0;
			if (a)
			{
				for (u32 i=0;i<TABLESIZE;++i)
				{
					store_alloc<>* storeAlloc=
						get_store_alloc(a,i);
					if (available_mem(storeAlloc))
					{
						clear(storeAlloc);
					}
				}
			}
			return result;
		}
	}
}
