
#include "math/dggt_math_constants.h"

namespace dggt
{
	namespace dggt_internal_
	{
		static const flag32 STORE_TABLE_EMPTY=0;
		static const flag32 STORE_TABLE_OCCUPIED=1;
		static const flag32 STORE_TABLE_DELETED=2;

		template <msize TABLESIZE>
		b32 table_owns(u32 storeCount)
		{
			return storeCount<TABLESIZE;
		}

		template <msize TABLESIZE>
		u32 table_hash0(u32 sizeKey)
		{
			u32 a=5;
			u32 b=11;
			return ((a*sizeKey+b)%LARGE_PRIME32)%TABLESIZE;
		}

		template <msize TABLESIZE>
		u32 table_hash1(u32 sizeKey)
		{
			return ((table_hash0<TABLESIZE>(sizeKey)>>1)<<1)&1;
		}

		template <msize TABLESIZE>
		u32 table_hash(u32 sizeKey,u32 trial)
		{
			return table_hash0<TABLESIZE>(sizeKey)+
				trial*table_hash1<TABLESIZE>(sizeKey);
		}

		template <msize TABLESIZE>
		b32 table_hash_insert(
				flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				msize size,u32* indexOut)
		{
			b32 result=0;
			ASSERT(flagTable&&storeTable&&indexOut);
			u32 sizeKey=(u32)size; // TODO: fix
			u32 trial=0;
			u32 hashTrial=0;
			hashTrial=table_hash<TABLESIZE>(sizeKey,trial++);
			if (flagTable[hashTrial]==STORE_TABLE_EMPTY||
					flagTable[hashTrial]==STORE_TABLE_DELETED)
			{
				result=1;
				*indexOut=hashTrial;
			}
			while (trial<TABLESIZE&&
					flagTable[hashTrial]==STORE_TABLE_OCCUPIED)
			{
				if (flagTable[hashTrial]==STORE_TABLE_EMPTY||
						flagTable[hashTrial]==STORE_TABLE_DELETED)
				{
					result=1;
					*indexOut=hashTrial;
					break;
				}
				hashTrial=table_hash<TABLESIZE>(sizeKey,trial++);
			}
			return result;
		}

		template <msize TABLESIZE>
		b32 table_hash_search(
				flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				msize size,u32* indexOut)
		{
			b32 result=0;
			ASSERT(flagTable&&storeTable&&indexOut);
			u32 sizeKey=(u32)size; // TODO: fix
			u32 trial=0;
			u32 hashTrial=0;
			for (u32 trial=0;trial<TABLESIZE;++trial)
			{
				hashTrial=table_hash<TABLESIZE>(sizeKey,trial);
				if (flagTable[hashTrial]==STORE_TABLE_OCCUPIED)
				{
					result=1;
					*indexOut=hashTrial;
					break;
				}
				else if (flagTable[hashTrial]==STORE_TABLE_EMPTY)
				{
					result=0;
					break;
				}
			}
			return result;
		}

		template <msize TABLESIZE>
		dggt::store_alloc<>* get_store_alloc(
				dggt::store_alloc<> storeTable[TABLESIZE],
				u32 index)
		{
			dggt::store_alloc<>* result=0;
			if (storeTable)
			{
				result=
					(dggt::store_alloc<>*)storeTable+index;
			}
			return result;
		}

		template <msize TABLESIZE>
		dggt::store_alloc<>* search_table_alloc(
				flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				msize size)
		{
			dggt::store_alloc<>* result=0;

			if (flagTable&&storeTable&&size)
			{
				u32 i=0;
				if (table_hash_search<TABLESIZE>(flagTable,storeTable,size,&i))
				{
					result=get_store_alloc<TABLESIZE>(storeTable,i); 
				}
			}
			return result;
		}

		template <msize TABLESIZE>
		dggt::store_alloc<>* insert_store_alloc(
				flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				u32* storeCount,
				msize size)
		{
			dggt::store_alloc<>* result=0;
			if (storeTable&&flagTable&&storeCount)
			{
				u32 i=0;
				if (table_hash_insert<TABLESIZE>(flagTable,storeTable,size,&i))
				{
					dggt::store_alloc<>* storeAlloc=
						get_store_alloc<TABLESIZE>(storeTable,i);
					*storeAlloc=dggt::store_alloc<>(size);
					++*storeCount;
					flagTable[i]=STORE_TABLE_OCCUPIED;
					result=storeAlloc;
				}
			}
			return result;
		}

		template <msize TABLESIZE>
		b32 clear_table(flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE])
		{
			b32 result=0;
			if (flagTable&&storeTable)
			{
				for (u32 i=0;i<TABLESIZE;++i)
				{
					dggt::store_alloc<>* storeAlloc=
						get_store_alloc<TABLESIZE>(flagTable,storeTable,i);
					if (storeAlloc&&available_mem(storeAlloc))
					{
						clear(storeAlloc);
					}
				}
			}
			return result;
		}

		template <msize TABLESIZE>
		void* table_alloc(flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				msize* availableMem,
				msize size)
		{
			void* result=0;
			dggt::store_alloc<>* storeAlloc=search_table_alloc<TABLESIZE>(
					flagTable,storeTable,size);
			if (storeTable&&flagTable&&availableMem)
			{
				result=alloc(storeAlloc,size);
				*availableMem-=size;
			}
			return result;
		}

		template <msize TABLESIZE>
		b32 table_free(flag32 flagTable[TABLESIZE],
				dggt::store_alloc<> storeTable[TABLESIZE],
				msize* availableMem,u32* storeCount,
				void* ptr,msize size)
		{
			b32 result=0;
			dggt::store_alloc<>* storeAlloc=
				search_table_alloc<TABLESIZE>(flagTable,storeTable,size);
			if (storeAlloc==0)
			{
				storeAlloc=insert_store_alloc<TABLESIZE>(flagTable,storeTable,
						storeCount,size);
			}

			if (storeAlloc)
			{
				result=free(storeAlloc,ptr,size);
				*availableMem+=size;
			}
			return result;
		}
	}

	template <msize TABLESIZE>
	table_alloc<TABLESIZE>::table_alloc()
	{
		for (msize i=0;i<TABLESIZE;++i)
		{
			flagTable[i]=dggt_internal_::STORE_TABLE_EMPTY;
		}
		availableMem=0;
		storeCount=0;
	}

	template <msize TABLESIZE>
	void* alloc(table_alloc<TABLESIZE>* a,msize size)
	{
		if (a)
		{
			return dggt_internal_::table_alloc(a->flagTable,
					a->storeTable,&a->availableMem,size);
		}
		else
		{
			return 0;
		}
	}

	template <msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::table_free(a->flagTable,
					a->storeTable,&a->availableMem,ptr,size);
		}
		else
		{
			return 0;
		}
	}
	
	template <msize TABLESIZE>
	b32 clear(table_alloc<TABLESIZE>* a)
	{
		if (a)
		{
			return dggt_internal_::clear_table(a->flagTable,
					a->storeTable);
		}
		else
		{
			return 0;
		}
	}

	template <msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const void* ptr,msize size)
	{
		if (a)
		{
			return dggt_internal_::table_owns(a->storeCount);
		}
		else
		{
			return 0;
		}
	}

	template <msize TABLESIZE>
	stack_state save_stack(table_alloc<TABLESIZE>* a)
	{
		return SAVE_STACK_FAIL;
	}

	template <msize TABLESIZE>
	b32 restore_stack(table_alloc<TABLESIZE>* a,stack_state state)
	{
		return false;
	}

	template <msize TABLESIZE>
	b32 is_stack_balanced(const table_alloc<TABLESIZE>* a)
	{
		return true;
	}

	template <msize TABLESIZE>
	msize used_mem(const table_alloc<TABLESIZE>* a)
	{
		return available_mem(a)?0:MAX_MSIZE;
	}

	template <msize TABLESIZE>
	msize available_mem(const table_alloc<TABLESIZE>* a)
	{
		return a->availableMem;
	}

	template <typename T,msize TABLESIZE>
	T* alloc(table_alloc<TABLESIZE>* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T,msize TABLESIZE>
	b32 free(table_alloc<TABLESIZE>* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T,msize TABLESIZE>
	b32 owns(const table_alloc<TABLESIZE>* a,const T* ptr,u32 count)
	{
		if (a)
		{
			return dggt_internal_::table_owns(a->storeCount);
		}
		else
		{
			return false;
		}
	}
}
