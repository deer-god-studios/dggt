#ifndef _DGGT_COLL_GRAPH_EDGE_H_

#include "dggt_coll_graph_node.h"

namespace dggt
{
	template <typename F,typename T>
	struct graph_edge
	{
		uuid nodeA;
		uuid nodeB;
		F weight;
		T val;
	};

	template <typename F,typename T>
	graph_edge create_graph_edge(uuid nodeA,uuid nodeB,F weight,T val)
	{
		return graph_edge<F,T>{nodeA,nodeB,weight,val};
	}
}

#define _DGGT_COLL_GRAPH_EDGE_H_
#endif
