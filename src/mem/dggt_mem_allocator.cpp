#include "dggt_mem_alloc.h"
#include "dggt_mem_null_alloc.h"
#include "dggt_mem_lin_alloc.h"
#include "dggy_mem_stack_alloc.h"
#include "dggy_mem_autostack_alloc.h"
#include "dggy_mem_free_alloc.h"
#include "dggy_mem_pool_alloc.h"
#include "dggy_mem_store_alloc.h"
#include "dggy_mem_store_table_alloc.h"

namespace dggt
{
	void* alloc(allocator* a,msize size)
	{
		void* result=0;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=alloc((autostack_alloc*)a,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=alloc((free_alloc*)a,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=alloc((pool_alloc*)a,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=alloc((store_alloc*)a,size);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=alloc((store_table_alloc*)a,size);
				} break;
		}
		return result;
	}

	b32 free(allocator* a,void* ptr,msize size)
	{
		b32 result=false;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=free((autostack_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=free((free_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=free((pool_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=free((store_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=free((store_table_alloc*)a,ptr,size);
				} break;
		}
		return result;
	}
	
	b32 clear(allocator* a)
	{
		b32 result=false;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=clear((autostack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=clear((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=clear((pool_alloc*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=clear((store_alloc*)a);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=clear((store_table_alloc*)a);
				} break;
		}
		return result;
	}

	b32 owns(const allocator* a,const void* ptr,msize size)
	{
		b32 result=false;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=owns((autostack_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_FREE:
				{
					result=owns((free_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_POOL:
				{
					result=owns((pool_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STORE:
				{
					result=owns((store_alloc*)a,ptr,size);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=owns((store_table_alloc*)a,ptr,size);
				} break;
		}
		return result;
	}

	stack_state save_stack(allocator* a)
	{
		b32 result=STACK_SAVE_FAIL;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=save_stack((autostack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=save_stack((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=save_stack((pool_alloc*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=save_stack((store_alloc*)a);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=save_stack((store_table_alloc*)a);
				} break;
		}
		return result;
	}

	b32 restore_stack(allocator* a,stack_state state)
	{
		b32 result=false;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=restore_stack((autostack_alloc*)a,state);
				} break;
			case ALLOC_T_FREE:
				{
					result=restore_stack((free_alloc*)a,state);
				} break;
			case ALLOC_T_POOL:
				{
					result=restore_stack((pool_alloc*)a,state);
				} break;
			case ALLOC_T_STORE:
				{
					result=restore_stack((store_alloc*)a,state);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=restore_stack((store_table_alloc*)a,state);
				} break;
		}
		return result;
	}

	b32 is_stack_balanced(const allocator* a)
	{
		b32 result=true;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=is_stack_balanced((autostack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=is_stack_balanced((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=is_stack_balanced((pool_alloc*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=is_stack_balanced((store_alloc*)a);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=is_stack_balanced((store_table_alloc*)a);
				} break;
		}
		return result;
	}

	msize used_mem(const allocator* a)
	{
		msize result=MAX_MSIZE;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=used_mem((autostack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=used_mem((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=used_mem((pool_alloc*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=used_mem((store_alloc*)a);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=used_mem((store_table_alloc*)a);
				} break;
		}
		return result;
	}

	msize available_mem(const allocator* a)
	{
		msize result=0;
		switch (a->baseAlloc.TYPE)
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
			case ALLOC_T_AUTOSTACK:
				{
					result=available_mem((autostack_alloc*)a);
				} break;
			case ALLOC_T_FREE:
				{
					result=available_mem((free_alloc*)a);
				} break;
			case ALLOC_T_POOL:
				{
					result=available_mem((pool_alloc*)a);
				} break;
			case ALLOC_T_STORE:
				{
					result=available_mem((store_alloc*)a);
				} break;
			case ALLOC_T_STORE_TABLE:
				{
					result=available_mem((store_table_alloc*)a);
				} break;
		}
		return result;
	}
}
