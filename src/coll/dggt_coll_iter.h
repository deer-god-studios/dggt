#ifndef _DGGT_COLL_ITER_H_

namespace dggt
{

	template <typename T,typename M,typename C>
	struct iter
	{
		typedef T ValType;
		typedef C CollType;
		typedef M MemType;

		MemType mem;
		CollType* coll;

		iter(MemType mem,CollType* coll);

		T& operator*();

		const T& operator*() const;

		explicit operator M&();
	};
}

#include "dggt_coll_iter.inl"

#define _DGGT_COLL_ITER_H_
#endif
