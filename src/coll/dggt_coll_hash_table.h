#ifndef _DGGT_COLL_HASH_TABLE_H_

#include "dggt_coll_linked_list.h"
#include "mem/dggt_mem_blk.h"

namespace dggt
{
	template <typename K>
	u32 prehash(const K& key);

	template <>
	u32 prehash(const u32& key);

	template <typename K,typename V>
	struct table_pair
	{
		K key_;
		V val_;

		table_pair() { }
		table_pair(K key,V val)
			: key_(key),val_(val) { }

		const K& get_key() { return key_; }
		V& get_val() { return val_;}
		const V& get_val() const { return val_;}

		b32 operator==(const table_pair& other)
		{
			return key_==other.key_;
		}
	};

	template <typename K,typename V>
	struct hash_table;

	template <typename K,typename V>
	using table_bucket=linked_list<table_pair<K,V>>;

	template <typename K,typename V>
	using bucket_iter=list_iter<table_pair<K,V>>;

	template <typename K,typename V>
	using table_blk=blk<table_bucket<K,V>>;

	template <typename K,typename V>
	using table_node=slnode<table_pair<K,V>>;

	template <typename K,typename V>
	using table_iter=iter<table_pair<K,V>,hash_table<K,V>,table_blk<K,V>>;

	template <typename K,typename V>
	struct iter<table_pair<K,V>,hash_table<K,V>,table_blk<K,V>> // wtf
	{
		u32 currentIndex;
		table_bucket<K,V>* currentBucket;
		table_node<K,V>* currentNode;
		table_blk<K,V> table;
		hash_table<K,V>* hashTable;

		b32 is_end() const;
		b32 next();
		table_pair<K,V>& get();
		const table_pair<K,V>& get() const;
		table_pair<K,V>* get_ptr();
		const table_pair<K,V>* get_ptr() const;
		table_blk<K,V> get_mem();
		const table_blk<K,V> get_mem() const;
		b32 is_coll_valid() const;
		b32 is_mem_valid() const;
		b32 vindicate_mem();
	};

 

	template <typename K,typename V>
	struct hash_table
	{
		table_blk<K,V> table;
		u32 count;

		table_iter<K,V> operator[](const K& key);
		const table_iter<K,V> operator[](const K& key) const;
	};

	template <typename K,typename V,typename A>
	hash_table<K,V> create_hash_table(A* alloc);

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key);

	template <typename K,typename V,typename A>
	table_iter<K,V> insert(hash_table<K,V>* table,const K& key,const V& val,A* alloc);

	template <typename K,typename V,typename A>
	table_iter<K,V> clear(hash_table<K,V>* table,A* alloc);

	template <typename K,typename V>
	table_iter<K,V> search(hash_table<K,V>* table,const K& key);

	template <typename K,typename V>
	const table_iter<K,V> search(const hash_table<K,V>* table,const K& key);

	template <typename K,typename V,typename A>
	table_iter<K,V> remove(hash_table<K,V>* table,const K& key,A* alloc);

	template <typename F,typename K,typename V>
	F get_load_factor(const hash_table<K,V>* table);

	template <typename K,typename V>
	u32 get_count(const hash_table<K,V>* table);

	template <typename K,typename V>
	u32 get_capacity(const hash_table<K,V>* table);

	template <typename K,typename V,typename A>
	table_iter<K,V> resize(hash_table<K,V>* table,u32 newSize,A* alloc);

	template <typename K,typename V>
	table_iter<K,V> get_iter(hash_table<K,V>* table);
}

#include "dggt_coll_hash_table.inl"

#define _DGGT_COLL_HASH_TABLE_H_
#endif
