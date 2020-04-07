
namespace dggt
{
	namespace dggt_internal_
	{
		template <typename F,typename T>
		graph_node_iter<F,T> get_def_graph_node_iter(graph<F,T>* grph)
		{
			graph_node_iter<F,T> result={};
			if (grph)
			{
				result.arr=grph->table.nodes;
			}
			return result;
		}

		template <typename F,typename T>
		graph_edge_iter<F,T> get_def_graph_edge_iter(graph<F,T>* grph,
				uid node)
		{
			graph_edge_iter<F,T> result={};
			if (grph)
			{
				result.list=&grph->table.nodes[node];
			}
			return result;
		}
	}

	template <typename F,typename T,typename A>
	graph<F,T> create_graph(A* allocator)
	{
		graph<F,T> result={};
		if (allocator)
		{
			node_arr<T> nodes=
				create_array<node_type<T>>(2,allocator);
			edge_list_arr<F,T> edges=
				create_array<edge_list<F,T>>(2,allocator);
			for (u32 i=0;i<get_capacity(&edges);++i)
			{
				edges[i]=create_list<edge_type<F,T>>();
			}
			result.nodes=nodes;
			result.edges=edges;
			result.count=0;
		}
		return result;
	}

	template <typename F,typename T>
	graph_node_iter<F,T> get_node(graph<F,T>* grph,uid index)
	{
		graph_node_iter<F,T> result=
			dggt_internal_::get_def_graph_node_iter(grph);
		if (grph&&index<get_count(grph))
		{
			result.current=index;
			result.table=grph->table.nodes;
		}
		return result;
	}

	template <typename F,typename T>
	const graph_node_iter<F,T> get_node(const graph<F,T>* grph,uid index)
	{
		const graph<F,T>* constGrph=grph;
		return get_node(constGrph,index);
	}

	template <typename F,typename T>
	graph_edge_iter<F,T> get_edge(graph<F,T>* grph,
			uid start,uid end)
	{
		graph_edge_iter<F,T> result=dggt_internal_::get_def_graph_edge_iter(
				grph);
		if (grph)
		{
			edge_list<F,T>& list=grph->table.edges[start];
			result=get_iter(&list);
			while (!result.is_end()&&(*result).end!=end)
			{
				++result;
			}
		}
		return result;
	}

	template <typename F,typename T>
	const graph_edge_iter<F,T> get_edge(const graph<F,T>* grph,
			uid start,uid end)
	{
		const graph<F,T>* constGrph=grph;
		return get_edge(constGrph,start,end);
	}

	template <typename F,typename T>
	graph_node_iter<F,T> get_node_iter(graph<F,T>* grph)
	{
		graph_edge_iter<F,T> result=dggt_internal_::get_def_graph_edge_iter(
				grph);
		if (grph)
		{	
			result=get_iter(&grph->table.nodes);
		}
		return result;
	}

	template <typename F,typename T>
	graph_node_iter<F,T> get_edge_iter(graph<F,T>* grph,uid node)
	{
		graph_edge_iter<F,T> result=dggt_internal_::get_def_graph_edge_iter(
				grph);
		if (grph)
		{
			result=get_iter(&grph->table.edges);
		}
		return result;
	}

	template <typename F,typename T,typename A>
	graph_node_iter<F,T> add_node(graph<F,T>* grph,T val,A* allocator)
	{
		graph_node_iter<F,T> result=dggt_internal_::get_def_node_iter(grph);
		
		if (grph)
		{
			uid newID=++grph->topID;
			if (newID>=get_capacity(grph->table.nodes))
			{
				resize(&grph->table.nodes,2*get_capacity(grph),allocator);
				resize(&grph->table.edges,2*get_capacity(grph),allocator);
			}
			graph_node<F,T> newNode=graph_node<T>{newID,val};
			grph->table.nodes[newID]=newNode;
			result.current=newID;
			result.table=grph->table.nodes;
			++grph->count;
		}

		return result;
	}

	template <typename F,typename T,typename A>
	graph_node_iter<F,T> remove_node(graph<F,T>* grph,uid node,A* allocator)
	{
		graph_node_iter<F,T> result=dggt_internal_::get_def_node_iter(grph);
		
		if (grph)
		{
			if (node<get_capacity(grph))
			{
				grph->table.nodes[node]=graph_node<T>{};
				--grph->count;
				if (get_load_factor<F>(grph)<0.5f)
				{
					resize(&grph->table.nodes,0.25f*get_capacity(grph),
							allocator);
					resize(&grph->table.edges,0.25f*get_capacity(grph),
							allocator);
				}
			}
		}

		return result;
	}

	template <typename F,typename T,typename A>
	graph_edge_iter<F,T> add_edge(graph<F,T>* grph,
			uid start,uid end,F weight,T val,A* allocator)
	{
		graph_node_iter<F,T> result=
			dggt_internal_::get_def_node_iter(grph);
		if (grph)
		{
			if (start>=get_capacity(&grph->table.nodes)||
					end>=get_capacity(&grph->table.edges))
			{
				resize(&grph->table.nodes,2*get_capacity(&grph->table.nodes),
						allocator);
				resize(&grph->table.nodes,2*get_capacity(&grph->table.edges),
						allocator);
			}
			graph_edge<F,T> startEdge=create_graph_edge(start,end,
					weight,val);
			graph_edge<F,T> endEdge=create_graph_edge(end,start,
					weight,val);
			push(&grph->table.edges[start],startEdge,allocator);
			push(&grph->table.edges[end],endEdge,allocator);
			++grph->edgeCount;
			result=get_edge_iter(grph,start);
		}
		return result;
	}

	template <typename F,typename T,typename A>
	graph_edge_iter<F,T> remove_edge(graph<F,T>* grph,uid start,uid end,
			A* allocator)
	{
		graph_edge_iter<F,T> result=dggt_internal_::get_def_edge_iter(grph);
		if (grph)
		{
			edge_list<F,T> startList=grph->table.edges[start];
			edge_list_iter<F,T> startListIter=get_iter(&startList);
			while (!startListIter.is_end())
			{
				if ((*startListIter).end==end)
				{

				}
				++startListIter;
			}
			edge_list<F,T> endList=grph->table.edges[end];
		}
		return result;
	}

	template <typename F,typename T>
	u32 get_count(graph<F,T>* grph)
	{
		return grph->nodeCount;
	}

	template <typename F,typename T>
	u32 get_node_count(graph<F,T>* grph)
	{
		return get_count(grph);
	}
	template <typename F,typename T>
	u32 get_edge_count(graph<F,T>* grph)
	{
		return grph->edgeCount;
	}
}
