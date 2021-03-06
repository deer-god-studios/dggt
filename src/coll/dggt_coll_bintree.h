#ifndef _DGGT_COLL_BIN_TREE_H_

namespace dggt
{
	template <typename T>
	struct tree_node
	{
		T val;
		tree_node<T>* left;
		tree_node<T>* right;
	};

	template <typename T>
	struct bin_tree
	{
		tree_node<T>* root;
	};
}

#define _DGGT_COLL_BIN_TREE_H_
#endif
