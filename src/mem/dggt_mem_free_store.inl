#include "defines/dggt_defines.h"

namespace dggt_internal_
{
	struct free_struct
	{
		free_struct* next;
	};
}

namespace dggt
{

	template <typename T>
	free_store<T>::free_store()
	{
		head=0;
		count=0;
	}

	template <typename T>
	T* free_store<T>::pop()
	{
		T* result=0;
		if (count)
		{
			dggt_internal_::free_struct* headFreeStruct=
				(dggt_internal_::free_struct*)head;
			result=head;
			head=(T*)headFreeStruct->next;
			--count;
		}
		return result;
	}

	template <typename T>
	void free_store<T>::push(T* val)
	{
		ASSERT(sizeof(T)>=sizeof(free_struct));
		dggt_internal_::free_struct* headFreeStruct=
			(dggt_internal_::free_struct*)head;
		dggt_internal_::free_struct* valFreeStruct=
			(dggt_internal_::free_struct*)val;
		valFreeStruct->next=headFreeStruct;
		head=val;
		++count;
	}

	template <typename T>
	msize free_store<T>::available_mem() const
	{
		return (msize)count*sizeof(T);
	}
}
