
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,u32 BLOCKSIZE>
		block_list_iter<T,BLOCKSIZE> get_def_block_list_iter(
				block_list<T,BLOCKSIZE>* blockList)
		{
			block_list_iter<T,BLOCKSIZE> result={};
			result.blockList=blockList;
			return result;
		}
	}

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list<T,BLOCKSIZE> create_block_list(u32 capacity,A* allocator)
	{
		block_list<T,BLOCKSIZE> result=block_list<T,BLOCKSIZE>{
			create_sllist()};
		u32 listCount=capacity/BLOCKSIZE;
		for (u32 i=0;i<listCount;++i)
		{
			push(&result.list,allocator);
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> destroy_block_list(
			block_list<T,BLOCKSIZE>* blockList,A* allocator)
	{
		block_list_iter<T,BLOCKSIZE> result=
			dggt_internal_::get_def_block_list_iter(blockList);
		if (blockList)
		{
			result.blockListMem=blockList->list;
			result.lblockListIter=get_iter(&blockList->list);
			result.lblockIter=get_iter(*result.lblockListIter);
			if (!is_coll_valid(destroy_sllist(blockList->list,allocator)))
			{
				result=
					dggt_internal_::get_def_block_list_iter<T,BLOCKSIZE>(
							(block_list<T,BLOCKSIZE>*)0);
			}
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> push(block_list<T,BLOCKSIZE>* blockList,
			A* allocator)
	{
		block_list_iter<T,BLOCKSIZE> result=
			dggt_internal_::get_def_block_list_iter(blockList);
		if (blockList)
		{
			result.blockListMem=blockList->list;
			result.lblockListIter=get_iter(blockList->list);
			if (get(get_iter(blockList->list)).count>=BLOCKSIZE)
			{
				result.lblockListIter=push(blockList->list,allocator);
			}
			result.lblockIter=push(get_ptr(get_iter(blockList->list)));
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> push(block_list<T,BLOCKSIZE>* blockList,
			const T& val,A* allocator)
	{
		block_list_iter<T,BLOCKSIZE> result=push(blockList,allocator);
		if (is_mem_valid(result))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> peek(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> pop(block_list<T,BLOCKSIZE>* blockList,
			A* allocator);

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> get(block_list<T,BLOCKSIZE>* blockList,
			u32 index);

	template <typename T,u32 BLOCKSIZE>
	list_block_iter<T,BLOCKSIZE> get_block(block_list<T,BLOCKSIZE>* blockList,
			u32 blockIndex);

	template <typename T,u32 BLOCKSIZE,typename A>
	block_list_iter<T,BLOCKSIZE> clear(block_list<T,BLOCKSIZE>* blockList,
			A* allocator);

	template <typename T,u32 BLOCKSIZE>
	block_list_iter<T,BLOCKSIZE> get_iter(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE>
	list_block_iter<T,BLOCKSIZE> get_block_iter(
			block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE>
	b32 contains(block_list<T,BLOCKSIZE>* blockList,const T& item);

	template <typename T,u32 BLOCKSIZE>
	u32 get_capacity(block_list<T,BLOCKSIZE>* blockList);

	template <typename T,u32 BLOCKSIZE>
	u32 get_count(block_list<T,BLOCKSIZE>* blockList);
}
