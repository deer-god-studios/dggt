
namespace dggt
{
	namespace dggt_internal_
	{
		global uuid topUUID=0;
		global queue<uuid> availableIDs_;
		global queue<uuid>* availableIDs=&availableIDs_;
		global b32 isInit=false;

		void uuid_init()
		{
			availableIDs=create_queue(allocator);
			isInit=true;
		}

		uuid get_next_uuid()
		{
			return topUUID++;
		}
	}

	template <typename A>
	uuid32 create_uuid(A* allocator)
	{
		uuid32 result=NULL_UUID;
		if (allocator==0)
		{
			allocator=get_cache_alloc();
		}
		if (!dggt_internal_::isInit)
		{
			dggt_internal_::uuid_init();

		}
		if (get_count(availableIDs))
		{
			result=get(dequeue(availableIDs,allocator));
		}
		else
		{
			result=get_next_uuid();
		}

		return result;
	}

	template <typename A=free_alloc>
	b32 destroy_uuid(uuid32 id,A* allocator)
	{
		b32 result=true;
		if (allocator==0)
		{
			allocator=get_cache_alloc();
		}
		if (!dggt_internal_::isInit)
		{
			uuid_init();
		}
		enqueue(dggt_internal_::availableIDs,allocator);
		return result;
	}
}
