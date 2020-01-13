
namespace dggt
{
	namespace dggt_internal_
	{

	}

	template <typename T>
	stack<T> create_stack(blk<T> mem)
	{
		return stack<T>{mem,0,mem.count};
	}

	template <typename T,alloc_t A>
	stack<T> create_stack(allocator<A>* alloc,u32 capacity)
	{
		blk<T> mem=alloc->alloc<T>(capacity);
		return create_stack<T>(mem);
	}

	template <typename T,alloc_t A>
	stack_iter<T> push(stack<T>* stk,allocator<A>* alloc)
	{
	}
}
