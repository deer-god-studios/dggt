#ifndef _DGGT_COLL_GRAPH_H_

#include "dggt_coll_graph_node.h"
#include "dggt_coll_graph_edge.h"
#include "dggt_coll_sllist.h"
#include "dggt_coll_array.h"

namespace dggt
{
	template <typename T>
	using node_type=graph_node<T>;

	template <typename F,typename T>
	using edge_type=graph_edge<F,T>;

	template <typename T>
	using node_arr=array<node_type<T>>;

	template <typename F,typename T>
	using edge_list=sllist<edge_type<F,T>>;

	template <typename F,typename T>
	using edge_list_arr=array<edge_list<F,T>>;

	template <typename F,typename T>
	using graph_edge_iter=list_iter<edge_type<F,T>>;

	template <typename T>
	using graph_node_iter=array_iter<node_type<T>>;

	template <typename F,typename T>
	struct graph_mem
	{
		node_arr<T> nodes;
		edge_list_arr<F,T> edges;
	};

	template <typename F,typename T>
	struct graph
	{
		graph_mem<F,T> table;
		u32 nodeCount;
		u32 edgeCount;
		uid topID;
	};

	template <typename F,typename T,typename A>
	graph<F,T> create_graph(A* allocator);

	template <typename F,typename T>
	graph_node_iter<F,T> get_node(graph<F,T>* grph,uid index);

	template <typename F,typename T>
	const graph_node_iter<F,T> get_node(const graph<F,T>* grph,uid index);

	template <typename F,typename T>
	graph_edge_iter<F,T> get_edge(graph<F,T>* grph,
			uid start,uid end);

	template <typename F,typename T>
	const graph_edge_iter<F,T> get_edge(const graph<F,T>* grph,
			uid start,uid end);

	template <typename F,typename T>
	graph_node_iter<F,T> get_node_iter(graph<F,T>* grph);

	template <typename F,typename T>
	graph_node_iter<F,T> get_edge_iter(graph<F,T>* grph,uid node);

	template <typename F,typename T,typename A>
	graph_node_iter<F,T> add_node(graph<F,T>* grph,T val,A* allocator);

	template <typename F,typename T,typename A>
	graph_node_iter<F,T> remove_node(graph<F,T>* grph,uid node,
			A* allocator);

	template <typename F,typename T,typename A>
	graph_edge_iter<F,T> add_edge(graph<F,T>* grph,
			uid start,uid end,F weight,T val,A* allocator);

	template <typename F,typename T,typename A>
	graph_edge_iter<F,T> remove_edge(graph<F,T>* grph,
			uid start,uid end,A* allocator);

	template <typename F,typename T>
	u32 get_count(graph<F,T>* grph);

	template <typename F,typename T>
	u32 get_node_count(graph<F,T>* grph);

	template <typename F,typename T>
	u32 get_edge_count(graph<F,T>* grph);
}

#include "dggt_coll_graph.inl"

#define _DGGT_COLL_GRAPH_H_
#endif
