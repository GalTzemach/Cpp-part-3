/*
T should have:
1) operator <<	:	in order to print with cout.
*/

#ifndef __MY_LINKED_LIST_H
#define __MY_LINKED_LIST_H

#include <iostream>

using namespace std;

template<class T>
class MyLinkedList
{

private:
	class Node
	{
	private:
		Node* next;
		T value;

	public:
		Node(const T& value);
		Node* getNext() const { return next; }
		const T& getValue() const { return value; }
		void setValue(T& value) { this->value = value }

		friend class MyLinkedList<T>;
	};

	int size;
	Node *head;
	Node *tail;

public:
	MyLinkedList();
	~MyLinkedList();

	int getSize() const;
	bool isEmpty() const;

	void addToTail(T value);
	T removeAtIndex(int index) throw (const string);

	const T& operator[](int index) const throw (const string);
	const MyLinkedList& operator=(const MyLinkedList& other) = delete;

	friend ostream& operator<<(ostream& os, const MyLinkedList& lst)
	{
		if (MyLinkedList<T>::isEmpty())
		{
			os << "LinkedList is empty";
		}
		else
		{
			MyLinkedList<T>::Node* temp = myLinkedList.head;

			while (temp != nullptr)
			{
				os << *temp->getValue() << endl;
				temp = temp->getNext();
			}
		}

		return os;
	}
};

template<class T>
MyLinkedList<T>::Node::Node(const T& value) : value(value)
{
	this->next = nullptr;
}

template<class T>
MyLinkedList<T>::~MyLinkedList()
{
	Node *current = this->head;
	Node *next = this->head;

	while (current != nullptr)
	{
		next = current->next;
		delete current;
		current = next;
	}
}

template<class T>
MyLinkedList<T>::MyLinkedList()
{
	this->head = this->tail = nullptr;
	this->size = 0;
}


template<class T>
void MyLinkedList<T>::addToTail(T value)
{
	Node* newNode = new Node(value);

	if (isEmpty())
		this->head = this->tail = newNode;
	else
	{
		this->tail->next = newNode;
		this->tail = this->tail->next;
		this->tail->next = nullptr;
	}

	size++;
}

template<class T>
T MyLinkedList<T>::removeAtIndex(int index)
{
	T value;
	Node<T>* temp = head;
	Node<T>* next = nullptr;

	if (index >= size || index < 0)
		throw string("Index is out of bound");

	if (index == 0) // First element
	{
		value = head->value;
		head = head->next;
		delete temp;
	}
	else
	{
		for (int i = 0; i < index - 1; ++i)
			temp = temp->next;

		if (temp->next == tail)// Last element
			tail = temp;
		else
			next = temp->next->next; // Skip

		value = temp->next->value; 
		delete temp->next;
		temp->next = next;
	}

	size--;
	return value;
}

template<class T>
bool MyLinkedList<T>::isEmpty() const
{
	return size == 0;
}

template<class T>
int MyLinkedList<T>::getSize() const
{
	return this->size;
}

template<class T>
const T& MyLinkedList<T>::operator[](int index) const
{
	Node* temp = head;

	if (index >= size || index < 0)
		throw string("Index is out of bound");

	if (index == 0)// First element
		return head->value;

	if (index == size - 1)// Last element
		return tail->value;

	for (int i = 0; i < index; ++i)// Else (not first or last)
		temp = temp->next;

	return temp->value;
}

#endif //__MY_LINKED_LIST_H