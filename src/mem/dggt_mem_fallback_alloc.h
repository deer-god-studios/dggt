#ifndef _DGGT_MEM_FALLBACK_ALLOC_H_

#include "dggt_mem_alloc.h"

namespace dggt
{
	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	struct allocator<ALLOC_T_FALLBACK,
	PTYPE,PU32...,PTYPES...,
	FTYPE,FU32s...,FTYPES>
	{
		static const u32 TYPE=ALLOC_T_FALLBACK;
		typedef allocator<PTYPE,PU32s...,PTYPES...> palloc;
		typedef allocator<FTYPE,FU32s...,FTYPES...> falloc;

		palloc* p;
		falloc* f;

		allocator();
		allocator(palloc* primary,falloc* secondary);
	};

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	using fallback_alloc=
	allocator<ALLOC_T_FALLBACK,
	PTYPE,PU32s...,PTYPES,
	FTYPE,FU32s...,FTYPES...>;

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	void* alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			msize* size=0);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	blkv alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			msize size=4);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	T* alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			u32* count=0);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	blk<T> alloc(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			u32 count=1);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			void* ptr,
			msize size);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			blkv block);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			T* ptr,
			u32 count);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 free(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			blk<T> block);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 clear(
			fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const void* ptr,
			msize size);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const blkv block);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const T* ptr,
			u32 count);

	template <typename T,u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 owns(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			const blk<T> block);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	msize available_mem(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	msize used_mem(
			const fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	stack_state save_stack(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 restore_stack(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a,
			stack_state state);

	template <u32 PTYPE,u32... PU32s,typename... PTYPES,
			 u32 FTYPE,u32... FU32s,typename... FTYPES>
	b32 is_stack_balanced(fallback_alloc<PTYPE,PU32s...,PTYPES...,FTYPE,FU32s...,FTYPES...>* a);

}

#include "dggt_mem_fallback_alloc.inl"

#define _DGGT_MEM_FALLBACK_ALLOC_H_
#endif
