
namespace dggt
{
	template <typename T>
	T* cache_alloc(u32 count)
	{
		return (T*)cache_alloc(sizeof(T)*count);
	}

	template <typename T>
	b32 cache_free(T* ptr,u32 count)
	{
		return cache_free(ptr,sizeof(T)*count);
	}

	template <msize... SizeArgs>
	allocator<SizeArgs...>* create_alloc(alloc_t type,
			void* buff,msize size)
	{
		allocator<SizeArgs...>* result=0;
		switch (type)
		{
			case ALLOC_T_NULL:
				{
					null_alloc* a=
						cache_alloc<null_alloc>();
					*a=null_alloc();
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_LIN:
				{
					lin_alloc* a=
						cache_alloc<lin_alloc>();
					if (buff)
					{
						*a=lin_alloc(buff,size);
					}
					else
					{
						*a=lin_alloc();
					}
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_STACK:
				{
					stack_alloc* a=
						cache_alloc<stack_alloc>();
					if (buff)
					{
						*a=lin_alloc(buff,size);
					}
					else
					{
						*a=lin_alloc();
					}
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_POOL:
				{
					pool_alloc<SizeArgs...>* a=
						cache_alloc<pool_alloc<SizeArgs...>>();
					if (buff)
					{
						*a=pool_alloc<SizeArgs...>(buff,size);
					}
					else
					{
						*a=pool_alloc<SizeArgs...>();
					}
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_FREE:
				{
					free_alloc* a=
						cache_alloc<free_alloc>();
					if (buff)
					{
						*a=free_alloc(buff,size);
					}
					else
					{
						*a=free_alloc();
					}
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_STORE:
				{
					store_alloc<SizeArgs...>* a=
						cache_alloc<store_alloc<SizeArgs...>>();
					*a=store_alloc<SizeArgs...>();
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_TABLE:
				{
					table_alloc<SizeArgs...>* a=
						cache_alloc<table_alloc<SizeArgs...>>();
					*a=table_alloc<SizeArgs...>();
					result=(allocator<SizeArgs...>*)a;
				} break;
			case ALLOC_T_FALLBACK:
				{
					fallback_alloc<SizeArgs...>* a=
						cache_alloc<fallback_alloc<SizeArgs...>>();
					*a=fallback_alloc<SizeArgs...>();
					result=(allocator<SizeArgs...>*)a;
				} break;
		}
		return result;
	}

	template <msize... SizeArgs>
	allocator<SizeArgs...>* create_alloc(alloc_t type,msize size)
	{
		return create_alloc<SizeArgs...>(type,cache_alloc(size));
	}

	template <msize PrimaryArg,msize FallbackArg>
	allocator<PrimaryArg,FallbackArg>* create_alloc(alloc_t type,
			allocator<PrimaryArg>* primary,
			allocator<FallbackArg>* fallback)
	{
		allocator<PrimaryArg,FallbackArg>* result=0;

		if (type==ALLOC_T_FALLBACK)
		{
			result=create_alloc<PrimaryArg,FallbackArg>(type,0);
			if (result)
			{
				fallback_alloc<PrimaryArg,FallbackArg>* fallbackAlloc=
					(fallback_alloc<PrimaryArg,FallbackArg>*)result;
				fallbackAlloc->p=primary;
				fallbackAlloc->f=fallback;
			}
		}
		return result;
	}

	template <msize PrimaryArg,msize FallbackArg>
	allocator<PrimaryArg,FallbackArg>* create_alloc(alloc_t type,
			alloc_t primaryType,msize primarySize,
			alloc_t fallbackType,msize fallbackSize)
	{
		allocator<PrimaryArg,FallbackArg>* result=0;

		if (type==ALLOC_T_FALLBACK)
		{
			allocator<PrimaryArg>* p=
				create_alloc<PrimaryArg>(primaryType,primarySize);
			allocator<FallbackArg>* f=
				create_alloc<FallbackArg>(fallbackType,fallbackSize);
			allocator<PrimaryArg,FallbackArg>* result=
				create_alloc(type,p,f);
		}
		return result;
	}

	template <msize... SizeArgs>
	b32 destroy_alloc(allocator<SizeArgs...>* a)
	{
		b32 result=false;
		switch (a->type)
		{
			case ALLOC_T_NULL:
				{
					null_alloc* nullAlloc=
						(null_alloc*)a;
					result=cache_free(nullAlloc);
				} break;
			case ALLOC_T_LIN:
				{
					lin_alloc* linAlloc=
						(lin_alloc*)a;
					b32 buffFree=
						cache_free(linAlloc->buff,linAlloc->buffSize);
					b32 allocFree=cache_free(linAlloc);
					result=buffFree&&allocFree;
				} break;
			case ALLOC_T_STACK:
				{
					stack_alloc* stackAlloc=
						(stack_alloc*)a;
					b32 buffFree=
						cache_free(stackAlloc->buff,
								stackAlloc->buffSize);
					b32 allocFree=
						cache_free(stackAlloc);
					result=buffFree&&allocFree;
				} break;
			case ALLOC_T_POOL:
				{
					pool_alloc<SizeArgs...>* poolAlloc=
						(pool_alloc<SizeArgs...>*)a;
					b32 buffFree=
						cache_free(poolAlloc->buff,
								poolAlloc->buffSize);
					b32 allocFree=
						cache_free(poolAlloc);
					result=allocFree&&buffFree;
				} break;
			case ALLOC_T_FREE:
				{
					free_alloc* freeAlloc=
						(free_alloc*)a;
					b32 buffFree=
						cache_free(freeAlloc->buff,
								freeAlloc->buffSize);
					b32 allocFree=
						cache_free(freeAlloc);
				} break;
			case ALLOC_T_STORE:
				{
					store_alloc<SizeArgs...>* storeAlloc=
						(store_alloc<SizeArgs...>*)a;
					result=cache_free(storeAlloc);
				} break;
			case ALLOC_T_TABLE:
				{
					table_alloc<SizeArgs...>* tableAlloc=
						(table_alloc<SizeArgs...>*)a;
					*a=table_alloc<SizeArgs...>();
					result=cache_free(tableAlloc);
				} break;
			case ALLOC_T_FALLBACK:
				{
					fallback_alloc<SizeArgs...>* fallbackAlloc=
						(fallback_alloc<SizeArgs...>*)a;
					b32 primaryFree=
						cache_free(fallbackAlloc->p);
					b32 fallbackFree=
						cache_free(fallbackAlloc->f);
					b32 allocFree=
						cache_free(fallbackAlloc);
					result=primaryFree&&fallbackFree&&allocFree;
				} break;
		}
		return result;
	}
}
