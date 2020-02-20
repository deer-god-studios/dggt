// TODO: This is all terrible.  Fix.
#include "defines/dggt_defines.h"
#include "math/dggt_math_constants.h"
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

	template <u32 TABLESIZE>
	allocator<alloc_t::STORE_TABLE,TABLESIZE>::allocator()
	{
		storeCount=0;
		availableMem=0;
		availableBlocks=0;
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
				if (result)
				{
					availableMem-=s;
					--availableBlocks;
				}
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
			blk<T> b=alloc<T>(c);
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
			if (dggt_internal_::store_table_hash_search<TABLESIZE>(
						this,size,&i))
			{
				allocator<alloc_t::STORE>* storeAlloc=
					dggt_internal_::search_store_table_alloc<TABLESIZE>(
							this,size);
				ASSERT(storeAlloc);
				result=storeAlloc->free(ptr);
				if (result)
				{
					availableMem+=size;
					availableBlocks++;
				}
			}
			else if (dggt_internal_::store_table_hash_insert<TABLESIZE>(
						this,size,&i))
			{
				if (dggt_internal_::insert_store_alloc<TABLESIZE>(this,size))
				{
					allocator<alloc_t::STORE>* storeAlloc=
						dggt_internal_::search_store_table_alloc<TABLESIZE>(
								this,size);
					ASSERT(storeAlloc);
					result=storeAlloc->free(ptr);
					if (result)
					{
						availableMem+=size;
						availableBlocks++;
					}
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
		result=free((void*)ptr,count*sizeof(T));
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
		return availableMem;
	}

	template <u32 TABLESIZE>
	msize allocator<alloc_t::STORE_TABLE,TABLESIZE>::used_mem() const
	{
		return available_mem()?0:MAX_MSIZE;
	}

	template <u32 TABLESIZE>
	u32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::available_blocks() const
	{
		return availableBlocks;
	}

	template <u32 TABLESIZE>
	u32 allocator<alloc_t::STORE_TABLE,TABLESIZE>::used_blocks() const
	{

		return available_blocks()?0:MAX_UINT32;
	}


	template <u32 TABLESIZE>
	void* alloc(store_table_alloc<TABLESIZE>* a,msize* size)
	{
		void* result=0;
		if (size&&*size)
		{
			msize s=*size;

			store_alloc<>* storeAlloc=
				dggt_internal_::search_store_table_alloc<TABLESIZE>(a,s);
			if (storeAlloc&&get_block_size(storeAlloc)==s&&
					available_mem(storeAlloc))
			{
				result=alloc(storeAlloc,s);
				if (result)
				{
					a->availableMem-=s;
					--a->blockCount;
				}
			}
		}
		return result;
	}

	template <u32 TABLESIZE>
	blkv alloc(store_table_alloc<TABLESIZE>* a,msize size)
	{
		blkv result=blkv();
		result.mem=alloc(a,&size);
		result.size=size;
		return result;
	}

	template <typename T,u32 TABLESIZE>
	T* alloc(store_table_alloc<TABLESIZE>* a,u32* count)
	{
		T* result=0;
		msize s=4;
		if (count&&*count)
		{
			s=sizeof(T)*count;
			result=alloc(a,s);
			*count=s/sizeof(T);
		}
		return result;
	}

	template <typename T,u32 TABLESIZE>
	blk<T> alloc(store_table_alloc<TABLESIZE>* a,u32 count)
	{
		blk<T> result=blk<T>();
		result.mem=alloc(a,&count);
		result.count=count;
		return result;
	}

	template <u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,void* ptr,msize size)
	{
		b32 result=0;
		if (ptr&&owns(a,ptr,size))
		{
			u32 i=0;
			if (dggt_internal_::store_table_hash_search<TABLESIZE>(
						a,size,&i))
			{
				store_alloc<>* storeAlloc=
					dggt_internal_::search_store_table_alloc<TABLESIZE>(
							a,size);
				ASSERT(storeAlloc);
				result=free(storeAlloc,ptr,size);
				if (result)
				{
					a->availableMem+=size;
					a->blockCount++;
				}
			}
			else if (dggt_internal_::store_table_hash_insert<TABLESIZE>(
						a,size,&i))
			{
				if (dggt_internal_::insert_store_alloc<TABLESIZE>(a,size))
				{
					store_alloc<>* storeAlloc=
						dggt_internal_::search_store_table_alloc<TABLESIZE>(
								a,size);
					ASSERT(storeAlloc);
					result=free(storeAlloc,ptr,size);
					if (result)
					{
						a->availableMem+=size;
						a->blockCount++;
					}
				}
			}
		}
		return result;
	}

	template <u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,blkv block)
	{
		return free(a,block.mem,block.size);
	}

	template <typename T,u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,T* ptr,u32 count)
	{
		return free(a,ptr,count*sizeof(T));
	}

	template <typename T,u32 TABLESIZE>
	b32 free(store_table_alloc<TABLESIZE>* a,blk<T> block)
	{
		return free(a,block.ptr,block.count);
	}

	template <u32 TABLESIZE>
	b32 clear(store_table_alloc<TABLESIZE>* a)
	{
		dggt_internal_::clear_store_table(a);
	}

	template <u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const void* ptr,msize size)
	{
		u32 i=0;
		b32 containsSize=dggt_internal_::store_table_hash_search(a,size,&i);
		return a->storeCount<TABLESIZE||containsSize;
	}

	template <u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const blkv block)
	{
		return owns(a,block.mem,block.size);
	}

	template <typename T,u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,count*sizeof(T));
	}

	template <typename T,u32 TABLESIZE>
	b32 owns(const store_table_alloc<TABLESIZE>* a,const blk<T> block)
	{
		return owns(a,block.ptr,block.count);
	}

	template <u32 TABLESIZE>
	msize available_mem(const store_table_alloc<TABLESIZE>* a)
	{
		return a->availableMem;
	}
	
	template <u32 TABLESIZE>
	msize used_mem(const store_table_alloc<TABLESIZE>* a)
	{
		return available_mem(a)?0:MAX_MSIZE;
	}

	template <u32 TABLESIZE>
	stack_state save_stack(store_table_alloc<TABLESIZE>* a)
	{
		return STACK_SAVE_FAIL;
	}

	template <u32 TABLESIZE>
	b32 restore_stack(store_table_alloc<TABLESIZE>* a,stack_state state)
	{
		return 0;
	}

	template <u32 TABLESIZE>
	b32 is_stack_balanced(store_table_alloc<TABLESIZE>* a)
	{
		return 1;
	}

	template <u32 TABLESIZE>
	u32 get_block_size(store_table_alloc<TABLESIZE>* a)
	{
		return NO_BLOCKSIZE;
	}
}


