#include "dggt_coll_uuids.h"

namespace dggt
{
	template <typename T,typename A>
	graph_node<T> create_graph_node(T val,A* allocator)
	{
		graph_node<T> result={};
		uuid newID=create_uuid(allocator);
		result.id=newID;
		result.val=val;
		return result;
	}

	template <typename T,typename A>
	b32 destroy_graph_node(graph_node<T> node,A* allocator)
	{
		return destroy_graph_node(node,allocator);
	}
}
