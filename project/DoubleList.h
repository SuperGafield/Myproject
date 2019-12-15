#pragma once

//双向链表
#ifndef __DLINK_H__
#define __DLINK_H__
/*
	[phead] -> [index0] -> [index1] -> [index2] -> ...... [phead]
	[phead] <- [index0] <- [index1] <- [index2] <- ...... [phead]
	phead 不存储数据。 index是从0开始的。count = index + 1；
*/
template <class T>
struct node
{
public:
	node() {}
	node(T a, node *p1, node *p2)
	{
		this->data = a;
		this->next = p2;
		this->prev = p1;
	}
	node *next;
	node *prev;
	T data;
};
template <class T>
class Dlink
{
public:
	Dlink();
	~Dlink();

	int create_Dlink();
	int destroy_Dlink();
	int getCount();
	int insert_Dlink(int index, T tData);
	int insert_Dlink_first(T tData);
	int insert_Dlink_last(T tData);
	T get_Dlink(int index);
	T get_Dlink_first();
	T get_Dlink_last();
	int delete_Dlink(int index);
	int delete_Dlink_first();
	int delete_Dlink_last();

private:
	node<T> *get_node(int index);
	node<T> *m_pHead;
	int m_nCount;
};
template <class T>
Dlink<T>::Dlink()
{
	m_pHead = NULL;
	m_nCount = 0;
}
template <class T>
Dlink<T>::~Dlink()
{

}
template <class T>
node<T> *Dlink<T>::get_node(int index)
{
	if (index < 0 || index >= m_nCount)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return NULL;
	}
#if 0
	node<T> *pnode = m_pHead->next;
	int i = 0;
	while (i < m_nCount)
	{
		if (i == index)
		{
			return pnode;
		}
		pnode = pnode->next;
		i++;
	}
#else
	// 正向查找
	if (index <= m_nCount / 2)
	{
		int i = 0;
		node<T> *pnode = m_pHead->next;
		while (i <= m_nCount / 2)
		{
			if (i == index)
			{
				return pnode;
			}
			pnode = pnode->next;
			i++;
		}
	}
	else  // 反向查找
	{
		node<T> *pnode = m_pHead->prev;
		int i = m_nCount - 1; // 注意这里是必须要减一。因为m_nCount = index + 1;
		while (i > (m_nCount / 2))
		{
			if (i == index)
			{
				return pnode;
			}
			pnode = pnode->prev;
			i--;
		}
	}
#endif
	return NULL;
}
template <class T>
int Dlink<T>::create_Dlink()
{
	m_pHead = new node<T>();
	m_pHead->next = m_pHead->prev = m_pHead; // 这个初始化非常重要
	return 0;
}
template <class T>
int Dlink<T>::destroy_Dlink()
{
	if (!m_pHead)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	node<T> *pnode = m_pHead->next;
	node<T> *tmp;
	while (pnode != m_pHead)
	{
		tmp = pnode;
		pnode = pnode->next;
		delete tmp;
		tmp = NULL;
	}
	delete m_pHead;
	m_pHead = NULL;
	m_nCount = 0;
	return 0;
}
template <class T>
int Dlink<T>::getCount()
{
	return m_nCount;
}
// index 表示要插入后的位置，所以这里可以等于m_nCount。表示在最后一个
template <class T>
int Dlink<T>::insert_Dlink(int index, T tData)
{
	if (!m_pHead)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	if (index < 0 || index > m_nCount)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	if (index == 0)
	{
		return insert_Dlink_first(tData);
	}
	if (index == m_nCount)
	{
		return insert_Dlink_last(tData);
	}
	node<T> *pindex = get_node(index);
	node<T> *pnode = new node<T>(tData, pindex->prev, pindex);
	pindex->prev->next = pnode;

#if 0 // 20180223 update. 突然发现这里写错了
	pindex->next->prev = pnode;
#endif
	pindex->prev = pnode; // 改为这样

	m_nCount++;
	return 0;
}
template <class T>
int Dlink<T>::insert_Dlink_first(T tData)
{
	if (!m_pHead)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	node<T> *pnode = new node<T>(tData, m_pHead, m_pHead->next);
	if (!pnode)
	{
		cout << __FUNCTION__ << "() Error step1 " << endl;
		return -1;
	}
	m_pHead->next->prev = pnode;
	m_pHead->next = pnode;
	m_nCount++;
	return 0;
}
template <class T>
int Dlink<T>::insert_Dlink_last(T tData)
{
	if (!m_pHead)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	node<T> *pnode = new node<T>(tData, m_pHead->prev, m_pHead);
	if (!pnode)
	{
		cout << __FUNCTION__ << "() Error step1 " << endl;
		return -1;
	}
	m_pHead->prev->next = pnode;
	m_pHead->prev = pnode;
	m_nCount++;
	return 0;
}
template <class T>
T Dlink<T>::get_Dlink(int index)
{
	node<T> *pnode = get_node(index);
	if (!pnode)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return NULL;
	}
	return pnode->data;
}
template <class T>
T Dlink<T>::get_Dlink_first()
{
	return get_Dlink(0);
}
template <class T>
T Dlink<T>::get_Dlink_last()
{
	return get_Dlink(count - 1);
}
// index 是从0开始编号的。这里的范围是 0 -- m_nCount-1
template <class T>
int Dlink<T>::delete_Dlink(int index)
{
	if (index < 0 || index >= m_nCount)
	{
		cout << __FUNCTION__ << "() Error" << endl;
		return -1;
	}
	node<T> *pnode = get_node(index);
	if (pnode)
	{
		pnode->next->prev = pnode->prev;
		pnode->prev->next = pnode->next;
		delete pnode;
		pnode = NULL;
		m_nCount--;
	}
	return -1;
}
template <class T>
int Dlink<T>::delete_Dlink_first()
{
	return delete_Dlink(0);
}
template <class T>
int Dlink<T>::delete_Dlink_last()
{
	return delete_Dlink(m_nCount - 1);
}

#endif // __DLINK_H__
