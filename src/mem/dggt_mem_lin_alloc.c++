#include "dggt_mem_lin_alloc.h"

namespace dggt
{
	namespace dggt_internal_
	{
		void* linear_alloc(void* buff,msize buffSize,
				msize* used,msize size)
		{
			void* result=0;
			if (size&&(*used)+size<=buffSize)
			{
				if (*used+size<=buffSize)
				{
					result=ptr_add(buff,*used);
					*used+=size;
				}
			}
			return result;
		}
		
		b32 linear_free()
		{
			return false;
		}

		b32 linear_clear(msize* used)
		{
			*used=0;
			return true;
		}
	}

	void* malloc(lin_alloc* a,msize size)
	{
		if (a)
		{
			return dggt_internal_::linear_alloc(a->val.pge.ptr,
					a->val.pge.size,&a->val.used,size);
		}
		else
		{
			return 0;
		}
	}

	
	b32 free(lin_alloc* a,void* ptr,msize size)
	{
		return dggt_internal_::linear_free();
	}

	
	b32 clear(lin_alloc* a)
	{
		if (a)
		{
			return dggt_internal_::linear_clear(&a->val.used);
		}
		else
		{
			return 0;
		}
	}
}
