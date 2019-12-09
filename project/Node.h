#pragma once
#include <iostream>

using namespace std;
template <typename Type>
class Node
{
public:
	Node();
	Node(Type data);
	~Node();
	void setData(Type data);
	Type getData();
	void setNext(Node<Type> *next);
	Node* getNext();
	void printData();
private:
	Type *m_tpData;
	Node<Type> *m_tpNext;
};


template <typename Type>
Node<Type>::Node()
{
	m_tpData = new Type;
	m_tpNext = NULL;
}

template <typename Type>
Node<Type>::Node(Type data)
{
	m_tpData = new Type(data);
	m_tpNext = NULL;
}

template <typename Type>
Node<Type>::~Node()
{
	delete m_tpData;
	m_tpData = NULL;
}

template <typename Type>
void Node<Type>::setData(Type data)
{
	*m_tpData = data;
}

template <typename Type>
Type Node<Type>::getData()
{
	return *m_tpData;
}

template <typename Type>
void Node<Type>::setNext(Node<Type> *next)
{
	m_tpNext = next;
}

template <typename Type>
Node<Type>* Node<Type>::getNext()
{
	return m_tpNext;
}

template <typename Type>
void Node<Type>::printData()
{
	cout << *m_tpData << endl;
}