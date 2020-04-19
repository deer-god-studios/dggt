#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_allocator.h"

namespace dggt
{
	template <typename P,typename F>
	struct fallback_alloc:
		allocator
	{
		P* p;
		F* f;

		fallback_alloc():allocator(),p(0),f(0) { }
		fallback_alloc(P* primary,F* fallback)
			:allocator(0),p(primary),f(fallback) { }
	};

	template <typename P,typename F>
	void* malloc(fallback_alloc<P,F>* a,msize size)
	{
		void* result=0;
		if (a)
		{
			result=malloc(a->p,size);
			if (!result)
			{
				result=malloc(a->f,size);
			}
		}
		return result;
	}

	template <typename P,typename F>
	vpage malloc_vpage(fallback_alloc<P,F>* a,msize size)
	{
		return vpage(malloc(a,size),size);
	}

	template <typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,void* ptr,msize size)
	{
		b32 result=false;
		if (a)
		{
			result=free(a->p,ptr,size);
			if (!result)
			{
				result=free(a->f,ptr,size);
			}
		}
		return result;
	}

	template <typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,vpage& pge)
	{
		return free(a,pge.ptr,pge.size);
	}

	template <typename P,typename F>
	b32 clear(fallback_alloc<P,F>* a)
	{
		b32 result=false;
		
		return result;
	}

	template <typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,const void* ptr,msize size)
	{
		return a?owns(a->p,ptr,size)||owns(a->f,ptr,size):false;
	}

	template <typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,const vpage& pge)
	{
		return owns(a,pge.ptr,pge.size);
	}

	template <typename P,typename F>
	stack_state save_stack(fallback_alloc<P,F>* a)
	{
		stack_state result=SAVE_STACK_FAIL;
		if (a)
		{
			result=save_stack(a->p);
			if (result==SAVE_STACK_FAIL)
			{
				result=save_stack(a->f);
			}
		}
		return result;
	}

	template <typename P,typename F>
	b32 restore_stack(fallback_alloc<P,F>* a,stack_state state)
	{
		b32 result=false;
		if (a)
		{
			result=restore_stack(a->p,state);
			if (!result)
			{
				result=restore_stack(a->f,state);
			}
		}
		return result;
	}

	template <typename P,typename F>
	b32 is_stack_balanced(const fallback_alloc<P,F>* a)
	{
		return a?is_stack_balanced(a->p)&&is_stack_balanced(a->f):false;
	}

	template <typename P,typename F>
	msize get_used(const fallback_alloc<P,F>* a)
	{
		return a?get_used(a->p)+get_used(a->f):MAX_MSIZE;
	}

	template <typename P,typename F>
	msize get_available(const fallback_alloc<P,F>* a)
	{
		return a?get_available(a->p)+get_available(a->f):0;
	}

	template <typename P,typename F>
	msize get_capacity(const fallback_alloc<P,F>* a)
	{
		return a?get_capacity(a->p)+get_capacity(a->f):0;
	}

	template <typename P,typename F>
	vpage get_buff(fallback_alloc<P,F>* a)
	{
		vpage result=vpage();
		if (a)
		{
			result=get_buff(a->p);
			if (result==vpage())
			{
				result=get_buff(a->f);
			}
		}
		return result;
	}

	template <typename P,typename F>
	const vpage get_buff(const fallback_alloc<P,F>* a)
	{
		vpage result=vpage();
		if (a)
		{
			result=get_buff(a->p);
			if (result==vpage())
			{
				result=get_buff(a->f);
			}
		}
		return result;
	}

	template <typename P,typename F>
	void* get_buff_ptr(fallback_alloc<P,F>* a)
	{
		void* result=0;
		if (a)
		{
			result=get_buff_ptr(a->p);
			if (!result)
			{
				result=get_buff_ptr(a->f);
			}
		}
		return result;
	}

	template <typename P,typename F>
	const void* get_buff_ptr(const fallback_alloc<P,F>* a)
	{
		void* result=0;
		if (a)
		{
			result=get_buff_ptr(a->p);
			if (!result)
			{
				result=get_buff_ptr(a->f);
			}
		}
		return result;
	}

	template <typename T,typename P,typename F>
	T* malloc(fallback_alloc<P,F>* a,msize size=1)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,typename P,typename F>
	page<T> malloc_page(fallback_alloc<P,F>* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T,typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,T* ptr,msize size=1)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,typename P,typename F>
	b32 free(fallback_alloc<P,F>* a,page<T>& pge)
	{
		return free(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
	
	template <typename T,typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,typename P,typename F>
	b32 owns(const fallback_alloc<P,F>* a,page<T>& pge)
	{
		return owns(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}
}

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
