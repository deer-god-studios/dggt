
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename T>
		idx_table_iter<T> get_def_idx_table_iter(idx_table<T>* idxTable)
		{
			return idx_table_iter<T>{
				idx_table_mem<T>{},idx_table_flag_mem{},
					0,0,idxTable};
		}
	}

	template <typename T,typename A>
	idx_table<T> create_idx_table(u32 capacity,A* allocator)
	{
		idx_table<T> result={create_array<T>(capacity,allocator),
			create_array<flag32>(capacity,allocator)};

		for (u32 i=0;i<get_capacity(result);++i)
		{
			result.flags[i]=IDX_EMPTY;
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> destroy_idx_table(idx_table<T>* table,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			result.tableMem=table->table;
			result.flagMem=table->flags;
			if (!is_coll_valid(destroy_array(table->table))&&
					!is_coll_valid(destroy_array(table->flags)))
			{
				result.table=0;
				result.tableMem=array<T>{};
				result.flagMem=array<flag32>{};
			}
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> add(idx_table<T>* table,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			if (get_count(table)>=get_capacity(table))
			{
				result=resize(table,2*get_capacity(table),allocator);
			}

			if (get_count(table)<get_capacity(table))
			{
				result.tableMem=table->table;
				result.flagMem=table->flags;
				result.currentHandle=table->nextHandle++;
				result.currentFlag=result.flagMem[result.currentHandle];
				result=get_iter(table);
			}
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> add(idx_table<T>* table,const T& val,A* allocator)
	{
		idx_table_iter<T> result=add(table,allocator);
		if (is_mem_valid(table))
		{
			*result=val;
			table->flags[result.currentHandle]=IDX_OCCUPIED;
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> remove(idx_table<T>* table,const T& val,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			for (idx_table_iter<T> it=get_iter(table);
					!it.is_end();++it)
			{
				if (*it==val)
				{
					result=remove(table,
							get_current(it),
							allocator);
					break;
				}
			}
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> remove(idx_table<T>* table,u32 handle,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table&&handle<get_count(table))
		{
			result=get_iter(table);
			result.currentHandle=handle;
			result.currentFlag=result.flagMem[result.currentHandle];
			if (get_count(table)>1)
			{
				table->table[handle]=table->table[table->nextHandle-1];
			}
			table->flags[table->nextHandle-1]=IDX_EMPTY;
			--table->nextHandle;
			if (get_load_factor<real32>(table)<0.25f)
			{
				result=resize(table,0.5f*get_capacity(table),allocator);
			}
		}
		return result;
	}

	template <typename T,typename A>
	idx_table_iter<T> clear(idx_table<T>* table,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			result=get_iter(table);
			for (idx_table_iter<T> it=get_iter(table);
					!it.is_end();++it)
			{
				it.flagMem[get_current(it)]=IDX_EMPTY;
				table->nextHandle=0;
			}
		}
		return result;
	}

	template <typename T>
	u32 get_count(const idx_table<T>* table)
	{
		return table?table->nextHandle:0;
	}

	template <typename T>
	idx_table_iter<T> get_iter(idx_table<T>* table)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			result.tableMem=table->tableMem;
			result.flagMem=table->flagMem;
			while (result.flagMem[result.currentHandle]==IDX_EMPTY&&
					!result.is_end())
			{
				++result.currentHandle;
			}
		}
		return result;
	}

	template <typename T>
	b32 contains(idx_table<T>* table,const T& item)
	{
		b32 result=false;
		if (table)
		{
			for (idx_table_iter<T> it=get_iter(table);
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

	template <typename T>
	u32 get_capacity(idx_table<T>* table)
	{
		return table?table->table.count:0;
	}

	template <typename F,typename T>
	F get_load_factor(idx_table<T>* table)
	{
		return get_capacity(table)?get_count(table)/get_capacity(table):0;
	}

	template <typename T,typename A>
	idx_table_iter<T> resize(idx_table<T>* table,u32 newCapacity,A* allocator)
	{
		idx_table_iter<T> result=
			dggt_internal_::get_def_idx_table_iter(table);
		if (table)
		{
			result.tableMem=table->table;
			result.flagMem=table->flags;

			b32 resizeTable=is_coll_valid(resize(&table->table,
						newCapacity,allocator));
			b32 resizeFlags=is_coll_valid(resize(&table->flags,
						newCapacity,allocator));
			if (resizeTable&&resizeFlags)
			{
				result=get_iter(table);
			}
		}
		return result;
	}

}
