#pragma once
#include <string>
using namespace std;
#include<iostream>

//����ѭ������ -- ������ģ��
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
	//����ͷ�ڵ�
	m_head = new ListNode<T>;
	if (nullptr == m_head)
	{
		cout << "��̬����ͷ�ڵ��ڴ�ʧ��" << endl;
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
	ClearList();    //��Ϊ�հ�
	delete m_head;  //�ͷ�ͷ�ڵ�
}

template <typename T>
void LinkListCy<T>::ClearList() const       //����Ա���� ���ı�����ֵ
{
	ListNode<T> *temp, *p = m_head->next;

	while (p != m_head)     //ɾ��ͷ�ڵ��Ժ�����нڵ�
	{
		temp = p->next;
		delete p;           //Ҫ�ͷŶ�̬�ڴ�
		p = temp;
	}

	m_head->next = m_head;
}

template <typename T>
bool LinkListCy<T>::Empty() const
{
	//���ͷ�ڵ����һ���ڵ�Ϊ�գ��������Ϊ��
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
		if (ptemp->data == data)            //ע�� �����ͱ���֧�� == �������������֧����Ҫ�������������
		{
			return location;
		}

		ptemp = ptemp->next;
	}

	return 0;       //����0��ʾδ�ҵ�
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

		//������һ���µĽڵ�
		ListNode<T> *newnode = new ListNode < T >;
		if (nullptr == newnode)
		{
			cout << "����ռ�ʧ��" << endl;
			return false;
		}

		newnode->data = elem;       //����������Ͳ��ǻ����������ͣ�����֧�� = ����������Ҫ���� = ������
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

		ListNode<T> *t = ptemp->next;       //ָ���ɾ���Ľڵ�

		ptemp->next = ptemp->next->next;        //����ɾ���ڵ����һ�ڵ�ָ���ɾ���ڵ����һ�ڵ�
		delete t;       //�ͷ�ɾ���ڵ���ڴ�

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
		if (ptemp->next->data == elem)          //�ҵ���Ҫɾ���Ľڵ���ͬ
		{
			ListNode<T> *t = ptemp->next;       //ָ���ɾ���Ľڵ�
			ptemp->next = ptemp->next->next;        //����ɾ���ڵ����һ�ڵ�ָ���ɾ���ڵ����һ�ڵ�
			delete t;       //�ͷ�ɾ���ڵ���ڴ�
		}
		else        //������Ҫע��һ�£����ɾ������ô������һ�ڵ����µĽڵ���Ҫ�����жϣ����Բ���Ҫ�ƶ�
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
