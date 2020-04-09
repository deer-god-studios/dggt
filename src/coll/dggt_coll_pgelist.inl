
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
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(&pgeList->list);
			result.pgeMemIter=get_iter(get_ptr(result.pgelistIter));
			if (!is_coll_valid(destroy_sllist(&pgeList->list,allocator)))
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
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(&pgeList->list);
			if ((*result.pgelistMemItr).count>=S)
			{
				result.lpgelistIter=push(&pgeList->list,allocator);
			}
			result.pgeMemIter=push(get_ptr(get_iter(&pgeList->list)));
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
	pgelist_iter<T,S> peek(pgelist<T,S>* pgeList)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(result.pgelistMem);
			result.pgeMemIter=get_iter(get_ptr(result.pgelistMemIter));
		}
		return result;
	}

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> pop(pgelist<T,S>* pgeList,A* allocator)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(&pgeList->list);
			result.pgeMemIter=get_iter(get_ptr(result.pgelistMemIter));
			sllist<starray<T,S>>* pageList=result.pgeList;
			starray<T,S>* page=get_ptr(result.pgelistMemIter);
			if (get_count(page)==0)
			{
				pop(pageList,allocator);
			}
			pop(page,allocator);
		}
		return result;
	}

	template <typename T,u32 S>
	pgelist_iter<T,S> get(pgelist<T,S>* pgeList,u32 index)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgelistMem=pgeList->list;
			u32 pgeIndex=index/S;
			u32 itemIndex=index%S;
			result.pgelistMemIter=get(&pgeList->list,pgeIndex);
			result.pgeMemIter=get(get_ptr(result.pgelistMemIter),itemIndex);
		}
		return result;
	}

	template <typename T,u32 S>
	page_mem_iter<T,S> get_page_mem(pgelist<T,S>* pgeList,
			u32 pgeIndex,u32 itemIndex)
	{
		pagelist_mem_iter<T,S> listIter=get(&pgeList->list,pgeIndex);
		page_mem_iter<T,S> result=get(get_ptr(listIter),itemIndex);
		return result;
	}

	template <typename T,u32 S,typename A>
	pgelist_iter<T,S> clear(pgelist<T,S>* pgeList,A* allocator)
	{
		pgelist_iter<T,S> result=
			dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(&pgeList->list);
			result.pgeMemIter=get(get_ptr(result.pgelistMemIter));
			if (!is_coll_valid(destroy_sllist(&pgeList->list,allocator)))
			{
				result.pgelistMem={};
				result.pgelistMemIter={};
				result.pgeMemIter={};
			}
		}
		return result;
	}

	template <typename T,u32 S>
	pgelist_iter<T,S> get_iter(pgelist<T,S>* pgeList)
	{
		pgelist_iter<T,S> result=dggt_internal_::get_def_pgelist_iter(pgeList);
		if (pgeList)
		{
			result.pgelistMem=pgeList->list;
			result.pgelistMemIter=get_iter(&pgeList->list);
			if (!is_end(result.pgelistMemIter))
			{
				result.pgeMemIter=get_iter(get_ptr(result.pgelistMemIter));
			}
		}
		return result;
	}

	template <typename T,u32 S>
	b32 contains(pgelist<T,S>* pgeList,const T& item)
	{
		b32 result=false;
		if (pgeList)
		{
			for (pgelist_iter<T,S> it=get_iter(pgeList);
					!it.is_end();++it)
			{
				if (*it==item)
				{
					result=true;
					break;
				}
			}
		}
		return result;
	}

	template <typename T,u32 S>
	u32 get_capacity(pgelist<T,S>* pgeList)
	{
		return S*get_count(pgeList);
	}

	template <typename T,u32 S>
	u32 get_count(pgelist<T,S>* pgeList)
	{
		u32 result=0;
		if (pgeList)
		{
			u32 listCount=get_count(&pgeList->list);
			if (listCount)
			{
				starray<T,S>* headPage=get_ptr(get_iter(&pgeList->list));
				result=get_count(headPage)+(listCount-1)*S;
			}
		}
		return result;
	}
}
