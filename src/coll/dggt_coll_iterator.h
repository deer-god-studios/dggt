#ifndef _DGGT_COLL_ITER_H_

/*
 * TODO: add is_begin
 * TODO: change advance to increment (or add increment).
 * TODO: change free to return a valid begin iterator.
 */

namespace dggt
{
	// T: underlying contained type.
	// M: container's memory back-store type.
	// C: container type.
	// K: key type.  anything that can be incremented and holds the
	// 		T value somehow. (eg. indexes, nodes, etc.)
	template <typename T,typename M,typename C,typename K>
	struct iterator
	{
		typedef T val_type;
		typedef K key_type;
		typedef M mem_type;
		typedef C coll_type;

		mem_type mem;
		coll_type* coll;
		key_type current;

		iterator(coll_type* coll) : this->coll(coll) { }
		iterator(const mem_type& mem,coll_type* coll)
			: iterator(coll),this->mem(mem) { }
		iterator()
			: iterator(mem_type(),0) { }
	};

	template <typename T,typename M,typename C>
	b32 is_coll_valid(const iterator<T,M,C>& it) { return coll!=0; }

	template <typename T,typename M,typename C>
	b32 is_mem_valid(const iterator<T,M,C>& it)
	{
		return is_coll_valid(it)&&
			it.mem==coll->mem;
	}

	template <typename T,typename M,typename C>
	b32 vindicate_mem(iterator<T,M,C>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&
				!is_mem_valid(it))
		{
			it.mem=coll->mem;
		}
		return result;
	}

	template <typename T,typename M,typename C>
	iterator<T,M,C>::coll_type* get_coll(iterator<T,M,C>& it)
	{
		return it.coll;
	}

	template <typename T,typename M,typename C>
	iterator<T,M,C>::mem_type get_mem(iterator<T,M,C>& it)
	{
		return it.mem;
	}

	template <typename T,typename M,typename C,typename A>
	b32 free(A* a,iterator<T,M,C>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&
				!is_mem_valid(it))
		{
			result=free(a,it.mem);
			result=result&&vindicate_mem(it);
		}
		return result;
	}

}

#define _DGGT_COLL_ITER_H_
#endif
