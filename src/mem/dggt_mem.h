/*!
 * @file mem/dggt_mem.h
 * @brief The public interface of the @ref mem.
 * */
/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_H_
/*! @endcond */

#include "dggt_mem_defines.h"
#include "dggt_mem_alloc.h"
#include "dggt_mem_linear_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_autostack_alloc.h"
#include "dggt_mem_pool_alloc.h"
#include "dggt_mem_free_list_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_store_table_alloc.h"
#include "dggt_mem_fallback_alloc.h"

namespace dggt
{
	/*!
	 * @addtogroup dggt
	 * @{
	 * */
	/*!
	 * @addtogroup mem
	 * @{
	 * */

	/*!
	 * @brief A short way to write allocator<alloc_t::LINEAR,SIZE>.
	 * @tparam SIZE The optional memory stack size (pass 0 for heap allocation.).
	 * */
	template <u32 SIZE=0>
	using lin_alloc=allocator<alloc_t::LINEAR,SIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::STACK,SIZE>.
	 * @tparam SIZE The optional memory stack size (pass 0 for heap allocation.).
	 * */
	template <u32 SIZE=0>
	using stack_alloc=allocator<alloc_t::STACK,SIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::POOL,SIZE>.
	 * @tparam SIZE The optional memory stack size (pass 0 for heap allocation.).
	 * */
	template <u32 SIZE=0>
	using pool_alloc=allocator<alloc_t::POOL,SIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::FREE_LIST,SIZE>.
	 * @tparam SIZE The optional memory stack size (pass 0 for heap allocation.).
	 * */
	template <u32 SIZE=0>
	using free_list_alloc=allocator<alloc_t::FREE_LIST,SIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::FREE_LIST,SIZE>.
	 * @tparam SIZE The optional block size (pass 0 for run-time block size.).
	 * */
	template <u32 SIZE=0>
	using store_alloc=allocator<alloc_t::STORE,SIZE>;

	/*!
	 * */
	template <u32 SIZE=2048>
	using store_table_alloc=allocator<alloc_t::STORE_TABLE,SIZE>;

	template <u32 P=alloc_t::STORE_TABLE,u32 SIZE=2048,
			 u32 F=alloc_t::LINEAR,u32 FSIZE=0>
	using fallback_alloc=allocator<alloc_t::FALLBACK,P,SIZE,F,FSIZE>;

	template <u32 TABLESIZE=2048,u32 LINEARSIZE=KB(10)>
	using scratch_alloc=allocator<alloc_t::FALLBACK,alloc_t::STORE_TABLE,TABLESIZE,alloc_t::LINEAR,LINEARSIZE>;

	void cache_init(msize cacheSize);
	b32 cache_is_initialized();
	void cache_shutdown();
	void cache_reinit(msize cacheSize);
	msize available_cache_mem();
	msize used_cache_mem();
	msize cache_size();
	void* cache_alloc(msize* size);
	blk<void> cache_alloc(msize size);
	b32 cache_free(void* ptr,msize size);
	b32 cache_free(blk<void> block);
	void cache_clear();

	template <typename T>
	T* cache_alloc(u32* count);
	template <typename T>
	blk<T> cache_alloc(u32 count);
	template <typename T>
	b32 cache_free(blk<T> block);
	template <typename T>
	b32 cache_free(T* ptr,u32 count);

	template <alloc_t A>
	allocator<A> create_alloc(msize size);
	template <alloc_t A,u32 SIZE>
	allocator<A,SIZE> create_alloc();

	template <alloc_t P,alloc_t F>
	allocator<alloc_t::FALLBACK,P,F> create_alloc(
			allocator<P>* primaryAlloc,
			allocator<F>* fallbackAlloc);

	template <alloc_t P,u32 SIZE,alloc_t F>
	allocator<alloc_t::FALLBACK,P,SIZE,F> create_alloc(
			allocator<P,SIZE>* primaryAlloc,
			allocator<F>* fallbackAlloc);

	template <alloc_t P,u32 PSIZE,alloc_t F,u32 FSIZE>
	allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE> create_alloc(
			allocator<P,PSIZE>* primaryAlloc,
			allocator<F,FSIZE>* fallbackAlloc);

	allocator<alloc_t::POOL> create_alloc(msize size,msize blockSize);
	allocator<alloc_t::STORE> create_alloc(msize blockSize);

	template <alloc_t A>
	b32 destroy_alloc(allocator<A>* alloc);

	/*!
	 * @}
	 * */
	/*!
	 * @}
	 * */
}


#include "dggt_mem.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_H_
#endif
/*! @endcond */
