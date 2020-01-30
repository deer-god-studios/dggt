
namespace dggt
{
	template <u32 P,u32 F>
	void* allocator<alloc_t::FALLBACK,P,F>::alloc(msize* size)
	{
		void* result=0;
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 F>
	blk<void> allocator<alloc_t::FALLBACK,P,F>::alloc(msize size)
	{
		blk<void> result=blk<void>();
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result.mem&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 F>
	template <typename T>
	T* allocator<alloc_t::FALLBACK,P,F>::alloc(u32* count)
	{
		T* result=0;
		if (p)
		{
			result=p->alloc(count);
		}
		if (!result&&f)
		{
			result=f->alloc(count);
		}
		return result;
	}

	template <u32 P,u32 F>
	template <typename T>
	blk<T> allocator<alloc_t::FALLBACK,P,F>::alloc(u32 count)
	{
		blk<T> result=blk<T>();
		if (p)
		{
			result=p->alloc(count);
		}
		if (!result&&f)
		{
			result=f->alloc(count);
		}
		return result;
	}

	template <u32 P,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,F>::free(void* ptr,msize size)
	{
		b32 result=0;
		if (p)
		{
			result=p->alloc(ptr,size);
		}
		if (!result&&f)
		{
			result=f->alloc(ptr,size);
		}
		return result;
	}

	template <u32 P,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,F>::free(blk<void> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}
	template <u32 P,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,F>::free(T* ptr,u32 count)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(ptr,count);
		}
		if (!result&&f)
		{
			result=f->free(ptr,count);
		}
		return result;
	}

	template <u32 P,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,F>::free(blk<T> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}

	template <u32 P,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,F>::clear()
	{
		b32 result=0;
		if (p)
		{
			result=p->clear();
		}
		if (!result&&f)
		{
			result=f->clear();
		}
		return result;
	}
	template <u32 P,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,F>::owns(const void* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=p->owns(ptr);
		}
		return result;
	}
	template <u32 P,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,F>::owns(const blk<void> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}
	template <u32 P,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,F>::owns(const T* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=f->owns(ptr);
		}
		return result;
	}

	template <u32 P,u32 F>
	template <typename T>	
	b32 allocator<alloc_t::FALLBACK,P,F>::owns(const blk<T> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}

	template <u32 P,u32 F>
	msize allocator<alloc_t::FALLBACK,P,F>::available_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->available_mem();
		}
		if (f)
		{
			result+=f->available_mem();
		}
		return result;
	}

	template <u32 P,u32 F>
	msize allocator<alloc_t::FALLBACK,P,F>::used_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->used_mem();
		}
		if (f)
		{
			result+=f->used_mem();
		}
		return result;
	}

	// "temp_fallback"

	template <u32 P,u32 SIZE,u32 F>
	void* allocator<alloc_t::FALLBACK,P,SIZE,F>::alloc(msize* size)
	{
		void* result=0;
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	blk<void> allocator<alloc_t::FALLBACK,P,SIZE,F>::alloc(msize size)
	{
		blk<void> result=blk<void>();
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result.mem&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	template <typename T>
	T* allocator<alloc_t::FALLBACK,P,SIZE,F>::alloc(u32* count)
	{
		T* result=0;
		if (p)
		{
			result=p->template alloc<T>(count);
		}
		if (!result&&f)
		{
			result=f->template alloc<T>(count);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	template <typename T>
	blk<T> allocator<alloc_t::FALLBACK,P,SIZE,F>::alloc(u32 count)
	{
		blk<T> result=blk<T>();
		if (p)
		{
			result=p->template alloc<T>(count);
		}
		if (!result&&f)
		{
			result=f->template alloc<T>(count);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::free(void* ptr,msize size)
	{
		b32 result=0;
		if (p)
		{
			result=p->alloc(ptr,size);
		}
		if (!result&&f)
		{
			result=f->alloc(ptr,size);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::free(blk<void> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}
	template <u32 P,u32 SIZE,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::free(T* ptr,u32 count)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(ptr,count);
		}
		if (!result&&f)
		{
			result=f->free(ptr,count);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::free(blk<T> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::clear()
	{
		b32 result=0;
		if (p)
		{
			result=p->clear();
		}
		if (!result&&f)
		{
			result=f->clear();
		}
		return result;
	}
	template <u32 P,u32 SIZE,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::owns(const void* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=p->owns(ptr);
		}
		return result;
	}
	template <u32 P,u32 SIZE,u32 F>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::owns(const blk<void> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}
	template <u32 P,u32 SIZE,u32 F>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::owns(const T* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=f->owns(ptr);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	template <typename T>	
	b32 allocator<alloc_t::FALLBACK,P,SIZE,F>::owns(const blk<T> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	msize allocator<alloc_t::FALLBACK,P,SIZE,F>::available_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->available_mem();
		}
		if (f)
		{
			result+=f->available_mem();
		}
		return result;
	}

	template <u32 P,u32 SIZE,u32 F>
	msize allocator<alloc_t::FALLBACK,P,SIZE,F>::used_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->used_mem();
		}
		if (f)
		{
			result+=f->used_mem();
		}
		return result;
	}
// "scratch_fallback"
	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	void* allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::alloc(msize* size)
	{
		void* result=0;
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	blk<void> allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::alloc(msize size)
	{
		blk<void> result=blk<void>();
		if (p)
		{
			result=p->alloc(size);
		}
		if (!result.mem&&f)
		{
			result=f->alloc(size);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>
	T* allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::alloc(u32* count)
	{
		T* result=0;
		if (p)
		{
			result=p->alloc(count);
		}
		if (!result&&f)
		{
			result=f->alloc(count);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>
	blk<T> allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::alloc(u32 count)
	{
		blk<T> result=blk<T>();
		if (p)
		{
			result=p->alloc(count);
		}
		if (!result&&f)
		{
			result=f->alloc(count);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::free(void* ptr,msize size)
	{
		b32 result=0;
		if (p)
		{
			result=p->alloc(ptr,size);
		}
		if (!result&&f)
		{
			result=f->alloc(ptr,size);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::free(blk<void> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}
	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::free(T* ptr,u32 count)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(ptr,count);
		}
		if (!result&&f)
		{
			result=f->free(ptr,count);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::free(blk<T> block)
	{
		b32 result=0;
		if (p)
		{
			result=p->free(block);
		}
		if (!result&&f)
		{
			result=f->free(block);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::clear()
	{
		b32 result=0;
		if (p)
		{
			result=p->clear();
		}
		if (!result&&f)
		{
			result=f->clear();
		}
		return result;
	}
	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::owns(const void* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=p->owns(ptr);
		}
		return result;
	}
	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::owns(const blk<void> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}
	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::owns(const T* ptr) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(ptr);
		}
		if (!result&&f)
		{
			result=f->owns(ptr);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	template <typename T>	
	b32 allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::owns(const blk<T> block) const
	{
		b32 result=0;
		if (p)
		{
			result=p->owns(block);
		}
		if (!result&&f)
		{
			result=f->owns(block);
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	msize allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::available_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->available_mem();
		}
		if (f)
		{
			result+=f->available_mem();
		}
		return result;
	}

	template <u32 P,u32 PSIZE,u32 F,u32 FSIZE>
	msize allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE>::used_mem() const
	{
		msize result=0;
		if (p)
		{
			result+=p->used_mem();
		}
		if (f)
		{
			result+=f->used_mem();
		}
		return result;
	}
}
