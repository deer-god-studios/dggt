
namespace dggt
{
	allocator<ALLOC_T_STORE,u32 BLOCKSIZE>::allocator()
	{
		init_member_if(this,0);
		head=0;
		blockCount=0;
	}

	allocator<ALLOC_T_STORE,u32 BLOCKSIZE>::allocator(u32 blockSize)
		:allocator();
	{
		u32 bsize=max<u32>(blockSize,sizeof(store_block));
		init_member_if(this,bsize);
	}

	blk<void> allocator<alloc_t::STORE>::alloc()
	{

	}

	b32 allocator<alloc_t::STORE>::free(blk<void> block)
	{
		b32 result=0;
		if (owns(block))
		{
			store_block* newBlock=(store_block*)block.mem;
			newBlock->next=head;
			head=newBlock;
			++blockCount;
			result=1;
		}
		return result;
	}

	b32 allocator<alloc_t::STORE>::free(void* ptr,msize size)
	{
		b32 result=1;
		if (size)
		{
			u32 blockCount=size/blockSize;
			for (u32 i=0;i<blockCount;++i)
			{
				result=result&&free(blk<void>(ptr,blockSize));
			}
		}
		else
		{
			result=free(blk<void>(ptr,blockSize));
		}
		return result;
	}

	b32 allocator<alloc_t::STORE>::owns(const void* ptr) const
	{
		return 1;
	}
	b32 allocator<alloc_t::STORE>::owns(const blk<void> block) const
	{
		return owns(block.mem)&&
			block.size==blockSize;
	}

	msize allocator<alloc_t::STORE>::available_mem() const
	{
		return blockCount*blockSize;
	}

	msize allocator<alloc_t::STORE>::used_mem() const
	{
		if (blockCount)
		{
			return 0;
		}
		else
		{
			return MAX_MSIZE;
		}
	}

	u32 allocator<alloc_t::STORE>::available_blocks() const
	{
		return blockCount;
	}

	u32 allocator<alloc_t::STORE>::used_blocks() const
	{
		if (blockCount)
		{
			return 0;
		}
		else
		{
			return MAX_UINT32;
		}
	}

	template <typename T>
	blk<T> allocator<alloc_t::STORE>::alloc()
	{
		blk<T> result=NULL_BLK<T>;
		if (head)
		{
			result=blk<T>((T*)head,sizeof(T));
			--blockCount;
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::free(T* ptr,u32 count)
	{
		b32 result=1;
		for (u32 i=0;i<count;++i)
		{
			result=result&&free(blk<T>(ptr,1));
		}
		return result;
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::free(blk<T> block)
	{
		return free(blk<void>(block));
	}

	template <typename T>
	b32 allocator<alloc_t::STORE>::owns(const T* ptr) const
	{
		return sizeof(T)==blockSize;
	}
	
	template <typename T>
	b32 allocator<alloc_t::STORE>::owns(const blk<T> block) const
	{
		return owns(block.mem)&&
			block.count==1;
	}

	template <u32 BLOCKSIZE>
	void* alloc(store_alloc<BLOCKSIZE>* a,msize* size)
	{
		void* result=0;

		if (head)
		{
			if (size)
			{
				*size=get_block_size(a);
			}
			result=(void*)head;
			head=head->next;
			--a->blockCount;
		}
		return result;
	}

	template <u32 BLOCKSIZE>
	blkv alloc(store_alloc<BLOCKSIZE>* a,msize size)
	{
		blkv result=blkv();
		result.mem=alloc(a,&size);
		result.size=size;
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	T* alloc(store_alloc<BLOCKSIZE>* a,u32* count)
	{
		T* result=0;
		u32 c=count?*count:1;
		msize size=sizeof(T)*c;
		result=(T*)alloc(a,&size);
		if (count)
		{
			*count=size/sizeof(T);
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	blk<T> alloc(store_alloc<BLOCKSIZE>* a,u32 count)
	{
		blk<T> result=blk<T>();
		result.mem=alloc(a,&count);
		result.count=count;
		return result;
	}

	template <u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,void* ptr,msize size)
	{
		b32 result=0;
		if (size<get_block_size(a))
		{
			size=get_block_size(a);
		}
		if (owns(ptr,size))
		{
			store_block* newBlock=(store_block*)ptr;
			newBlock->next=a->head;
			a->head=newBlock;
			++a->blockCount;
			result=1;
		}
		return result;
	}

	template <u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,blkv block)
	{
		return free(a,block.mem,block.size);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,blk<T> block)
	{
		return free(a,block.mem,block.count);
	}

	template <u32 BLOCKSIZE>
	b32 clear(store_alloc<BLOCKSIZE>* a)
	{
		a->head=0;
		a->blockCount=0;
	}

	template <u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const void* ptr,msize size)
	{
		return size<=get_block_size(a);
	}

	template <u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const blkv block)
	{
		return owns(a,block.mem,block.size);
	}

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,count*sizeof(T));
	}

	template <typename T,u32 BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const blk<T> block)
	{
		return owns(a,block.mem,block.count);
	}

	template <u32 BLOCKSIZE>
	msize available_mem(const store_alloc<BLOCKSIZE>* a)
	{
		return (msize)get_block_size(a)*a->blockCount;
	}
	
	template <u32 BLOCKSIZE>
	msize used_mem(const store_alloc<BLOCKSIZE>* a)
	{
		return available_mem(a)?0:MAX_MSIZE;
	}

	template <u32 BLOCKSIZE>
	stack_state save_stack(store_alloc<BLOCKSIZE>* a)
	{
		return SAVE_STACK_FAIL;
	}

	template <u32 BLOCKSIZE>
	b32 restore_stack(store_alloc<BLOCKSIZE>* a,stack_state state)
	{
		return 0;
	}

	template <u32 BLOCKSIZE>
	b32 is_stack_balanced(store_alloc<BLOCKSIZE>* a)
	{
		return 1;
	}

	template <u32 BLOCKSIZE>
	u32 get_block_size(store_alloc<BLOCKSIZE>* a)
	{
		return get_member_if(a);
	}
}
