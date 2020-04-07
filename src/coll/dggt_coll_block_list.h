#ifndef _DGGT_COLL_BLOCK_LIST_H_

#include "dggt_coll_block_list_iter.h"

namespace dggt
{
	template <typename T,u32 BLOCKSIZE>
	struct block_list
	{
		lblock_mem<T,BLOCKSIZE> list;
	};

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list<T,BLOCKSIZE> create_block_list(u32 capacity,A* allocator);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> destroy_block_list(block_list<T,BLOCKSIZE>* blockList,A* allocator);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> push(block_list<T,BLOCKSIZE>* blockList,A* allocator);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> push(block_list<T,BLOCKSIZE>* blockList,const T& val,A* allocator);

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> peek(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> pop(block_list<T,BLOCKSIZE>* blockList,
			A* allocator);

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> get(block_list<T,BLOCKSIZE>* blockList,
			u32 index);

	template <typename T,u32 BLOCKSIZE>
	lblock_iter<T,BLOCKSIZE> get_lblock(block_list<T,BLOCKSIZE>* blockList,
			u32 blockIndex);

	template <typename T,u32 BLOCKSIZE>
	lblock_list_iter<T,BLOCKSIZE> get_lblock_list(
			block_list<T,BLOCKSIZE>* blockList,u32 blockIndex);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> clear(block_list<T,BLOCKSIZE>* blockList,
			A* allocator);

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> get_iter(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE>
	b32 contains(block_list<T,BLOCKSIZE>* blockList,const T& item);

	template <typename T,u32 BLOCKSIZE>
	u32 get_capacity(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE>
	u32 get_count(block_list<T,BLOCKSIZE>* blockList);
}

#include "dggt_coll_block_list_iter.inl"
#include "dggt_coll_block_list.inl"

#define _DGGT_COLL_BLOCK_LIST_H_
#endif
