#pragma once
template <class T>
class LinkedList
{
private:	
	template<class T>
	class LinkedListItem 
	{
	public:
		T* value;
		LinkedListItem<T>* next;

		LinkedListItem(T* value) 
		{
			this->value = value;
			this->next = NULL;
		}

		~LinkedListItem() 
		{
			delete this->value;
			delete this->next;
		}
		
	};
	LinkedListItem<T>* root;
public:
	LinkedList();
	~LinkedList();

	void Add(T* value);
	void RemoveAt(int id);
	T* getItemAt(int id);
	int Count();	
};

