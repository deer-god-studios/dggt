/*!
 * @file mem/dggt_mem.h
 * @brief The public interface of the @ref mem.
 * */
/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_H_
/*! @endcond */

#include "dggt_mem_defines.h"
#include "dggt_mem_alloc.h"
#include "dggt_mem_lin_alloc.h"
#include "dggt_mem_stack_alloc.h"
#include "dggt_mem_autostack_alloc.h"
#include "dggt_mem_pool_alloc.h"
#include "dggt_mem_free_list_alloc.h"
#include "dggt_mem_fallback_alloc.h"
#include "dggt_mem_store_alloc.h"
#include "dggt_mem_store_table_alloc.h"

// TODO: Rearange/refactor allocator template arguments.

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
	 * If successful, this function is guaranteed to allocate at least the
	 * requested amount.
	 * @param size The size to allocate.
	 * */
	blkv cache_alloc(msize size);

	/*!
	 * @brief Frees cache memory from a previous cache_alloc call.
	 * @param ptr Address of the cache memory.
	 * @param size Memory size.
	 * @return Nonzero if the memory was successfully freed, zero if not.
	 * */
	b32 cache_free(void* ptr,msize size);

	/*!
	 * @brief Frees a block of cache memory from a previous cache_alloc call.
	 * @param block Memory block.
	 * @return Nonzero if the block was successfully freed, zero if not.
	 * */
	b32 cache_free(blk<void> block);

	/*!
	 * @brief Frees all previously allocated cache memory.
	 * */
	void cache_clear();

	/*!
	 * @brief Allocates memory from the cache.
	 *
	 * If successful, this function is guaranteed to allocate at least the
	 * requested amount.
	 * @tparam The type to allocate.
	 * @param count A pointer to the requested count (ie. number of T
	 * objects.).
	 * @return A pointer to memory if successfull and a null pointer otherwise. 
	 * */
	template <typename T>
	T* cache_alloc(u32* count);

	/*!
	 * @brief Allocates a block of memory from the cache.
	 *
	 * If successfull, this function is guaranteed to allocate at least the
	 * requested amount.
	 * @tparam The type to allocate.
	 * @param count The number to of items allocate.
	 * @return A block of memory if successfull, null block otherwise.
	 * */
	template <typename T>
	blk<T> cache_alloc(u32 count);

	/*!
	 * @brief Frees a block of cache memory.
	 * @tparam T The block's underlying type.
	 * @param block The block to free.
	 * @return Nonzero if the block was successfully freed, zero otherwise.
	 * */
	template <typename T>
	b32 cache_free(blk<T> block);

	/*!
	 * @brief Frees cache memory count T items large.
	 * @tparam T The memory type.
	 * @param ptr The memory address.
	 * @param count The number of T items.
	 * @return Nonzero if the block was successfully freed, zero otherwise.
	 * */
	template <typename T>
	b32 cache_free(T* ptr,u32 count);

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
