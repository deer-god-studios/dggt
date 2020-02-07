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
	 * If successful, this function is guaranteed to allocate at least the
	 * requested amount.
	 * @param size The size to allocate.
	 * */
	blk<void> cache_alloc(msize size);

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
	 * @brief Creates an allocator which draws from cache memory of a desired
	 * size.
	 * @tparam A An allocator type enum value.
	 * @param size The memory size available to the allocator.
	 * @return The newly created allocator.
	 * */
	template <alloc_t A>
	allocator<A> create_alloc(msize size);

	/*!
	 * @brief Creates an allocator which draws from stack memory of a desired
	 * size.
	 * @tparam A An allocator type enum value.
	 * @tparam SIZE The stack memory size.
	 * @return The newly created allocator.
	 * */
	template <alloc_t A,u32 SIZE>
	allocator<A,SIZE> create_alloc();

	/*!
	 * @brief Creates a fallback allocator consisting of two allocators both
	 * with, under normal circumstance, memory off the heap.
	 * @tparam P The primary allocator type enum value.
	 * @tparam F The primary allocator type enum value.
	 * @param primaryAlloc A pointer to the primary allocator.
	 * @param fallbackAlloc A pointer to the fallback allocator.
	 * @return The newly created allocator.
	 * */
	template <alloc_t P,alloc_t F>
	allocator<alloc_t::FALLBACK,P,F> create_alloc(
			allocator<P>* primaryAlloc,
			allocator<F>* fallbackAlloc);

	/*!
	 * @brief Creates a fallback allocator consisting of a primary allocator
	 * with a template SIZE argument and a fallback allocator with none.
	 * @tparam P The primary allocator type enum value.
	 * @tparam SIZE The stack memory size.
	 * @tparam F The primary allocator type enum value.
	 * @param primaryAlloc A pointer to the primary allocator.
	 * @param fallbackAlloc A pointer to the fallback allocator.
	 * @return The newly created allocator.
	 * */
	template <alloc_t P,u32 SIZE,alloc_t F>
	allocator<alloc_t::FALLBACK,P,SIZE,F> create_alloc(
			allocator<P,SIZE>* primaryAlloc,
			allocator<F>* fallbackAlloc);

	/*!
	 * @brief Creates a fallback allocator consisting of two allocators both
	 * of which draw memory off the stack under normal circumstances.
	 * @tparam P The primary allocator type enum value.
	 * @tparam PSIZE The primary allocator stack size.
	 * @tparam F The fallback allocator type enum value.
	 * @tparam FSIZE The fallback allocator stack size.
	 * @param primaryAlloc A pointer to the primary allocator.
	 * @param fallbackAlloc A pointer to the fallback allocator.
	 * @return The newly created fallback allocator.
	 * */
	template <alloc_t P,u32 PSIZE,alloc_t F,u32 FSIZE>
	allocator<alloc_t::FALLBACK,P,PSIZE,F,FSIZE> create_alloc(
			allocator<P,PSIZE>* primaryAlloc,
			allocator<F,FSIZE>* fallbackAlloc);

	/*!
	 * @brief Creates a pool allocator which draws from cache memory.
	 * @param size The size of cache memory the pool will have access to.
	 * @param blockSize The size of each block of memory the pool will
	 * allocate.
	 * @return The newly created pool allocator.
	 * */
	allocator<alloc_t::POOL> create_alloc(msize size,msize blockSize);

	/*!
	 * @brief Creates a store allocator (recycles memory previously freed into
	 * it.).
	 * @param blockSize The block size the store allocator can free and
	 * allocate.
	 * @return The newly created store allocator.
	 * */
	allocator<alloc_t::STORE> create_alloc(msize blockSize);

	/*!
	 * @brief Destroys an allocator by freeing it's underlying memory back
	 * to the cache if applicable.
	 * @tparam A The allocator type enum value.
	 * @param A pointer to the allocator to destroy.
	 * @return Nonzero if the allocator was successfully destroyed, zero
	 * otherwise.
	 * */
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
