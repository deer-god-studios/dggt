#ifndef _DGGT_MEM_STALLOCATOR_H_

#include "dggt_mem_stack_alloc.h"

namespace dggt
{
	template <msize BUFFSIZE,typename A=stack_alloc>
	struct stallocator
	{
		A a_;
		ubyte buff[BUFFSIZE];

		stallocator() { a_=A((void*)buff,BUFFSIZE); }
	};
}

#define _DGGT_MEM_STALLOCATOR_H_
#endif
