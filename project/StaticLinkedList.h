#pragma once
#define MAXSIZE 1000
#include<iostream>
using namespace std;
#include <vector>

template<typename EleType>
class StaticList
{
public:
	typedef struct
	{
		EleType data;
		int cur;
	}Node;
	StaticList();
	~StaticList();
	bool Insert(const EleType& e, int index = 1);
	bool Delete(EleType& e, int index = 1);
	void Show()const;
private:
	int NewSpace();//返回list中一个能够用的空间下标
	void DeleteSpace(int index);//删除list中的index元素
	bool Empty()const;
	bool Full()const;
	Node StList[MAXSIZE];
	int Length;
};

template<typename EleType>
StaticList<EleType>::StaticList() :Length(0)
{
	for (int i = 0; i < MAXSIZE - 1; ++i)
	{
		StList[i].cur = i + 1;
	}
	StList[MAXSIZE - 1].cur = 0;

}

template<typename EleType>
StaticList<EleType>::~StaticList()
{

}

template<typename EleType>
bool StaticList<EleType>::Insert(const EleType& e, int index /*= 1*/)
{
	if (Full())//假设为满，则不插入数据
	{
		cout << "Can't insert element to a full List!\n";
		return false;
	}
	if (index<1 || index>Length + 1)//假设插入点的下标不合法，返回false
	{
		cout << "The invalid index!\n";
		return false;
	}
	int k = NewSpace();//返回一个能够插入的节点的下标
	int j = MAXSIZE - 1;
	if (k)//假设返回下标不为0
	{
		StList[k].data = e;//将返回位置的数据设置成e
		for (int i = 1; i <= index - 1; ++i)//找到插入节点的前一个节点的下标
		{
			j = StList[j].cur;
		}
		StList[k].cur = StList[j].cur;//将插入节点的cur设置成插入位置前一个节点的cur
		StList[j].cur = k;//将插入位置的前一个节点的cur设置成k，实现把第k个节点插入到index-1个节点后。实现把第K个节点插入到第index个位置
		++Length;//链表长度加一
		return true;
	}
	return false;
}

template<typename EleType>
bool StaticList<EleType>::Delete(EleType& e, int index /*= 1*/)
{
	if (Empty())//假设链表为空。不运行删除操作
	{
		cout << "Can't delete element in a empty list!\n";
		return false;
	}
	if (index<1 || index>Length)//假设删除的位置不合法，返回false
	{
		cout << "The invalid index!\n";
		return false;
	}
	int k = MAXSIZE - 1;
	int i = 1;
	for (; i <= index - 1; ++i)//找到第index-1个节点k
	{
		k = StList[k].cur;
	}
	i = StList[k].cur;//i为第index个节点的下标
	StList[k].cur = StList[i].cur;//将第index-1个节点的cur设置成第index个节点的cur，实现了把第index个节点排除在链表之外
	e = StList[i].data;//返回第index个节点的data给e
	DeleteSpace(i);//回收第index个节点的空间
	--Length;//链表长度减一
	return true;
}

template<typename EleType>
void StaticList<EleType>::Show() const
{
	if (Empty())
	{
		cout << "The List is Empty!\n";
		return;
	}
	int k = StList[MAXSIZE - 1].cur;
	cout << "The list is :\n";
	for (int i = 1; i <= Length; ++i)
	{
		cout << StList[k].data << " ";
		k = StList[k].cur;
	}
	cout << endl;
}

template<typename EleType>
bool StaticList<EleType>::Full() const
{
	if (Length > MAXSIZE - 2)//保证StList[0]和StList[MAXSIZE-1]不被插入数据覆盖
	{
		return true;
	}
	return false;
}

template<typename EleType>
bool StaticList<EleType>::Empty() const
{
	return(Length == 0);
}

template<typename EleType>
void StaticList<EleType>::DeleteSpace(int index)
{
	StList[index].cur = StList[0].cur;//将要删除的节点增加到空暇节点最前
	StList[0].cur = index;//把该节点设置成第一个可用的空暇节点
}

template<typename EleType>
int StaticList<EleType>::NewSpace()
{
	int i = StList[0].cur;//第一个可用的空暇姐弟那

	if (StList[0].cur)//假设该空暇节点可用
	{
		StList[0].cur = StList[i].cur;//设置下一次第一个可用的空暇节点为返回节点的下一个节点
	}
	return i;//返回可用节点的下标
}

//test
//int main()
//{
//	StaticList<int> TestList;
//	TestList.Insert(12);
//	TestList.Insert(12);
//	TestList.Insert(34);
//
//	TestList.Insert(23);
//	TestList.Insert(12);
//
//	TestList.Insert(99, 4);
//	TestList.Show();
//	int m = 0;
//	TestList.Delete(m, 7);
//	cout << "____________" << m << "_______________\n";
//	TestList.Show();
//	return 0;
//}