#include <iostream>
using namespace std;

//单向链表
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



template <typename Type>
class LinkList
{
public:
	LinkList();
	~LinkList();
	bool isListEmpty();
	bool clearList();
	int getListLength();
	int getElemIndex(Type &elem);
	bool getListElem(int index, Type* elem);
	bool ListInsert(int index, Type &elem);
	bool ListDelete(int index, Type *elem);
	void ListPrint(void);
private:
	Node<Type> *m_pList;//头结点
	int m_iLength;
};

template <typename Type>
LinkList<Type>::LinkList()
{
	m_pList = new Node<Type>;
	m_pList->setData(NULL);
	m_pList->setNext(NULL);
	m_iLength = 0;
}

template <typename Type>
LinkList<Type>::~LinkList()
{
	Node<Type> *nextNode = m_pList;
	while (nextNode->getNext() != NULL)    //delete Node while pointerNext == NULL
	{
		nextNode = m_pList->getNext();
		delete m_pList;
		m_pList = nextNode;
	}
	delete m_pList;//delete last Node
	m_pList = NULL;
}

template <typename Type>
bool LinkList<Type>::isListEmpty()
{
	if (m_iLength == 0)
		return true;
	return false;
}


template <typename Type>
bool LinkList<Type>::clearList()
{
	if (isListEmpty())
	{
		cout << "List empty clear fail" << endl;
		return false;
	}

	//delete All node except first node
	Node<Type> *nowNode = m_pList->getNext();
	Node<Type> *nextNode = m_pList->getNext();
	while (nextNode->getNext() != NULL)
	{
		nextNode = nowNode->getNext();
		delete nowNode;
		nowNode = nextNode;
	}
	delete nowNode;//delete last Node

	m_iLength = 0;
	m_pList->setNext(NULL);
	return true;
}

template <typename Type>
int LinkList<Type>::getListLength()
{
	return m_iLength;
}
template <typename Type>
int LinkList<Type>::getElemIndex(Type &elem)
{
	Node<Type> *tempNode = m_pList;
	for (int i = 0; i < m_iLength; i++)
	{
		tempNode = tempNode->getNext();
		if (elem == tempNode->getData())
		{
			return i;
		}
	}
	return -1;
}
template <typename Type>
bool LinkList<Type>::getListElem(int index, Type* elem)
{
	if (index < 0 || index >= m_iLength)
	{
		return false;
	}

	Node<Type> *tempNode = m_pList;
	for (int i = 0; i <= index; i++)
	{
		tempNode = tempNode->getNext();
	}

	*elem = tempNode->getData();
	return true;
}

template <typename Type>
bool LinkList<Type>::ListInsert(int index, Type &elem)
{
	//index out of range
	if (index<0 || index>m_iLength)
	{
		return false;
	}

	//
	Node<Type> *tempPreNode = m_pList;
	for (int i = 0; i < index; i++)
	{
		tempPreNode = tempPreNode->getNext();
	}

	Node<Type> *newnode = new Node<Type>;    //create a new node
	if (newnode == NULL)
	{
		cout << "new node create fail" << endl;
		return false;
	}
	Node<Type> *tempNode = tempPreNode->getNext();//save pre node pointer
	tempPreNode->setNext(newnode); //set pre node pointer to new node address
	newnode->setNext(tempNode);//set new node pointer to pre node pointer
	newnode->setData(elem);    //set new node new data
	m_iLength++;
	return true;
}

template <typename Type>
bool LinkList<Type>::ListDelete(int index, Type *elem)
{
	//index out of range
	if (index < 0 || index >= m_iLength)
	{
		return false;
	}

	//
	Node<Type> *tempPreNode = m_pList; //pre node
	for (int i = 0; i < index; i++)//find pre node
	{
		tempPreNode = tempPreNode->getNext();
	}

	Node<Type> * tempNode = tempPreNode->getNext();//save delete point pointer 
	tempPreNode->setNext(tempNode->getNext());//set pre node  point to next node
	*elem = tempNode->getData();
	delete tempNode;

	m_iLength--;
	return true;
}

template <typename Type>
void LinkList<Type>::ListPrint(void)
{
	if (isListEmpty())
	{
		cout << "List empty" << endl;
		return;
	}
	Node<Type> *tempNode = m_pList->getNext();
	while (tempNode->getNext() != NULL)
	{
		tempNode->printData();
		tempNode = tempNode->getNext();
	}
	tempNode->printData();
	cout << "end" << endl;
}