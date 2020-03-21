#ifndef _DGGT_COLL_GRAPH_H_

#include "dggt_coll_graph_node.h"
#include "dggt_coll_graph_edge.h"
#include "dggt_coll_array.h"

namespace dggt
{
	template <typename F,typename T>
	struct graph
	{
		typedef graph_node<T> node_type;
		typedef graph_edge<F,T> edge_type;
		typedef array<node_type> nodes_coll;
		typedef array<edge_type> edge_coll;

		nodes_coll nodes;
		edge_coll edges;
	};

	template <typename F,typename T>
	graph<F,T> create_graph();
}

#define _DGGT_COLL_GRAPH_H_
#endif
