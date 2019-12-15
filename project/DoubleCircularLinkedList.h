#pragma once

#include<iostream>  
using namespace std;
template<class T>
class LinkNode //�ڵ���  
{
public:           //ȫΪ�����ķ������  
	T data; //ģ�����͵�һ������  
	LinkNode<T> *next; //�ý���һ��ָ�룬����ָ����  
	LinkNode<T> *prior;//����ָ��ǰ��  
public:
	LinkNode(LinkNode<T> *ptr = NULL)//ֻ��ʼ��ָ��Ĺ��캯��,��ʹָ����Ϊ��  
	{
		next = ptr; prior = ptr;
	}

	LinkNode(const T& item, LinkNode<T> *ptr = NULL)//������ָ��һͬ��ʼ���Ĺ��캯��������ָ����Ĭ�ϲ���Ϊ��  
	{
		data = item; next = ptr; prior = ptr;
	}

	~LinkNode() {}

};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;//���캯���п���ͷ���  
	first->prior = first;//ͷ����ǰ��ָ���ָ���䱾�� �߼�ѭ��  
	first->next = first;
}
//��ÿһ�εĲ����ɾ��֮����Ҫ����β������������������ɿ�������ͨ����

template<class T>//�̳еĹ����У����ϴ˾���������ȻΪ��ģ��  

class List

{
protected:
	LinkNode<T>* first;//��װ  
public:
	List();
	List(List<T>& L);
	~List();
	void makeEmpty();//��������ÿ�����Ŀռ�  
	int Length() const;//������ǰ��ڵ���  

	LinkNode<T>* getHead() const;//����ͷָ��  
	LinkNode<T>* Search(T x) const;//����������ָ��  
	LinkNode<T>* Locate(int i) const;//��λ������ָ��  

	bool GetData(int i, T& x) const;//���ص�i������Ԫ��ֵ�����õ���ʽ  
	bool SetData(int i, T& x);//�޸ĵ�i������Ԫ��ֵ  
	bool Insert(int i, T& x);//�ڵ�i���ڵ��������½ڵ�Ԫ��ֵ  
	LinkNode<T>* Remove(int i, T& x);//ɾ����i�����  

	bool isEmpty() const;//�б��  
	void Sort(); //����  
	void input(T endTag);//����������  
	void output();//�����  
	void operator = (List<T>& L);//��������  
};

template<class T>
List<T>::List()
{
	first = new LinkNode<T>;//���캯���п���ͷ���  
	first->prior = first;//ͷ����ǰ��ָ���ָ���䱾�� �߼�ѭ��  
	first->next = first;
}
template<class T>
List<T>::List(List<T>& L)

{
	LinkNode<T> *L_HEAD = L.getHead();
	LinkNode<T> *srcptr = L_HEAD->next; //��ȡͷָ�� ���ڱ���  
	LinkNode<T> *destptr = first = new LinkNode<T>;//����ͷ��� ��ʼ��  
	LinkNode<T> *newNode;
	T value;

	while (srcptr != L_HEAD)//ֱ��ѭ������ָ��wΪ����  
	{
		value = srcptr->data;
		newNode = new LinkNode<T>(value);
		newNode->prior = destptr;//��������ĺ������  
		destptr->next = newNode;
		srcptr = srcptr->next;//����  
		destptr = destptr->next;
	}
	destptr->next = first;//��β��� ����ѭ��  
	first->prior = destptr;
}

template<class T>
List<T>::~List()
{
	makeEmpty();
}



template<class T>
void List<T>::makeEmpty() //ȫ������ָ����Դ  
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
	LinkNode<T> *current = first;//ͷָ�븱�����ڱ���  
	while (current->next != first)//�뵥����ı�������������ͬ����ǰ�������Ƿ�Ϊ��  
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
	while (current != NULL)//��ʱ�Ŀ�������Ϊĳ������next֪��Ϊ��  
	{
		if (current->data == x)
			return current;//�����ѯ��ֱ�Ӻ�������,�������ò���(����������ж��xԪ��ֵ,���Ե�һ��Ϊ׼����)  
		current = current->next;
	}
	return NULL;
}

template<class T>
LinkNode<T>* List<T>::Locate(int i) const
{
	if (i < 0)     //��λ�����ǵ�0����Ҳ����ͷ���ָ��  
		return NULL;
	LinkNode<T> *current = first; int k = 0;
	while (current != NULL && k < i)//˫�������ƺ�������������  
	{
		current = current->next;k++;
	}
	return current;//ָ���i��Ԫ�ص�ָ��  
}

template<class T>
bool List<T>::GetData(int i, T& x) const   //���������±�ֵ��һ�����ж����±�ֵ�Ƿ�Ϸ�  
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

	if (i < 0)//���Բ����ڵ�һ�����֮ǰ,��ͷ���ĺô�����һ��  
		return false;
	LinkNode<T> *current = Locate(i);
	return false;
	LinkNode<T> *newNode = new LinkNode<T>(x);

	if (newNode == NULL)

		return false;
	newNode->prior = current; //˫���������Ĺؼ��Ĳ���˳���ܱ䣬���һ��������ִ��  
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
	LinkNode<T> *current = Locate(i);//�͵�����ͬ����,˫��������ǰָ�����ָ��ǰ��,���Զ�λ����i���ͺ�  
	if (current == NULL)return NULL;
	current->next->prior = current->prior;//˫������ɾ��������Ϊ������  
	current->prior->next = current->next;//���´���  
	x = current->data;
	delete current;//����ָ����Դ  
}

template<class T>
bool List<T>::isEmpty() const
{
	return ((first->next == NULL) ? true : false);
}

template<class T>
void List<T>::input(T endTag)
{
	makeEmpty();//������ǰ���������  
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
	last->next = first;  //������β����  

	first->prior = last;

}

template<class T>
void List<T>::output()//���  
{
	cout << "˫�������������:" << endl;
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
void List<T>::Sort()//��Сѡ�� ����  
{
	LinkNode<T> *current1, *current2;//��������ȡ���ָ������ѭ�������ڵ����ڶ������  
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
	makeEmpty();//��ȫ������ָ����Դ  
	LinkNode<T> *L_HEAD = L.getHead(); //��ȡ��ָ�� ������ֹ����  
	LinkNode<T> *srcptr = L_HEAD->next; //��ȡͷָ�� ���ڱ���  
	LinkNode<T> *destptr = first;   //= new LinkNode<T>;//�����ڸ�ֵ��ʼ��,ֻ���ڸ���,���ý�����ͷ���  
	LinkNode<T> *newNode;
	T value;
	while (srcptr != L_HEAD)//ֱ�����һ������βָ��Ϊ�ս���  
	{
		value = srcptr->data;
		newNode = new LinkNode<T>(value);
		newNode->prior = destptr;//��������ĺ������  
		destptr->next = newNode;
		srcptr = srcptr->next;//����  
		destptr = destptr->next;
	}

	destptr->next = first;//��β��� ѭ��  
	first->prior = destptr;

}
