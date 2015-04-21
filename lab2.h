// CS 14 Lab
// Lab Number 2
// Name: Robinson Vo-Ly
// SID: 861166275
// Date: 4/14/2015

#include <iostream>
#include <cstdlib>
#include <forward_list>

using namespace std;

template<typename T>
struct Node
{
	T data;
	Node *next;
	Node( T data ) : data(data), next(0) {}
};

template<typename T>
class List
{
	private:
		Node<T> *head;
		Node<T> *tail;
		int size;
	public:
		List();
		~List();
		void push_front(T);
		void push_back(T);
		void pop_front();
		void display() const;
		
		void elementSwap(int pos);
};

template<typename T>
List<T>::List()
 : head(0), tail(0), size(0)
{ }

template<typename T>
List<T>::~List()
{
	while (head != 0)
	{
		pop_front();
	}
}

template <typename T>
void List<T>::push_front(T value)
{
	Node<T> *temp = new Node<T>(value);
	temp->next = head;
	head = temp;
	
	if (!tail)
	{
		tail = head;
	}
	
	size += 1;
}

template<typename T>
void List<T> :: pop_front()
{
	if (head == 0)
	{
		size = 0;
		return;
	}
	
	Node<T> *temp = head;
	head = head->next;
	delete temp;
	size -= 1;
	
	if (head == 0)
	{
		tail = 0;
	}
}

template<typename T>
void List<T>::display() const
{
	for (Node<T> *curr = head; curr != 0; curr = curr->next)
	{
		cout << curr->data;
		if(curr->next != 0)
		{
		    cout << ' ';
		}
	}
	cout << endl;
}

template <typename T>
void List<T>::push_back(T value)
{
	Node<T> *temp = new Node<T>(value);
	
	if(!head)
	{
		head = temp;
		tail = head;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
	
	size += 1;
}

template <typename T>
void List<T>::elementSwap (int pos)
{
	if (pos >= size - 1) 
	{
		cout << "Error: Out of bounds" << endl;
		return;
	}
	
	Node<T> *curr = head;
	
	if (pos == 0)
	{
		Node<T> *temp = curr->next;
		curr->next = temp->next;
		temp->next = curr;
		head = temp;
		return;
	}
	
	for (int i = 0; i < pos - 1; ++i)
	{
		curr = curr->next;
	}
	
	Node<T> *temp = curr->next->next;
	Node<T> *temp2 = curr->next;
	
	if (temp == tail)
	{
		curr->next = temp;
		tail = temp2;
		temp->next = temp2;
		tail->next = 0;
	}
	else
	{
		curr->next = temp;
		temp2->next = temp->next;
		temp->next = temp2;
	}
}