#ifndef _DGGT_COLL_ITER_H_

/*
 * TODO: change advance to increment (or add increment).
 * TODO: change free to return a valid begin iterator.
 */

namespace dggt
{
	template <typename Settings>
	struct iterator;

	template <typename Settings>
	b32 is_end(const iterator<Settings>& it);
	template <typename Settings>
	b32 is_begin(const iterator<Settings>& it);
	template <typename Settings>
	b32 increment(const iterator<Settings>& it);
	template <typename Settings>
	b32 decrement(const iterator<Settings>& it);

	template <typename T,typename M,typename C,typename K>
	struct iter_settings
	{
		typedef T val_type;
		typedef K key_type;
		typedef M mem_type;
		typedef C coll_type;
	};

	// T: underlying contained type.
	// M: container's memory back-store type.
	// C: container type.
	// K: key type.  anything that can be incremented and holds the
	// 		T value somehow. (eg. indexes, nodes, etc.)
	template <typename Settings>
	struct iterator
	{
		typedef typename Settings::val_type val_type;
		typedef typename Settings::key_type key_type;
		typedef typename Settings::mem_type mem_type;
		typedef typename Settings::coll_type coll_type;

		mem_type mem;
		coll_type* coll;
		key_type current;

		iterator(coll_type& coll,key_type& current)
			: coll(&coll),mem(coll.mem),current(current) { }
		iterator(coll_type& coll) : coll(&coll),
		mem(coll.mem),current(key_type()) { }
		iterator()
			: coll(0),mem(mem_type()),current(key_type()) { }

		b32 operator==(const iterator<Settings>& rhs)
		{
			return this==&rhs||
				(mem==rhs.mem&&
				 coll==rhs.coll&&
				 current==rhs.current);
		}

		b32 operator!=(const iterator<Settings>& rhs)
		{
			return !(this->operator==(rhs));
		}

		b32 is_end() const { return dggt::is_end(*this); }
		b32 is_begin() const { return dggt::is_begin(*this); }
		val_type& operator*() { return get(*this); }
		const val_type& operator*() const { return get(*this); }

		iterator<Settings>& operator--()
		{
			if (!dggt::is_begin(*this))
			{
				decrement(*this);
			}
			return *this;
		}

		iterator<Settings> operator--(int)
		{
			iterator<Settings> result=*this;
			this->operator--();
			return result;
		}


		iterator<Settings>& operator++()
		{
			if (!dggt::is_end(*this))
			{
				increment(*this);
			}
			return *this;
		}

		iterator<Settings> operator++(int)
		{
			iterator<Settings> result=*this;
			this->operator++();
			return result;
		}

		explicit operator mem_type() { return mem; }
	};

	template <typename Settings>
	b32 is_end(const iterator<Settings>& it)
	{
		return it.current.is_end();
	}

	template <typename Settings>
	b32 is_begin(const iterator<Settings>& it)
	{
		return it.current.is_begin();
	}

	template <typename Settings>
	b32 increment(iterator<Settings>& it)
	{
		b32 result=false;
		if (!is_end(it))
		{
			++it.current;
		}
		return false;
	}

	template <typename Settings>
	b32 advance(iterator<Settings>& it)
	{
		return increment(it);
	}

	template <typename Settings>
	b32 decrement(iterator<Settings>& it)
	{
		b32 result=false;
		if (!is_begin(it))
		{
			--it.current;
		}
		return result;
	}

	template <typename Settings>
	typename iterator<Settings>::val_type& get(iterator<Settings>& it)
	{
		return *it.current;
	}

	template <typename Settings>
	const typename iterator<Settings>::val_type& get(const iterator<Settings>& it)
	{
		return *it.current;
	}

	template <typename Settings>
	typename iterator<Settings>::val_type* get_ptr(iterator<Settings>& it)
	{
		return (typename iterator<Settings>::val_type*)it.current;
	}

	template <typename Settings>
	const typename iterator<Settings>::val_type* get_ptr(const iterator<Settings>& it)
	{
		return (typename iterator<Settings>::val_type*)it.current;
	}

	template <typename Settings>
	b32 is_coll_valid(const iterator<Settings>& it) { return it.coll!=0; }

	template <typename Settings>
	b32 is_mem_valid(const iterator<Settings>& it)
	{
		return is_coll_valid(it)&&
			it.mem==it.coll->mem;
	}

	template <typename Settings>
	b32 vindicate_mem(iterator<Settings>& it)
	{
		b32 result=false;
		if (is_coll_valid(it)&&
				!is_mem_valid(it))
		{
			it.mem=it.coll->mem;
		}
		return result;
	}

	template <typename Settings>
	typename iterator<Settings>::coll_type* get_coll(iterator<Settings>& it)
	{
		return it.coll;
	}

	template <typename Settings>
	typename iterator<Settings>::mem_type get_mem(iterator<Settings>& it)
	{
		return it.mem;
	}

	template <typename Settings>
	typename iterator<Settings>::key_type get_key(iterator<Settings>& it)
	{
		return it.current;
	}

	template <typename Settings,typename A>
	b32 free(A* a,iterator<Settings>& it)
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
