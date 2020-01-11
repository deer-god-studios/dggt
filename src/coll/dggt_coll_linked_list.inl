
template <typename T>
list_node<T>::list_node() { }

template <typename T>
list_node<T>::list_node(const T& val,list_node* next)
{
	this->val=val;
	this->next=next;
}

template <typename T>
list_node<T>::list_node(const T& val)
	: list_node(val,0) { }

template <typename T>
list_iter<T>::list_iter(list_node* begin)
{
	current=begin;
}

template <typename T>
b32 list_iter<T>::is_end() const
{
	return current==0;
}

template <typename T>
void list_iter<T>::advance()
{
	if (!is_end())
	{
		current=current->next;
	}
}

template <typename T>
const T& list_iter<T>::get() const
{
	return val;
}

template <typename T>
T& list_iter<T>::get()
{
	return val;
}
