#ifndef _DGGT_COLL_BLOCK_LIST_ITER_H_

#include "dggt_coll_starray.h"
#include "dggt_coll_sllist.h"

namespace dggt
{
	template <typename T,u32 BLOCKSIZE>
	struct block_list;

	template <typename T,u32 BLOCKSIZE>
	using lblock=starray<T,BLOCKSIZE>;

	template <typename T,u32 BLOCKSIZE>
	using lblock_mem=sllist<lblock<T,BLOCKSIZE>>;

	template <typename T,u32 BLOCKSIZE>
	using lblock_iter=starray_iter<T,BLOCKSIZE>;

	template <typename T,u32 BLOCKSIZE>
	using lblock_list_iter=sllist_iter<lblock<T,BLOCKSIZE>>;

	template <typename T,u32 BLOCKSIZE>
	struct block_list_iter
	{
		block_list_mem<T,BLOCKSIZE> blockListMem;
		lblock_iter<T,BLOCKSIZE> lblockIter;
		lblock_list_iter<T,BLOCKSIZE> lblockListIter;
		block_list<T,BLOCKSIZE>* blockList;

		b32 is_end() const;
		T& operator*();
		const T& operator*() const;
		block_list_iter<T,BLOCKSIZE>& operator++();
		block_list_iter<T,BLOCKSIZE> operator++(int);
	};

	template <typename T,u32 BLOCKSIZE>
	b32 is_end(const block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	b32 advance(block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	T& get(block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	const T& get(const block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	T* get_ptr(block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	const T* get_ptr(const block_list_iter<T,BLOCKSIZE>& it);
	
	template <typename T,u32 BLOCKSIZE>
	block_list_mem<T,BLOCKSIZE> get_mem(block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	const block_list_mem<T,BLOCKSIZE> get_mem(const block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	b32 is_coll_valid(const block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	b32 is_mem_valid(const block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,u32 BLOCKSIZE>
	b32 vindicate_mem(block_list_iter<T,BLOCKSIZE>& it);

	template <typename T,typename A>
	b32 free(A* a,block_list_iter<T,BLOCKSIZE>& it);
}

#define _DGGT_COLL_BLOCK_LIST_ITER_H_
#endif
