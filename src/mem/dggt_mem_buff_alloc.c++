#include "dggt_mem_buff_alloc.h"
#include "dggt_mem_utils.h"

namespace dggt
{
	namespace internal_
	{
		b32 buff_alloc_owns(const allocator* a,const void* ptr,msize size)
		{
			b32 result=false;
			buff_alloc* buffAlloc=(buff_alloc*)a;
			if (buffAlloc)
			{
				const void* buffPtr=get_buff_ptr(a);
				msize buffSize=get_capacity(a);
				result=ptr>=buffPtr&&
					ptr_add(ptr,size)<ptr_add(buffPtr,buffSize);
			}
			return result;
		}

		b32 buff_alloc_owns(const allocator* a,const vpage& pge)
		{
			return buff_alloc_owns(a,pge.ptr,pge.size);
		}

		msize buff_alloc_get_capacity(const allocator* a)
		{
			msize result=0;
			buff_alloc* buffAlloc=(buff_alloc*)a;
			if (buffAlloc)
			{
				return buffAlloc->buff.size;
			}
			return result;
		}

		msize buff_alloc_get_available(const allocator* a)
		{
			return buff_alloc_get_capacity(a);
		}

		vpage buff_alloc_get_buff(allocator* a)
		{
			vpage result=vpage();
			buff_alloc* buffAlloc=(buff_alloc*)a;
			if (buffAlloc)
			{
				return buffAlloc->buff;
			}
			return result;
		}

		const vpage buff_alloc_get_buff(const allocator* a)
		{
			vpage result=vpage();
			buff_alloc* buffAlloc=(buff_alloc*)a;
			if (buffAlloc)
			{
				return buffAlloc->buff;
			}
			return result;
		}

		void* buff_alloc_get_buff_ptr(allocator* a)
		{
			return buff_alloc_get_buff(a).ptr;
		}

		const void* buff_alloc_get_buff_ptr(const allocator* a)
		{
			return buff_alloc_get_buff(a).ptr;
		}

		global alloc_func_table BUFF_ALLOC_TABLE=
		{
			allocator_malloc,
			allocator_malloc_vpage,
			allocator_free,
			allocator_free,
			allocator_clear,
			buff_alloc_owns,
			buff_alloc_owns,
			allocator_save_stack,
			allocator_restore_stack,
			allocator_is_stack_balanced,
			allocator_get_used,
			buff_alloc_get_available,
			buff_alloc_get_capacity,
			buff_alloc_get_buff,
			buff_alloc_get_buff,
			buff_alloc_get_buff_ptr,
			buff_alloc_get_buff_ptr
		};
	}

	buff_alloc::buff_alloc(alloc_func_table* tbl,vpage buffer)
		: allocator(tbl),buff(buffer) { }

	buff_alloc::buff_alloc(vpage buffer)
		: buff_alloc(&internal_::BUFF_ALLOC_TABLE,buffer) { }

	buff_alloc::buff_alloc()
		: buff_alloc(vpage()) { }

	buff_alloc::buff_alloc(void* buffer,msize size)
		: buff_alloc(vpage(buffer,size)) { }
}
