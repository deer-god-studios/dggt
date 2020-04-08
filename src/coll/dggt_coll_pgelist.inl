
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T,u32 S>
		pgelist_iter<T,S> get_def_pgelist_iter(
				pgelist<T,S>* pgeList)
		{
			pgelist_iter<T,S> result={};
			result.pgeList=pgeList;
			return result;
		}
	}

	template <typename T,u32 S,typename A>
	pgelist<T,S> create_pgelist(u32 capacity,A* allocator)
	{
		pgelist<T,S> result=pgelist<T,S>{
			create_sllist()};
		u32 listCount=capacity/S;
		for (u32 i=0;i<listCount;++i)
		{
			push(&result.list,allocator);
		}
		return result;
	}

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> destroy_pgelist(
			pgelist<T,S>* pgeList,A* allocator)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgeListMem=pgeList->list;
			result.lpgeListIter=get_iter(&pgeList->list);
			result.lblockIter=get_iter(*result.lpgeListIter);
			if (!is_coll_valid(destroy_sllist(pgeList->list,allocator)))
			{
				result=
					dggt_internal_::get_def_pgelist_iter<T,S>(
							(pgelist<T,S>*)0);
			}
		}
		return result;
	}

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> push(pgelist<T,S>* pgeList,
			A* allocator)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgeListMem=pgeList->list;
			result.lpgeListIter=get_iter(pgeList->list);
			if (get(get_iter(pgeList->list)).count>=S)
			{
				result.lpgeListIter=push(pgeList->list,allocator);
			}
			result.lblockIter=push(get_ptr(get_iter(pgeList->list)));
		}
		return result;
	}

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> push(pgelist<T,S>* pgeList,
			const T& val,A* allocator)
	{
		pgelist_iter<T,S> result=push(pgeList,allocator);
		if (is_mem_valid(result))
		{
			*result=val;
		}
		return result;
	}

	template <typename T,u32 S>
	pgelist_iter<T,S> peek(pgelist<T,S>* pgeList);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> pop(pgelist<T,S>* pgeList,
			A* allocator);

	template <typename T,u32 S>
	pgelist_iter<T,S> get(pgelist<T,S>* pgeList,
			u32 index);

	template <typename T,u32 S>
	list_block_iter<T,S> get_block(pgelist<T,S>* pgeList,
			u32 blockIndex);

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> clear(pgelist<T,S>* pgeList,
			A* allocator);

	template <typename T,u32 S>
	pgelist_iter<T,S> get_iter(pgelist<T,S>* pgeList);

	template <typename T,u32 S>
	list_block_iter<T,S> get_block_iter(
			pgelist<T,S>* pgeList);

	template <typename T,u32 S>
	b32 contains(pgelist<T,S>* pgeList,const T& item);

	template <typename T,u32 S>
	u32 get_capacity(pgelist<T,S>* pgeList);

	template <typename T,u32 S>
	u32 get_count(pgelist<T,S>* pgeList);
}
