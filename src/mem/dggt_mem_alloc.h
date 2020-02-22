/*! @cond IncludeGuard */
#ifndef _DGGT_MEM_ALLOC_H_
/*! @endcond */

// TODO: implement is_valid(block) to check if a block has already 
// 		been 'freed'.
// TODO: allow pool allocs to free multiple blocks. 

#include "dggt_mem_blk.h"

 // TODO: fix allocators!  This enumerator shit sucks.

namespace dggt
{

	/*!
	 * @addtogroup mem
	 * @{
	 * */

	global const alloc_t ALLOC_T_NULL=0;
	global const alloc_t ALLOC_T_LINEAR=1;
	global const alloc_t ALLOC_T_STACK=2;
	global const alloc_t ALLOC_T_AUTOSTACK=3;
	global const alloc_t ALLOC_T_FREE=4;
	global const alloc_t ALLOC_T_POOL=5;
	global const alloc_t ALLOC_T_FALLBACK=6;
	global const alloc_t ALLOC_T_STORE=7;
	global const alloc_t ALLOC_T_STORE_TABLE=8;

	global const alloc_t ALLOC_T_LIB_END=ALLOC_T_STORE_TABLE;
	global const alloc_t ALLOC_T_BEGIN=ALLOC_T_LIB_END+1;

	template <alloc_t ALLOC_T,
			 template <u32...> SizeArgs=make_sequence<>>
	struct alloc_type
	{
		static constexpr alloc_t TYPE=ALLOC_T;
		using size_args=SizeArgs<u32...>;
	};
	template <alloc_t ALLOC_T,
			 template <u32...>> SizeArgs=make_sequence<>>
	struct make_alloc_type
	{
		using type=alloc_type<ALLOC_T,SizeArgs>;
	};

	template <u32 I,template <alloc_t,template <u32...>> A>
	struct alloc_type_get;

	template <u32 I,alloc_t TYPE,u32 HEAD,u32... REST>
	struct alloc_type_get<I,alloc_type<TYPE,sequece<HEAD,REST...>>>
	{
		static constexpr const u32 value=sequence_get<I-1,REST...>::value;
	};


	template <template <alloc_t,template <u32...>> A> 
	struct allocator
	{
		static constexpr const u32 TYPE=A::TYPE; 
		using size_args=A::size_args;
	};

	template <template <alloc_t,template <u32...>> A>
	blkv alloc(allocator<ALLOC_T,S...>* a,msize size=4);
	
	template <template <alloc_t,template <u32...>> A>
	void* alloc(allocator<ALLOC_T,S...>* a,msize* size=0);

	template <typename T,template <alloc_t,template <u32...>> A>
	blk<T> alloc(allocator<ALLOC_T,S...>* a,u32 count=1);

	template <typename T,template <alloc_t,template <u32...>> A>
	T* alloc(allocator<ALLOC_T,S...>* a,u32* count=0);

	template <template <alloc_t,template <u32...>> A>
	b32 free(allocator<ALLOC_T,S...>* a,void* ptr,msize size);
	
	template <template <alloc_t,template <u32...>> A>
	b32 free(allocator<ALLOC_T,S...>* a,blkv block);

	template <typename T,template <alloc_t,template <u32...>> A>
	b32 free(allocator<ALLOC_T,S...>* a,T* ptr,u32 count);

	template <typename T,template <alloc_t,template <u32...>> A>
	b32 free(allocator<ALLOC_T,S...>* a,blk<T> block);

	template <template <alloc_t,template <u32...>> A>
	b32 clear(allocator<ALLOC_T,S...>* a);

	template <template <alloc_t,template <u32...>> A>
	b32 owns(const allocator<ALLOC_T,S...>* a,const void* ptr,msize size);

	template <template <alloc_t,template <u32...>> A>
	b32 owns(const allocator<ALLOC_T,S...>* a,const blkv block);

	template <typename T,template <alloc_t,template <u32...>> A>
	b32 owns(const allocator<ALLOC_T,S...>* a,const blk<T> block);
	
	template <typename T,template <alloc_t,template <u32...>> A>
	b32 owns(const allocator<ALLOC_T,S...>* a,const T* ptr,u32 count);

	template <template <alloc_t,template <u32...>> A>
	stack_state save_stack(allocator<ALLOC_T,S...>* a);

	template <template <alloc_t,template <u32...>> A>
	b32 restore_stack(allocator<ALLOC_T,S...>* a,stack_state state);

	template <template <alloc_t,template <u32...>> A>
	b32 is_stack_balanced(allocator<ALLOC_T,S...>* a);

	template <template <alloc_t,template <u32...>> A>
	msize used_mem(allocator<ALLOC_T,S...>* a);

	template <template <alloc_t,template <u32...>> A>
	msize available_mem(allocator<ALLOC_T,S...>* a);

	template <template <alloc_t,template <u32...>> A>
	u32 get_block_size(allocator<ALLOC_T,S...>* a);
}

//#include "dggt_mem_alloc.inl"

/*! @cond IncludeGuard */
#define _DGGT_MEM_ALLOC_H_
#endif
/*! @endcond  */
