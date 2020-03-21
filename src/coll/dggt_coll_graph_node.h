#ifndef _DGGT_COLL_GRAPH_NODE_H_

#include "defines/dggt_defines.h"
#include "types/dggt_types.h"

namespace dggt
{
	global const uid INVALID_NODE=MAX_U32;

	template <typename T>
	struct graph_node
	{
		uuid id;
		T val;
	};

	template <typename T,typename A>
	graph_node<T> create_graph_node(T val,A* allocator=0);

	template <typename T,typename A>
	b32 destroy_graph_node(graph_node<T> node,A* allocator=0);
}

#include "dggt_coll_graph_node.inl"

#define _DGGT_COLL_GRAPH_NODE_H_
#endif
