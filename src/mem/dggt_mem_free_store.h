#ifndef _DGGT_MEM_FREE_STORE_H_

namespace dggt
{
	template <typename T>
	struct free_store
	{
		T* head;
		u32 count;

		free_store();

		T* pop();
		void push(T* val);
		msize available_mem() const;
	};
}

#include "dggt_mem_free_store.inl"

#define _DGGT_MEM_FREE_STORE_H_
#endif
