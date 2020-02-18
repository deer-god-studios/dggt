
namespace dggt
{
	namespace dggt_internal_
	{
		template <u32 BLOCKSIZE>
		u32 get_block_size(pool_allocator<BLOCKSIZE>* a)
		{
			return BLOCKSIZE?BLOCKSIZE:ifBlockSize;
		}
	}

	template <u32 BLOCKSIZE>
	struct pool_block<BLOCKSIZE>::pool_block()
	: next((pool_block<BLOCKSIZE>*)0) { }

	template <u32 BLOCKSIZE>
	struct pool_block<BLOCKSIZE>::pool_block(msize blockSize)
	: pool_block(), ifblockSize(0) { }

	template <u32 BLOCKSIZE>
	allocator<ALLOC_T_POOL,BLOCKSIZE>::allocator()
	: buff(blk<void>()), used(0),pool((pool_block<BLOCKSIZE>*)0) { }

	template <u32 BLOCKSIZE>
	allocator<ALLOC_T_POOL,BLOCKSIZE>::allocator(void* ptr,msize size,
			msize blockSize)
	: allocator()
	{
		buff.mem=ptr;
		buff.size=size;
		pool->next=0;
		init_u32_or<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
				blockSize,&ifBlockSize);
		init_u32_or<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
				ifBlockSize,&pool->ifBlockSize);
		
		if (blockSize<sizeof(pool_block))
		{
			blockSize=sizeof(pool_block);
		}
		this->blockSize=blockSize;
		blockCount=(u32)(size/blockSize);
		pool=(pool_block<BLOCKSIZE>*)ptr;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block<BLOCKSIZE>* current=pool+i;
			init_if<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
					ifBlockSize,&current->ifBlockSize);
			current->next=
				i==blockCount-1?0:current+1;
		}
	}



	b32 allocator<alloc_t::POOL>::free(blk<void> block)
	{
		b32 result=0;
		if (owns(block))
		{
			result=free(block.mem);
		}
		return result;
	}

	b32 allocator<alloc_t::POOL>::clear()
	{
		pool=(pool_block*)buff.mem;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block* current=pool+i;
			pool->next=i==blockCount-1?0:current+1;

		}
		used=0;
		blocksUsed=0;
		return 1;
	}

	b32 allocator<alloc_t::POOL>::owns(const void* ptr) const
	{
		return ptr>=buff.mem&&ptr<=ptr_add(buff.mem,buff.size);
	}

	b32 allocator<alloc_t::POOL>::owns(const blk<void> block) const
	{
		return owns(block.mem)&&
			ptr_add(block.mem,block.size)<=
			ptr_add(buff.mem,buff.size);
	}

	msize allocator<alloc_t::POOL>::available_mem() const
	{
		return buff.size-used;
	}

	msize allocator<alloc_t::POOL>::used_mem() const
	{
		return used;
	}

	u32 allocator<alloc_t::POOL>::available_blocks() const
	{
		return blockCount-blocksUsed;
	}

	u32 allocator<alloc_t::POOL>::used_blocks() const
	{
		return blocksUsed;
	}

	template <u32 BLOCKSIZE>
	void* alloc(pool_alloc<BLOCKSIZE>* a,msize* size)
	{
		void* result;
		if (pool)
		{
			result=pool;
			if (size)
			{
				*size=dggt_internal_::get_block_size(a);
			}
			pool=pool->next;
			used+=dggt_internal_::get_block_size(a);
		}
		return result;
	}

	template <u32 BLOCKSIZE>
	blkv alloc(pool_alloc<BLOCKSIZE>* a,msize size)
	{
		blkv result=blkv();
		void* ptr=alloc(a,&size);
		result.mem=ptr;
		result.size=size;
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	T* alloc(pool_alloc<BLOCKSIZE>* a,u32* count)
	{
		T* result=0;
		if (sizeof(T)<=dggt_internal_::get_block_size(a))
		{
			if (count)
			{
				// TODO: handle count better.
				*count=1;
			}
			msize size=sizeof(T);
			result=(T*)alloc(a,&size);
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	blk<T> alloc(pool_alloc<BLOCKSIZE>* a,u32 count)
	{
		blk<T> result=0;
		T* ptr=alloc(a,&count);
		result.mem=ptr;
		result.count=count;
		return result;
	}

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,void* ptr,msize size)
	{
		b32 result=0;
		if (owns(a,ptr,size))
		{
			pool_block<BLOCKSIZE>* newBlock=(pool_block<BLOCKSIZE>*)ptr;
			init_if<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
					blockSize,&newBlock->ifBlockSize);
			newBlock->next=pool;
			pool=newBlock;
			used-=blockSize;
			result=1;
		}
		return result;
	}

	template <u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,blkv block)
	{
		return free(a,block.mem,block.size);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,T* ptr,u32 count)
	{
		b32 result=0;
		u32 blockSize=dggt_internal_::get_block_size(a);
		if (sizeof(T)<=blockSize)
		{
			result=free(a,ptr,(msize)blockSize);
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,blk<T> block)
	{
		return free(a,block.mem,block.count);
	}

	template <u32 BLOCKSIZE>
	b32 clear(pool_alloc<BLOCKSIZE>* a)
	{
		pool->next=0;
		init_if<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
				ifBlockSize,&pool->ifBlockSize);

		blockCount=(u32)(size/blockSize);
		pool=(pool_block<BLOCKSIZE>*)ptr;
		for (u32 i=0;i<blockCount;++i)
		{
			pool_block<BLOCKSIZE>* current=pool+i;
			init_if<BLOCKSIZE==NO_BLOCKSIZE,BLOCKSIZE>(
					ifBlockSize,&current->ifBlockSize);
			current->next=
				i==blockCount-1?0:current+1;
	}

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const void* ptr,msize size)
	{
		return size<=dggt_internal_::get_block_size(a)&&
			intvl(ptr,buff.mem,ptr_add(buff.mem,buff.size))&&
			intvl(ptr_add(ptr,size),buff.mem,ptr_add(buff.mem,buff.size));
	}

	template <u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const blkv block)
	{
		return owns(a,block.mem,block.size);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	template <u32 BLOCKSIZE>
	msize available_mem(const pool_alloc<BLOCKSIZE>* a)
	{
		return buff.size-used;
	}
	
	template <u32 BLOCKSIZE>
	msize used_mem(const pool_alloc<BLOCKSIZE>* a)
	{
		return used;
	}

	template <u32 BLOCKSIZE>
	stack_state save_stack(pool_alloc<BLOCKSIZE>* a)
	{
		return SAVE_STACK_FAIL;
	}

	template <u32 BLOCKSIZE>
	b32 restore_stack(pool_alloc<BLOCKSIZE>* a,stack_state state)
	{
		return 0;
	}

	template <u32 BLOCKSIZE>
	b32 is_stack_balanced(pool_alloc<BLOCKSIZE>* a)
	{
		return 1;
	}

	// pool_stalloc<SIZE>


	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	allocator<ALLOC_T_POOL,BLOCKSIZE,BUFFSIZE>::allocator(msize blockSize)
	{
		a_=pool_alloc<ALLOC_T_POOL,BLOCKSIZE>(
				(void*)buff,BUFFSIZE,blockSize);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	void* alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,msize* size)
	{
		return alloc(&a->a_,size);
	}
	
	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	blkv alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,msize size)
	{
		return alloc(&a->a_,size);
	}

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	T* alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,u32* count)
	{
		return alloc(&a->a_,count);
	}
	
	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	blk<T> alloc(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,u32 count)
	{
		return alloc(&a->a_,count);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,void* ptr,msize size)
	{
		return free(&a->a_,ptr,size);
	}
	
	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,blkv block)
	{
		return free(&a->a_,block);
	}

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,T* ptr,u32 count)
	{
		return free(&a->a_,ptr,count);
	}

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 free(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,blk<T> block)
	{
		return free(&a->a_,block);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 clear(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a)
	{
		return clear(&a->a_);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,
			const void* ptr,msize size)
	{
		return owns(&a->a_,ptr,size);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const blkv block)
	{
		return owns(&a->a_,block);
	}

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const T* ptr,u32 count)
	{
		return owns(&a->a_,ptr,count);
	}

	template <typename T,u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 owns(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,const blk<T> block)
	{
		return owns(&a->a_,block);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	msize available_mem(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a)
	{
		return available_mem(&a->a_);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	msize used_mem(const pool_stalloc<BLOCKSIZE,BUFFSIZE>* a)
	{
		return used_mem(&a->a_);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	stack_state save_stack(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a)
	{
		return save_stack(&a->a_);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 restore_stack(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a,stack_state state)
	{
		return restore_stack(&a->a_,state);
	}

	template <u32 BLOCKSIZE,u32 BUFFSIZE>
	b32 is_stack_balanced(pool_stalloc<BLOCKSIZE,BUFFSIZE>* a)
	{
		return is_stack_balanced(&a->a_);
	}
}
