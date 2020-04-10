
namespace dggt
{
	namespace dggt_internal_
	{
		template <msize BLOCKSIZE>
		void* pool_alloc(pool_block** pool,msize* used)
		{
			void* result=0;
			if (*pool)
			{
				result=*pool;
				*pool=(*pool)->next;
				*used+=BLOCKSIZE;
			}
			return result;
		}

		template <msize BLOCKSIZE>
		b32 pool_owns(const void* buff,msize buffSize,
				const void* ptr,msize size)
		{
			return ptr>=buff&&
				ptr_add(ptr,size)<=ptr_add(buff,buffSize)&&
				size==BLOCKSIZE;
		}

		template <msize BLOCKSIZE>
		b32 pool_free(pool_block** pool,
				void* buff,msize buffSize,
				msize* used,void* ptr,msize size)
		{
			b32 result=false;
			if (pool_owns<BLOCKSIZE>(buff,buffSize,ptr,size))
			{
				pool_block* newBlock=(pool_block*)ptr;
				newBlock->next=*pool;
				*pool=newBlock;
				*used-=BLOCKSIZE;
				result=true;
			}
			return result;
		}

		template <msize BLOCKSIZE>
		void pool_init(pool_block** pool,void* buff,msize buffSize,
				u32* blockCount,msize* used)
		{
			*used=0;
			*blockCount=(u32)(buffSize/BLOCKSIZE);
			*pool=(pool_block*)buff;
			for (u32 i=0;i<*blockCount;++i)
			{
				pool_block* current=*pool+i;
				current->next=
					i==*blockCount-1?0:current+1;
			}
		}
	}

	template <msize BLOCKSIZE>
	pool_alloc<BLOCKSIZE>::pool_alloc()
	{
		buff=0;
		buffSize=0;
		used=0;
		blockCount=0;
		pool=0;
	}

	template <msize BLOCKSIZE>
	pool_alloc<BLOCKSIZE>::pool_alloc(void* ptr,msize size)
	: pool_alloc()
	{
		buff=ptr;
		buffSize=size;
		dggt_internal_::pool_init<BLOCKSIZE>(&pool,buff,buffSize,&blockCount,
				&used);
	}

	template <msize BLOCKSIZE>
	void* malloc(pool_alloc<BLOCKSIZE>* a,msize size)
	{
		return dggt_internal_::pool_alloc<BLOCKSIZE>(&a->pool,&a->used);
	}

	template <msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,void* ptr,msize size)
	{
		return dggt_internal_::pool_free<BLOCKSIZE>(
				&a->pool,a->buff,a->buffSize,
				&a->used,ptr,size);
	}
	
	template <msize BLOCKSIZE>
	b32 clear(pool_alloc<BLOCKSIZE>* a)
	{
		dggt_internal_::pool_init<BLOCKSIZE>(
				&a->pool,a->buff,a->buffSize,&a->blockCount,&a->used);
		return true;
	}

	template <msize BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const void* ptr,msize size)
	{
		return dggt_internal_::pool_owns<BLOCKSIZE>(
				a->buff,a->buffSize,ptr,size);
	}

	template <msize BLOCKSIZE>
	stack_state save_stack(pool_alloc<BLOCKSIZE>* a)
	{
		return SAVE_STACK_FAIL;
	}

	template <msize BLOCKSIZE>
	b32 restore_stack(pool_alloc<BLOCKSIZE>* a,stack_state state)
	{
		return false;
	}

	template <msize BLOCKSIZE>
	b32 is_stack_balanced(const pool_alloc<BLOCKSIZE>* a)
	{
		return true;
	}

	template <msize BLOCKSIZE>
	msize used_mem(const pool_alloc<BLOCKSIZE>* a)
	{
		return a->used;
	}

	template <msize BLOCKSIZE>
	msize available_mem(const pool_alloc<BLOCKSIZE>* a)
	{
		return a->buffSize-a->used;
	}

	template <typename T,msize BLOCKSIZE>
	T* malloc(pool_alloc<BLOCKSIZE>* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,msize BLOCKSIZE>
	b32 free(pool_alloc<BLOCKSIZE>* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,msize BLOCKSIZE>
	b32 owns(const pool_alloc<BLOCKSIZE>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	T* malloc(pool_alloc<>* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T>
	b32 free(pool_alloc<>* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T>
	b32 owns(const pool_alloc<>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}
}
