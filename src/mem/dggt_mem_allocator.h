#ifndef _DGGT_MEM_ALLOCATOR_H_

#include "dggt_mem_utils.h"
#include "dggt_mem_page.h"
#include "dggt_mem_defines.h"
#include "tmpl/dggt_tmpl_enable_if.h"
#include "tmpl/dggt_tmpl_is_type.h"

namespace dggt
{
	typedef msize stack_state;
	static constexpr const stack_state SAVE_STACK_FAIL=MAX_MSIZE;

	struct mblock
	{
		mblock* next;
	};

	struct smblock
	{
		msize size;
		smblock* next;
	};

	struct alloc_buff
	{
		vpage pge;
		msize used;
		alloc_buff() : pge(vpage()),used(0) { }
		alloc_buff(vpage pge,msize used) : pge(pge),used(used) { }
	};

	struct alloc_stack:
		alloc_buff
	{
		u32 stateCount;
		stack_state prevState;

		alloc_stack(vpage pge,msize used) : 
			alloc_buff(pge,used),
			stateCount(0),prevState(0) { }

		alloc_stack() : alloc_stack(vpage(),0) { }
	};

	template <typename B>
	struct alloc_chain
	{
		B* head;
		msize count;
	};

	template <typename M=alloc_buff,bool32 BUFF=true>
	struct allocator:
		val_if<BUFF,M>
	{
		static constexpr bool32 BUFFERED=BUFF;
		typedef M mem_type;

		allocator(M m) : val_if<BUFF,M>(m) { }
		allocator() : allocator(M()) { }
	};

	template <typename M,bool32 B>
	void* malloc(allocator<M,B>* a,msize size=0)
	{
		if constexpr (is_base_of<val_if<false,u32>,allocator<M,B>>::val)
		{
			return 0;
		}
	}

	template <typename M,bool32 B>
	b32 free(allocator<M,B>* a,void* ptr,msize size=0)
	{
		if constexpr (allocator<M,B>::BUFFERED==false)
		{
			return false;
		}
	}
	
	template <typename M,bool32 B>
	b32 clear(allocator<M,B>* a)
	{
		if constexpr (allocator<M,B>::BUFFERED==false)
		{
			return false;
		}
	}

	template <typename M,bool32 B>
	b32 owns(const allocator<M,B>* a,const void* ptr,msize size=0)
	{
		if constexpr (allocator<M,B>::BUFFERED)
		{
			if constexpr (is_same<typename allocator<M,B>::mem_type,alloc_buff>::val)
			{
				return ptr>a->val.pge.ptr&&
					ptr_add(ptr,size)<=
					ptr_add(a->val.pge.ptr,a->val.pge.size);
			}
		}
		else
		{
			return ptr==0&&size==0;
		}
	}

	template <typename M,bool32 B>
	stack_state save_stack(allocator<M,B>* a)
	{
		if constexpr (is_same<typename allocator<M,B>::mem_type,alloc_stack>::val)
		{
			stack_state result=(stack_state)used_mem(a);
			a->val.prevState=result;
			++a->val.stateCount;
			return result;
		}
		else
		{
			return SAVE_STACK_FAIL;
		}
	}

	template <typename M,bool32 B>
	b32 restore_stack(allocator<M,B>* a,stack_state state)
	{
		if constexpr (is_same<typename allocator<M,B>::mem_type,alloc_stack>::val)
		{
			b32 result=state==a->val.prevState;
			if (result)
			{
				a->val.used=state;
				--a->val.stateCount;
			}
			return result;
		}
		else
		{
			return false;
		}
	}

	template <typename M,bool32 B>
	b32 is_stack_balanced(const allocator<M,B>* a)
	{
  		if constexpr (is_same<typename allocator<M,B>::mem_type,alloc_stack>::val)
		{
			return a->val.stateCount==0;
		}
		else
		{
			return true;
		}
	}

	template <typename M,bool32 B>
	msize used_mem(const allocator<M,B>* a)
	{
		if constexpr (allocator<M,B>::BUFFERED)
		{
			if constexpr (is_type<typename allocator<M,B>::mem_type,alloc_buff>::val)
			{
				return a->val.used;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return MAX_MSIZE;
		}
	}

	template <typename M,bool32 B>
	msize available_mem(const allocator<M,B>* a)
	{
		if constexpr (allocator<M,B>::BUFFERED)
		{
			if constexpr (is_same<typename allocator<M,B>::mem_type,alloc_buff>::val)
			{
				return a->val.pge.size-a->val.used;
			}
			else if constexpr (is_same<typename allocator<M,B>::mem_type,
					alloc_chain<mblock>>::val)
			{
				return a->val.count*sizeof(mblock);
			}
			else if constexpr (is_same<typename allocator<M,B>::mem_type,
					alloc_chain<smblock>>::val)
			{
				msize result=0;
				smblock* current=a->val.head;
				while (current)
				{
					result+=current->size;
					current=current->next;
				}
				return result;
			}
		}
		else
		{
			return 0;
		}
	}

	template <typename T,typename M,bool32 B>
	T* malloc(allocator<M,B>* a,msize size)
	{
		return (T*)malloc(a,sizeof(T)*size);
	}

	template <typename T,typename M,bool32 B>
	b32 free(allocator<M,B>* a,T* ptr,msize size)
	{
		return free(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,typename M,bool32 B>
	b32 owns(const allocator<M,B>* a,const T* ptr,msize size)
	{
		return owns(a,(void*)ptr,sizeof(T)*size);
	}

	template <typename T,typename M,bool32 B>
	page<T> malloc_page(allocator<M,B>* a,msize size)
	{
		return page<T>(malloc<T>(a,size),size);
	}

	template <typename T,typename M,bool32 B>
	vpage malloc_vpage(allocator<M,B>* a,msize size)
	{
		return vpage(malloc(a,size),size);
	}

	template <typename T,typename M,bool32 B>
	b32 free(allocator<M,B>* a,page<T>& pge)
	{
		return free(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}

	template <typename M,bool32 B>
	b32 free(allocator<M,B>* a,vpage& pge)
	{
		return free(a,(void*)pge.ptr,pge.size);
	}

	template <typename T,typename M,bool32 B>
	b32 owns(allocator<M,B>* a,page<T>& pge)
	{
		return owns(a,(void*)pge.ptr,sizeof(T)*pge.size);
	}

	template <typename M,bool32 B>
	b32 owns(allocator<M,B>* a,vpage& pge)
	{
		return owns(a,(void*)pge.ptr,pge.size);
	}
}

#define _DGGT_MEM_ALLOCATOR_H_
#endif
