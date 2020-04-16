#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	void* malloc(lin_alloc* a,msize size)
	{
		void* result=0;
		if (a&&get_used(a)+size<=get_available(a))
		{
			result=ptr_add(get_buff_ptr(a),get_used(a));
			++a->used;
		}
		return result;
	}

	b32 owns(const lin_alloc* a,void* ptr,msize size)
	{
		b32 result=0;
		if (a)
		{
			return ptr>=a->buff.ptr&&
				ptr_add(ptr,size)<ptr_add(a->buff.ptr,a->buff.size);
		}
		return result;
	}

	b32 clear(lin_alloc* a)
	{
		b32 result=false;
		if (a)
		{
			a->used=0;
			result=true;
		}
		return result;
	}

	msize get_used(const lin_alloc* a) { return a?a->used:MAX_MSIZE; }

	msize get_available(const lin_alloc* a) { return a?get_capacity(a)-get_used(a):0; }

	void* get_buff_ptr(lin_alloc* a)
	{
		return a?a->buff.ptr:0;
	}

	const void* get_buff_ptr(const lin_alloc* a)
	{
		return a?a->buff.ptr:0;
	}


}
