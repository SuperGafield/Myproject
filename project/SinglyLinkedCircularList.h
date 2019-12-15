#pragma once
#include <string>
using namespace std;
#include<iostream>

//单向循环链表 -- 采用类模板
template <typename T>
class LinkListCy
{
public:
	LinkListCy();
	LinkListCy(T elem);
	LinkListCy(int n, T elem);
	~LinkListCy();
	void ClearList() const;
	bool Empty() const;
	int Length() const;
	T GetElem(int n) const;
	int LocateElem(T elem) const;
	bool Insert(int n, T elem);
	bool Delete(int n);
	void Displasy();
	void Remove(T elem);
private:
	ListNode<T> *m_head;
};

template <typename T>
LinkListCy<T>::LinkListCy()
{
	//创建头节点
	m_head = new ListNode<T>;
	if (nullptr == m_head)
	{
		cout << "动态申请头节点内存失败" << endl;
		return;
	}

	m_head->next = m_head;
}

template <typename T>
LinkListCy<T>::LinkListCy(T elem) :LinkListCy()
{
	Insert(1, elem);
}

template <typename T>
LinkListCy<T>::LinkListCy(int n, T elem) :LinkListCy()
{
	for (int i = 0; i < n; ++i)
	{
		Insert(i, elem);
	}
}

template <typename T>
LinkListCy<T>::~LinkListCy()
{
	ClearList();    //置为空白
	delete m_head;  //释放头节点
}

template <typename T>
void LinkListCy<T>::ClearList() const       //常成员函数 不改变对象的值
{
	ListNode<T> *temp, *p = m_head->next;

	while (p != m_head)     //删除头节点以后的所有节点
	{
		temp = p->next;
		delete p;           //要释放动态内存
		p = temp;
	}

	m_head->next = m_head;
}

template <typename T>
bool LinkListCy<T>::Empty() const
{
	//如果头节点的下一个节点为空，则该链表为空
	return m_head == m_head->next;
}

template <typename T>
int LinkListCy<T>::Length() const
{
	int count = 0;
	ListNode<T> *ptemp = m_head->next;

	while (ptemp != m_head)
	{
		count++;
		ptemp = ptemp->next;
	}

	return count;
}

template <typename T>
T LinkListCy<T>::GetElem(int n) const
{
	ListNode<T> *ptemp = m_head->next;

	if (n <= Length())
	{
		for (int i = 1; i < n; ++i)
		{
			ptemp = ptemp->next;
		}
	}
	else
	{
		cout << "out of ranger" << endl;
		return false;
	}

	return ptemp->data;
}

template <typename T>
int LinkListCy<T>::LocateElem(T data) const
{
	size_t location = 0;
	ListNode<T> *ptemp = m_head->next;

	while (ptemp != m_head)
	{
		++location;
		if (ptemp->data == data)            //注意 该类型必须支持 == 操作符，如果不支持需要进行运算符重载
		{
			return location;
		}

		ptemp = ptemp->next;
	}

	return 0;       //返回0表示未找到
}

template <typename T>
bool LinkListCy<T>::Insert(int n, T elem)
{
	ListNode<T> *ptemp = m_head;

	if (n - 1 <= Length())
	{
		for (int i = 0; i < n - 1; ++i)
		{
			ptemp = ptemp->next;
		}

		//先生成一个新的节点
		ListNode<T> *newnode = new ListNode < T >;
		if (nullptr == newnode)
		{
			cout << "申请空间失败" << endl;
			return false;
		}

		newnode->data = elem;       //如果数据类型不是基本数据类型，即不支持 = 操作符，需要重载 = 操作符
		newnode->next = ptemp->next;
		ptemp->next = newnode;

		return true;
	}
	else
	{
		cout << "out of range" << endl;
		return false;
	}
}

template <typename T>
bool LinkListCy<T>::Delete(int n)
{
	ListNode<T> *ptemp = m_head;

	if (n <= Length())
	{
		for (int i = 0; i < n - 1; ++i)
		{
			ptemp = ptemp->next;
		}

		ListNode<T> *t = ptemp->next;       //指向待删除的节点

		ptemp->next = ptemp->next->next;        //将待删除节点的上一节点指向待删除节点的下一节点
		delete t;       //释放删除节点的内存

		return true;
	}
	else
	{
		cout << "out of range" << endl;
		return false;
	}
}

template <typename T>
void LinkListCy<T>::Displasy()
{
	ListNode<T> *ptemp = m_head->next;

	while (ptemp != m_head)
	{
		cout << ptemp->data << "  ";
		ptemp = ptemp->next;
	}
	cout << endl;
}

template <typename T>
void LinkListCy<T>::Remove(T elem)
{
	ListNode<T> *ptemp = m_head;

	while (ptemp->next != m_head)
	{
		if (ptemp->next->data == elem)          //找到与要删除的节点相同
		{
			ListNode<T> *t = ptemp->next;       //指向待删除的节点
			ptemp->next = ptemp->next->next;        //将待删除节点的上一节点指向待删除节点的下一节点
			delete t;       //释放删除节点的内存
		}
		else        //这里需要注意一下：如果删除了那么它的下一节点是新的节点需要重现判断，所以不需要移动
		{
			ptemp = ptemp->next;
		}
	}
}

//int main()
//{
//	LinkListCy<string> List{ 10, "haha" };
//
//	List.Insert(5, "zjy");
//
//	List.Delete(1);
//
//	cout << List.Length() << endl;
//	cout << List.LocateElem("zjy") << endl;
//	cout << List.GetElem(1) << endl;
//
//	List.Displasy();
//
//	system("pause");
//	return 0;
//}
