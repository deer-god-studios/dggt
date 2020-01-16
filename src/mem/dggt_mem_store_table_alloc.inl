
#include "defines/dggt_defines.h"
namespace dggt
{
	static const flag32 STORE_TABLE_EMPTY=0;
	static const flag32 STORE_TABLE_OCCUPIED=1;
	static const flag32 STORE_TABLE_DELETED=2;

	namespace dggt_internal_
	{
		static const u32 LARGE_PRIME32=2'038'074'743;
		static const u64 LARGE_PRIME64=19'957'072'636'091;

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
				allocator<alloc_t::STORE_TABLE,TABLESIZE>* alloc,
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
				if (alloc->flagTable[hashTrial]==STORE_TABLE_EMPTY||
						alloc->flagTable[hashTrial]==STORE_TABLE_DELETED)
				{
					result=1;
					*indexOut=hashTrial;
					break;
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		b32 store_table_hash_search(
				allocator<alloc_t::STORE_TABLE,TABLESIZE>* alloc,
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
		allocator<alloc_t::STORE_TABLE>* get_store_alloc(
				allocator<alloc_t::STORE_TABLE,TABLESIZE>* alloc,u32 index)
		{
			allocator<alloc_t::STORE_TABLE>* result=0;
			if (alloc)
			{
				flag32 f=alloc->flagTable[index];
				if (f==STORE_TABLE_OCCUPIED)
				{
					result=
						(allocator<alloc_t::STORE_TABLE>*)alloc->storeTable+index;
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		allocator<alloc_t::STORE>* search_store_table_alloc(
				allocator<alloc_t::STORE_TABLE,TABLESIZE>* alloc,
				msize size)
		{
			allocator<alloc_t::STORE>* result=0;

			if (alloc&&size)
			{
				u32 i=0;
				if (store_table_hash_search<TABLESIZE>(alloc,size,&i))
				{
					result=get_store_alloc<TABLESIZE>(alloc,i); 
				}
			}
			return result;
		}

		template <u32 TABLESIZE>
		b32 insert_store_alloc(
				allocator<alloc_t::STORE_TABLE,TABLESIZE>* alloc,
				msize size)
		{
			b32 result=0;
			if (alloc)
			{
				u32 i=0;
				if (store_table_hash_insert<TABLESIZE>(alloc,size,&i))
				{
					allocator<alloc_t::STORE_TABLE>* a=
						get_store_alloc<TABLESIZE>(alloc,i);
					*a=allocator<alloc_t::STORE_TABLE>(size);
					++a->storeCount;
				}
			}
			return result;
		}
	}

	template <u32 TABLESIZE>
	allocator<alloc_t::STORE_TABLE,TABLESIZE>::allocator()
	{
		storeCount=0;
		for (u32 i=0;i<TABLESIZE;++i)
		{
			flagTable[i]=STORE_TABLE_EMPTY;
			storeTable[i]={};
		}
	}

	template <u32 TABLESIZE>
	void* allocator<alloc_t::STORE_TABLE,TABLESIZE>::alloc(msize* size)
	{
		void* result=0;
		if (size&&*size)
		{
			msize s=*size;

			allocator<alloc_t::STORE>* a=
				dggt_internal_::search_store_table_alloc<TABLESIZE>(this,s);
			if (a&&a->blockSize==s&&
					a->available_mem())
			{
				result=a->alloc();
			}
		}
		return result;
	}

	template <u32 TABLESIZE>
	blk<void> allocator<alloc_t::STORE_TABLE,TABLESIZE>::alloc(msize size)
	{
		void* ptr=alloc(&size);
		return blk<void>(ptr,size);
	}

	template <u32 TABLESIZE>
	template <typename T>
	blk<T> allocator<alloc_t::STORE_TABLE,TABLESIZE>::alloc(u32 count)
	{
		blk<T> result=blk<T>();
		if (count)
		{
			msize s=count*sizeof(T);
			result=(blk<T>)alloc(s);
		}
		return result;
	}

	template <u32 TABLESIZE>
	template <typename T>
	T* allocator<alloc_t::STORE_TABLE,TABLESIZE>::alloc(u32* count)
	{
		T* result=0;
		if (count&&*count)
		{
			u32 c=*count;
			blk<T> b=alloc(c);
			result=b.mem;
			*count=b.count;
		}
		return result;
	}

	template <u32 TABLESIZE>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::free(void* ptr,msize size)
	{
		b32 result=0;
		if (ptr&&owns(blk<void>(ptr,size)))
		{
			u32 i=0;
			if (dggt_internal_::store_table_hash_insert<TABLESIZE>(
						this,size,&i))
			{
				if (dggt_internal_::insert_store_alloc<TABLESIZE>(this,size))
				{
					allocator<alloc_t::STORE>* storeAlloc=
						dggt_internal_::search_store_table_alloc<TABLESIZE>(
								this,size);
					ASSERT(storeAlloc);
					storeAlloc->free(ptr);
				}
			}
		}
		return result;
	}

	template <u32 TABLESIZE>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::free(blk<void> block)
	{
		return free(block.mem,block.size);
	}

	template <u32 TABLESIZE>
	template <typename T>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::free(T* ptr,u32 count)
	{
		b32 result=1;
		while (count)
		{
			result=result&&free((void*)ptr,sizeof(T));
			--count;
			if (!result)
			{
				break;
			}
		}
		return result;
	}

	template <u32 TABLESIZE>
	template <typename T>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::free(blk<T> block)
	{
		return free(block.mem,block.count);
	}

	template <u32 TABLESIZE>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::owns(const void* ptr) const
	{
		return storeCount<TABLESIZE; 
	}

	template <u32 TABLESIZE>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::owns(
			const blk<void> block) const
	{
		return owns(block.mem);
	}

	template <u32 TABLESIZE>
	template <typename T>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::owns(
			const T* ptr) const
	{
		return owns((void*)ptr);
	}

	template <u32 TABLESIZE>
	template <typename T>
	b32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::owns(
			const blk<T> block) const
	{
		return owns(block.mem);
	}

	template <u32 TABLESIZE>
	msize allocator<alloc_t::STORE_TABLE,TABLESIZE>::available_mem() const
	{
		return MAX_MSIZE; // TODO: this shit.
	}

	template <u32 TABLESIZE>
	msize allocator<alloc_t::STORE_TABLE,TABLESIZE>::used_mem() const
	{
		return 0;
	}

	template <u32 TABLESIZE>
	u32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::available_blocks() const
	{
		return MAX_UINT32;
	}
	template <u32 TABLESIZE>
	u32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::used_blocks() const
	{
		return 0;
	}
}

