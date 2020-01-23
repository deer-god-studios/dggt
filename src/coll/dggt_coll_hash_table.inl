
namespace dggt
{

	template <typename K,typename V>
	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	is_end() const
	{
		return (currentIndex>=table.count)&&(currentNode==0);
	}

	b32 iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>::
	next()
	{
		b32 result=0;
		if (!is_end())
		{
		}
		return result;
	}

	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
	//iter<tnode<K,V>,hash_table<K,V>,blk<linked_list<tnode<K,V>>>>
}
