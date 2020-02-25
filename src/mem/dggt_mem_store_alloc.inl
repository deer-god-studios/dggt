
namespace dggt
{
	namespace dggt_internal_
	{
		template <msize BLOCKSIZE>
		void* store_alloc(store_block** head,
				u32* blockCount,msize size)
		{
			void* result=0;
			if (*head)
			{
				result=*head;
				*head=*head->next;
				++*blockCount;
			}
			return result;
		}

		template <msize BLOCKSIZE>
		b32 store_owns(void* ptr,msize size)
		{
			return size==BLOCKSIZE;
		}

		template <msize BLOCKSIZE>
		b32 store_free(store_block** head,u32* blockCount,
				void* ptr,msize size)
		{
			b32 result=false;
			if (store_owns<BLOCKSIZE>(ptr,size))
			{
				store_block* newBlock=(store_block*)ptr;
				newBlock->next=*head;
				*head=newBlock;
				++*blockCount;
				result=true;
			}
			return result;
		}

		template <msize BLOCKSIZE>
		b32 store_clear(store_block** head,u32* blockCount)
		{
			*head=0;
			*blockCount=0;
		}

		template <msize BLOCKSIZE>
		msize store_used_mem(u32 blockCount)
		{
			return blockCount?0:MAX_MSIZE;
		}

		template <msize BLOCKSIZE>
		msize store_available_mem(u32 blockCount)
		{
			return (msize)blockCount*BLOCKSIZE;
		}
	}

	template <msize BLOCKSIZE>
	store_alloc<BLOCKSIZE>::store_alloc()
	{
		baseAlloc(allocator<BLOCKSIZE>(ALLOC_T_STORE));
		head=0;
		blockCount=0;
	}

	template <msize BLOCKSIZE>
	void* alloc(store_alloc<BLOCKSIZE>* a,msize size)
	{
		return dggt_internal_::store_alloc<BLOCKSIZE>(&a->head,
				&a->blockCount,size);
	}

	template <msize BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,void* ptr,msize size)
	{
		return dggt_internal_::store_free<BLOCKSIZE>(&a->head,&a->blockCount,
				ptr,size);
	}
	
	template <msize BLOCKSIZE>
	b32 clear(store_alloc<BLOCKSIZE>* a)
	{
		return dggt_internal_::store_clear<BLOCKSIZE>(&a->head,&a->blockCount);
	}

	template <msize BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const void* ptr,msize size)
	{
		return dggt_internal_::store_owns<BLOCKSIZE>(ptr,size);
	}

	template <msize BLOCKSIZE>
	stack_state save_stack(store_alloc<BLOCKSIZE>* a)
	{
		return SAVE_STACK_FAIL;
	}

	template <msize BLOCKSIZE>
	b32 restore_stack(store_alloc<BLOCKSIZE>* a,stack_state state)
	{
		return false;
	}

	template <msize BLOCKSIZE>
	b32 is_stack_balanced(const store_alloc<BLOCKSIZE>* a)
	{
		return true;
	}

	template <msize BLOCKSIZE>
	msize used_mem(const store_alloc<BLOCKSIZE>* a)
	{
		return dggt_internal_::store_used_mem(a->blockCount);
	}

	template <msize BLOCKSIZE>
	msize available_mem(const store_alloc<BLOCKSIZE>* a)
	{
		return dggt_internal_::store_available_mem(a->blockCount);
	}

	template <typename T,msize BLOCKSIZE>
	T* alloc(store_alloc<BLOCKSIZE>* a,u32 count)
	{
		return (T*)alloc(a,sizeof(T)*count);
	}

	template <typename T,msize BLOCKSIZE>
	b32 free(store_alloc<BLOCKSIZE>* a,T* ptr,u32 count)
	{
		return free(a,ptr,sizeof(T)*count);
	}

	template <typename T,msize BLOCKSIZE>
	b32 owns(const store_alloc<BLOCKSIZE>* a,const T* ptr,u32 count)
	{
		return owns(a,ptr,sizeof(T)*count);
	}
}
