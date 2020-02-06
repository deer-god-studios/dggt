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
	 * @brief A short way to write allocator<alloc_t::STORE_TABLE,SIZE>.
	 * @tparam SIZE The required store table size (ie. The number of different block size's that the allocator can handle.).
	 * */
	template <u32 SIZE=2048>
	using store_table_alloc=allocator<alloc_t::STORE_TABLE,SIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::FALLBACK,P,SIZE,F,FSIZE>.
	 * @tparam P The primary allocator type.
	 * @tparam SIZE The primary allocator size.
	 * @tparam F The fallback allocator type.
	 * @tparam FSIZE The fallback allocator size.
	 * */
	template <u32 P=alloc_t::STORE_TABLE,u32 SIZE=2048,
			 u32 F=alloc_t::LINEAR,u32 FSIZE=0>
	using fallback_alloc=allocator<alloc_t::FALLBACK,P,SIZE,F,FSIZE>;

	/*!
	 * @brief A short way to write allocator<alloc_t::FALLBACK,alloc_t::STORE_TABLE,TABLESIZE,alloc_t::LINEAR,LINEARSIZE>.
	 *
	 * This is a type of allocator where all memory comes off of the stack from a linear allocator and is recycled into a store table allocator.
	 * @tparam TABLESIZE The number of memory recycling slots in the store table allocator.  Defaults to 2048.
	 * @tparam LINEARSIZE The amount of memory off the stack to allocate from the linear allocator.  Defaults to 10 KB.
	 * */
	template <u32 TABLESIZE=2048,u32 LINEARSIZE=KB(10)>
	using scratch_alloc=allocator<alloc_t::FALLBACK,alloc_t::STORE_TABLE,TABLESIZE,alloc_t::LINEAR,LINEARSIZE>;

	/*!
	 * @brief Initializes the library's memory cache.
	 *
	 * Most memory requested comes from this memory cache.
	 * @param cacheSize The amount of memory to allocate.
	 * */
	void cache_init(msize cacheSize);

	/*!
	 * @brief Checks if the library's memory cache has been allocated.
	 * @return Nonzero if the cache is initialized, zero otherwise.
	 * */
	b32 cache_is_initialized();

	/*!
	 * @brief Frees all cache memory.
	 * */
	void cache_shutdown();

	/*!
	 * @brief Frees the currently allocated cache if initialized and initializes a new block of memory.
	 * @param cacheSize The amount of memory to allocate for the cache.
	 * */
	void cache_reinit(msize cacheSize);

	/*!
	 * @brief Returns the amount of cache memory available for allocation.
	 * @return The amount of available cache memory.
	 * */
	msize available_cache_mem();

	/*!
	 * @brief Returns the amount of cache memory in use by the library (or user).
	 * @return The amount of used cache memory.
	 * */
	msize used_cache_mem();

	/*!
	 * @brief Returns the total amount of cache memory.
	 * @return The amount of available cache memory plus the amount of used cache memory.
	 * */
	msize cache_size();

	/*!
	 * @brief Allocates memory from the cache.
	 *
	 * If successful, this function is guaranteed to allocate at least the requested amount.
	 * @param size A pointer to an integer representing the requested memory size.  May be set to a larger value if more memory than requested was allocated. 
	 * @return If successful, this value is a pointer to the beginning of the requested memory block, otherwise it returns a null pointer.
	 * */
	void* cache_alloc(msize* size);

	/*!
	 * @brief Allocates memory from the cache.
	 *
	 * If successful, this function is guaranteed to allocate at least the requested amount.
	 * */
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
