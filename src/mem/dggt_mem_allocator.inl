
namespace dggt
{
	template <msize... SizeArgs>
	void* alloc(allocator<SizeArgs...>* a,msize size)
	{
		void* result=0;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=alloc((null_alloc*)a,size);
				} break;
			case ALLOC_T_LIN:
				{
					result=alloc((lin_alloc*)a,size);
				} break;
			case ALLOC_T_STACK:
				{
					result=alloc((stack_alloc*)a,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=alloc((free_alloc*)a,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=alloc((pool_alloc<SizeArgs...>*)a,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=alloc((store_alloc<SizeArgs...>*)a,size);
				} break;
			case ALLOC_T_TABLE:
				{
					result=alloc((table_alloc<SizeArgs...>*)a,size);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=alloc((fallback_alloc<SizeArgs...>*)a,size);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	b32 free(allocator<SizeArgs...>* a,void* ptr,msize size)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=free((null_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_LIN:
				{
					result=free((lin_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STACK:
				{
					result=free((stack_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=free((free_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=free((pool_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=free((store_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_TABLE:
				{
					result=free((table_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=free((fallback_alloc<SizeArgs...>*)a,ptr,size);
				} break;
		}
		return result;
	}
	
	template <msize... SizeArgs>
	b32 clear(allocator<SizeArgs...>* a)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=clear((null_alloc*)a);
				} break;
			case ALLOC_T_LIN:
				{
					result=clear((lin_alloc*)a);
				} break;
			case ALLOC_T_STACK:
				{
					result=clear((stack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=clear((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=clear((pool_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=clear((store_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_TABLE:
				{
					result=clear((table_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=clear((fallback_alloc<SizeArgs...>*)a);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	b32 owns(const allocator<SizeArgs...>* a,const void* ptr,msize size)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=owns((null_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_LIN:
				{
					result=owns((lin_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STACK:
				{
					result=owns((stack_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=owns((free_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=owns((pool_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=owns((store_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_TABLE:
				{
					result=owns((table_alloc<SizeArgs...>*)a,ptr,size);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=owns((fallback_alloc<SizeArgs...>*)a,ptr,size);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	stack_state save_stack(allocator<SizeArgs...>* a)
	{
		stack_state result=SAVE_STACK_FAIL;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=save_stack((null_alloc*)a);
				} break;
			case ALLOC_T_LIN:
				{
					result=save_stack((lin_alloc*)a);
				} break;
			case ALLOC_T_STACK:
				{
					result=save_stack((stack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=save_stack((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=save_stack((pool_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=save_stack((store_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_TABLE:
				{
					result=save_stack((table_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=save_stack((fallback_alloc<SizeArgs...>*)a);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	b32 restore_stack(allocator<SizeArgs...>* a,stack_state state)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=restore_stack((null_alloc*)a,state);
				} break;
			case ALLOC_T_LIN:
				{
					result=restore_stack((lin_alloc*)a,state);
				} break;
			case ALLOC_T_STACK:
				{
					result=restore_stack((stack_alloc*)a,state);
				} break;
			case ALLOC_T_FREE:
				{
					result=restore_stack((free_alloc*)a,state);
				} break;
			case ALLOC_T_POOL:
				{
					result=restore_stack((pool_alloc<SizeArgs...>*)a,state);
				} break;
			case ALLOC_T_STORE:
				{
					result=restore_stack((store_alloc<SizeArgs...>*)a,state);
				} break;
			case ALLOC_T_TABLE:
				{
					result=restore_stack((table_alloc<SizeArgs...>*)a,state);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=restore_stack((fallback_alloc<SizeArgs...>*)a,state);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	b32 is_stack_balanced(const allocator<SizeArgs...>* a)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=is_stack_balanced((null_alloc*)a);
				} break;
			case ALLOC_T_LIN:
				{
					result=is_stack_balanced((lin_alloc*)a);
				} break;
			case ALLOC_T_STACK:
				{
					result=is_stack_balanced((stack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=is_stack_balanced((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=is_stack_balanced((pool_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=is_stack_balanced((store_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_TABLE:
				{
					result=is_stack_balanced((table_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=is_stack_balanced((fallback_alloc<SizeArgs...>*)a);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	msize used_mem(const allocator<SizeArgs...>* a)
	{
		msize result=MAX_MSIZE;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=used_mem((null_alloc*)a);
				} break;
			case ALLOC_T_LIN:
				{
					result=used_mem((lin_alloc*)a);
				} break;
			case ALLOC_T_STACK:
				{
					result=used_mem((stack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=used_mem((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=used_mem((pool_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=used_mem((store_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_TABLE:
				{
					result=used_mem((table_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=used_mem((fallback_alloc<SizeArgs...>*)a);
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	msize available_mem(const allocator<SizeArgs...>* a)
	{
		msize result=0;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=available_mem((null_alloc*)a);
				} break;
			case ALLOC_T_LIN:
				{
					result=available_mem((lin_alloc*)a);
				} break;
			case ALLOC_T_STACK:
				{
					result=available_mem((stack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=available_mem((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=available_mem((pool_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=available_mem((store_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_TABLE:
				{
					result=available_mem((table_alloc<SizeArgs...>*)a);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=available_mem((fallback_alloc<SizeArgs...>*)a);
				} break;
		}
		return result;
	}

	template <typename T,msize... SizeArgs>
	T* alloc(allocator<SizeArgs...>* a,u32 count)
	{
		T* result=0;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=alloc((null_alloc*)a,count);
				} break;
			case ALLOC_T_LIN:
				{
					result=alloc((lin_alloc*)a,count);
				} break;
			case ALLOC_T_STACK:
				{
					result=alloc((stack_alloc*)a,count);
				} break;
			case ALLOC_T_FREE:
				{
					result=alloc((free_alloc*)a,count);
				} break;
			case ALLOC_T_POOL:
				{
					result=alloc((pool_alloc<SizeArgs...>*)a,count);
				} break;
			case ALLOC_T_STORE:
				{
					result=alloc((store_alloc<SizeArgs...>*)a,count);
				} break;
			case ALLOC_T_TABLE:
				{
					result=alloc((table_alloc<SizeArgs...>*)a,count);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=alloc((fallback_alloc<SizeArgs...>*)a,count);
				} break;
		}
		return result;
	}

	template <typename T,msize... SizeArgs>
	b32 free(allocator<SizeArgs...>* a,T* ptr,u32 count)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=free((null_alloc*)a,count);
				} break;
			case ALLOC_T_LIN:
				{
					result=free((lin_alloc*)a,count);
				} break;
			case ALLOC_T_STACK:
				{
					result=free((stack_alloc*)a,count);
				} break;
			case ALLOC_T_FREE:
				{
					result=free((free_alloc*)a,count);
				} break;
			case ALLOC_T_POOL:
				{
					result=free((pool_alloc<SizeArgs...>*)a,count);
				} break;
			case ALLOC_T_STORE:
				{
					result=free((store_alloc<SizeArgs...>*)a,count);
				} break;
			case ALLOC_T_TABLE:
				{
					result=free((table_alloc<SizeArgs...>*)a,ptr,count);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=free((fallback_alloc<SizeArgs...>*)a,ptr,count);
				} break;
		}
		return result;
	}

	template <typename T,msize... SizeArgs>
	b32 owns(const allocator<SizeArgs...>* a,const T* ptr,u32 count)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					result=owns((null_alloc*)a,ptr,count);
				} break;
			case ALLOC_T_LIN:
				{
					result=owns((lin_alloc*)a,ptr,count);
				} break;
			case ALLOC_T_STACK:
				{
					result=owns((stack_alloc*)a,ptr,count);
				} break;
			case ALLOC_T_FREE:
				{
					result=owns((free_alloc*)a,ptr,count);
				} break;
			case ALLOC_T_POOL:
				{
					result=owns((pool_alloc<SizeArgs...>*)a,ptr,count);
				} break;
			case ALLOC_T_STORE:
				{
					result=owns((store_alloc<SizeArgs...>*)a,ptr,count);
				} break;
			case ALLOC_T_TABLE:
				{
					result=owns((table_alloc<SizeArgs...>*)a,ptr,count);
				} break;
			case ALLOC_T_FALLBACK:
				{
					result=owns((fallback_alloc<SizeArgs...>*)a,ptr,count);
				} break;
		}
		return result;
	}
}
