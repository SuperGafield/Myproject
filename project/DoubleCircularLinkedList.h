#pragma once

#include<iostream>  
using namespace std;
template<class T>
class LinkNode //节点类  
{
public:           //全为公共的方便操作  
	T data; //模板类型的一个数据  
	LinkNode<T> *next; //该结点的一个指针，用于指向后继  
	LinkNode<T> *prior;//用于指向前驱  
public:
	LinkNode(LinkNode<T> *ptr = NULL)//只初始化指针的构造函数,并使指针域为空  
	{
		next = ptr; prior = ptr;
	}

	LinkNode(const T& item, LinkNode<T> *ptr = NULL)//数据与指针一同初始化的构造函数，依旧指针域默认参数为空  
	{
		data = item; next = ptr; prior = ptr;
	}

	~LinkNode() {}

};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;//构造函数中开辟头结点  
	first->prior = first;//头结点的前后指针均指向其本身 逻辑循环  
	first->next = first;
}
//在每一次的插入和删除之后需要把首尾连接起来，其余操作可看做是普通链表。

template<class T>//继承的过程中，加上此句派生类依然为类模板  

class List

{
protected:
	LinkNode<T>* first;//封装  
public:
	List();
	List(List<T>& L);
	~List();
	void makeEmpty();//依次销毁每个结点的空间  
	int Length() const;//搜索当前表节点数  

	LinkNode<T>* getHead() const;//返回头指针  
	LinkNode<T>* Search(T x) const;//搜索并返回指针  
	LinkNode<T>* Locate(int i) const;//定位并返回指针  

	bool GetData(int i, T& x) const;//返回第i个结点的元素值以引用的形式  
	bool SetData(int i, T& x);//修改第i个结点的元素值  
	bool Insert(int i, T& x);//在第i个节点后面插入新节点元素值  
	LinkNode<T>* Remove(int i, T& x);//删除第i个结点  

	bool isEmpty() const;//判表空  
	void Sort(); //排序  
	void input(T endTag);//建立表并输入  
	void output();//输出表  
	void operator = (List<T>& L);//复制重载  
};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;//构造函数中开辟头结点  
	first->prior = first;//头结点的前后指针均指向其本身 逻辑循环  
	first->next = first;
}
template<class T>
List<T>::List(List<T>& L)

{
	LinkNode<T> *L_HEAD = L.getHead();
	LinkNode<T> *srcptr = L_HEAD->next; //获取头指针 用于遍历  
	LinkNode<T> *destptr = first = new LinkNode<T>;//建立头结点 初始化  
	LinkNode<T> *newNode;
	T value;

	while (srcptr != L_HEAD)//直到循环到首指针w为结束  
	{
		value = srcptr->data;
		newNode = new LinkNode<T>(value);
		newNode->prior = destptr;//往新链表的后面插入  
		destptr->next = newNode;
		srcptr = srcptr->next;//后移  
		destptr = destptr->next;
	}
	destptr->next = first;//首尾相接 建立循环  
	first->prior = destptr;
}

template<class T>
List<T>::~List()
{
	makeEmpty();
}



template<class T>
void List<T>::makeEmpty() //全部销毁指针资源  
{
	LinkNode<T> *current = first->next;
	LinkNode<T> *del;
	while (current != first)
	{
		del = current;
		current = current->next;
		delete del;
	}

}

template<class T>
int List<T>::Length() const
{
	int count = 0;
	LinkNode<T> *current = first;//头指针副本用于遍历  
	while (current->next != first)//与单链表的遍历控制条件相同，当前结点后后继是否为空  
	{
		current = current->next;
		count++;
	}
	return count;
}



template<class T>
LinkNode<T>* List<T>::getHead() const
{
	return first;
}

template<class T>
LinkNode<T>* List<T>::Search(T x) const
{
	LinkNode<T> *current = first->next;
	while (current != NULL)//此时的控制条件为某个结点的next知否为空  
	{
		if (current->data == x)
			return current;//如果查询到直接函数返回,不用无用操作(如果链表中有多个x元素值,则以第一个为准返回)  
		current = current->next;
	}
	return NULL;
}

template<class T>
LinkNode<T>* List<T>::Locate(int i) const
{
	if (i < 0)     //定位可以是第0个，也就是头结点指针  
		return NULL;
	LinkNode<T> *current = first; int k = 0;
	while (current != NULL && k < i)//双条件控制后者其更多的作用  
	{
		current = current->next;k++;
	}
	return current;//指向第i个元素的指针  
}

template<class T>
bool List<T>::GetData(int i, T& x) const   //参数中有下标值的一般先判断其下标值是否合法  
{
	if (i <= 0)
		return false;
	LinkNode<T> *current = Locate(i);
	if (current == NULL)
		return false;
	x = current->data;
	retrun true;
}
template<class T>
bool List<T>::SetData(int i, T& x)
{
	if (i <= 0)
		return false;
	LinkNode<T> *current = Locate(i);
	if (current == NULL)
		return false;
	current->data = x;
	return true;
}

template<class T>

bool List<T>::Insert(int i, T& x)

{

	if (i < 0)//可以插入在第一个结点之前,有头结点的好处代码一致  
		return false;
	LinkNode<T> *current = Locate(i);
	return false;
	LinkNode<T> *newNode = new LinkNode<T>(x);

	if (newNode == NULL)

		return false;
	newNode->prior = current; //双向链表插入的关键四步，顺序不能变，最后一句必须最后执行  
	newNode->next = current->next;
	current->next->prior = newNode;
	current->next = newNode;
	return true;
}
template<class T>
LinkNode<T>* List<T>::Remove(int i, T& x)
{
	if (i <= 0)
		return NULL;
	LinkNode<T> *current = Locate(i);//和单链表不同的是,双向链表有前指针可以指向前驱,所以定位到第i个就好  
	if (current == NULL)return NULL;
	current->next->prior = current->prior;//双向链表删除操作较为简单明了  
	current->prior->next = current->next;//重新搭链  
	x = current->data;
	delete current;//销毁指针资源  
}

template<class T>
bool List<T>::isEmpty() const
{
	return ((first->next == NULL) ? true : false);
}

template<class T>
void List<T>::input(T endTag)
{
	makeEmpty();//在输入前先清空链表  
	LinkNode<T> *newNode, *last = first;
	T value;
	cin >> value;
	while (value != endTag)
	{
		newNode = new LinkNode<T>(value);
		newNode->prior = last;
		last->next = newNode;
		last = newNode;
		cin >> value;
	}
	last->next = first;  //重新首尾连接  

	first->prior = last;

}

template<class T>
void List<T>::output()//输出  
{
	cout << "双向链表输出如下:" << endl;
	LinkNode<T> *current = first->next;
	int count = 0;
	while (current != first)
	{
		cout << "#" << count + 1 << ":" << current->data << endl;
		current = current->next;
		count++;
	}

}
template<class T>
void List<T>::Sort()//最小选择 排序  
{
	LinkNode<T> *current1, *current2;//下面连续取后继指针把外层循环控制在倒数第二个结点  
	for (current1 = first->next; current1->next != first; current1 = current1->next)
	{
		for (current2 = current1->next; current2 != first; current2 = current2->next)
		{
			if (current1->data > current2->data)

			{
				T temp;
				temp = current1->data;
				current1->data = current2->data;
				current2->data = temp;
			}
		}
	}
}
template<class T>

void List<T>::operator= (List<T> &L)

{
	makeEmpty();//先全部销毁指针资源  
	LinkNode<T> *L_HEAD = L.getHead(); //获取首指针 遍历终止条件  
	LinkNode<T> *srcptr = L_HEAD->next; //获取头指针 用于遍历  
	LinkNode<T> *destptr = first;   //= new LinkNode<T>;//不用于赋值初始化,只用于复制,不用建立新头结点  
	LinkNode<T> *newNode;
	T value;
	while (srcptr != L_HEAD)//直到最后一个结点的尾指针为空结束  
	{
		value = srcptr->data;
		newNode = new LinkNode<T>(value);
		newNode->prior = destptr;//往新链表的后面插入  
		destptr->next = newNode;
		srcptr = srcptr->next;//后移  
		destptr = destptr->next;
	}

	destptr->next = first;//首尾相接 循环  
	first->prior = destptr;

}
