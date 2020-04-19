#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	namespace internal_
	{
		void* lin_alloc_malloc(allocator* a,msize size)
		{
			void* result=0;
			lin_alloc* linAlloc=(lin_alloc*)a;
			if (linAlloc&&
					lin_alloc_get_used(linAlloc)+size<=
					lin_alloc_get_available(linAlloc))
			{
				result=ptr_add(get_buff_ptr(linAlloc),get_used(linAlloc));
				++linAlloc->used;
			}
			return result;
		}

		vpage lin_alloc_malloc_vpage(allocator* a,msize size)
		{
			return vpage(lin_alloc_malloc(a,size),size);
		}

		b32 lin_alloc_clear(allocator* a)
		{
			b32 result=false;
			lin_alloc* linAlloc=(lin_alloc*)a;
			if (linAlloc)
			{
				linAlloc->used=0;
				result=true;
			}
			return result;
		}

		msize lin_alloc_get_used(const allocator* a)
		{
			msize result=0;
			lin_alloc* linAlloc=(lin_alloc*)a;
			if (linAlloc)
			{
				return linAlloc->used;
			}
			return result;
		}

		msize lin_alloc_get_available(const allocator* a)
		{
			return buff_alloc_get_capacity(a)-lin_alloc_get_used(a);
		}

		static alloc_func_table LIN_ALLOC_TABLE=
		{
			lin_alloc_malloc,
			lin_alloc_malloc_vpage,
			allocator_free,
			allocator_free,
			lin_alloc_clear,
			buff_alloc_owns,
			buff_alloc_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			lin_alloc_get_used,
			lin_alloc_get_available,
			buff_alloc_get_capacity,
			buff_alloc_get_buff,
			buff_alloc_get_buff,
			buff_alloc_get_buff_ptr,
			buff_alloc_get_buff_ptr
		};
	}

	lin_alloc::lin_alloc(alloc_func_table* tbl,vpage buff)
		:buff_alloc(tbl,buff),used(0) { }

	lin_alloc::lin_alloc()
		:lin_alloc(&internal_::LIN_ALLOC_TABLE,vpage()) { }

	lin_alloc::lin_alloc(vpage buff)
		:lin_alloc(&internal_::LIN_ALLOC_TABLE,buff) { }

	lin_alloc::lin_alloc(void* buff,msize size)
		:lin_alloc(vpage(buff,size)) { }
}
