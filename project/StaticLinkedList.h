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
	int NewSpace();//����list��һ���ܹ��õĿռ��±�
	void DeleteSpace(int index);//ɾ��list�е�indexԪ��
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
	if (Full())//����Ϊ�����򲻲�������
	{
		cout << "Can't insert element to a full List!\n";
		return false;
	}
	if (index<1 || index>Length + 1)//����������±겻�Ϸ�������false
	{
		cout << "The invalid index!\n";
		return false;
	}
	int k = NewSpace();//����һ���ܹ�����Ľڵ���±�
	int j = MAXSIZE - 1;
	if (k)//���践���±겻Ϊ0
	{
		StList[k].data = e;//������λ�õ��������ó�e
		for (int i = 1; i <= index - 1; ++i)//�ҵ�����ڵ��ǰһ���ڵ���±�
		{
			j = StList[j].cur;
		}
		StList[k].cur = StList[j].cur;//������ڵ��cur���óɲ���λ��ǰһ���ڵ��cur
		StList[j].cur = k;//������λ�õ�ǰһ���ڵ��cur���ó�k��ʵ�ְѵ�k���ڵ���뵽index-1���ڵ��ʵ�ְѵ�K���ڵ���뵽��index��λ��
		++Length;//�����ȼ�һ
		return true;
	}
	return false;
}

template<typename EleType>
bool StaticList<EleType>::Delete(EleType& e, int index /*= 1*/)
{
	if (Empty())//��������Ϊ�ա�������ɾ������
	{
		cout << "Can't delete element in a empty list!\n";
		return false;
	}
	if (index<1 || index>Length)//����ɾ����λ�ò��Ϸ�������false
	{
		cout << "The invalid index!\n";
		return false;
	}
	int k = MAXSIZE - 1;
	int i = 1;
	for (; i <= index - 1; ++i)//�ҵ���index-1���ڵ�k
	{
		k = StList[k].cur;
	}
	i = StList[k].cur;//iΪ��index���ڵ���±�
	StList[k].cur = StList[i].cur;//����index-1���ڵ��cur���óɵ�index���ڵ��cur��ʵ���˰ѵ�index���ڵ��ų�������֮��
	e = StList[i].data;//���ص�index���ڵ��data��e
	DeleteSpace(i);//���յ�index���ڵ�Ŀռ�
	--Length;//�����ȼ�һ
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
	if (Length > MAXSIZE - 2)//��֤StList[0]��StList[MAXSIZE-1]�����������ݸ���
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
	StList[index].cur = StList[0].cur;//��Ҫɾ���Ľڵ����ӵ���Ͼ�ڵ���ǰ
	StList[0].cur = index;//�Ѹýڵ����óɵ�һ�����õĿ�Ͼ�ڵ�
}

template<typename EleType>
int StaticList<EleType>::NewSpace()
{
	int i = StList[0].cur;//��һ�����õĿ�Ͼ�����

	if (StList[0].cur)//����ÿ�Ͼ�ڵ����
	{
		StList[0].cur = StList[i].cur;//������һ�ε�һ�����õĿ�Ͼ�ڵ�Ϊ���ؽڵ����һ���ڵ�
	}
	return i;//���ؿ��ýڵ���±�
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