#pragma once
#include<iostream>
#include<mutex>
using namespace std;

/*  ʵ��һ���̰߳�ȫ������ָ�� */
/* ���ü������� */

class Sp_counter
{
private:
	size_t *_count;
	std::mutex mt;
public:
	Sp_counter()
	{
		cout << "���๹��,����counter�ڴ�" << endl;
		_count = new size_t(0);
	}
	virtual ~Sp_counter()
	{
		if (_count && !(*_count)) {
			cout << "��������" << endl;
			cout << "[�ͷ�counter�ڴ�]" << endl;
			delete _count;
			_count = NULL;
		}
	}
	Sp_counter &operator=(Sp_counter &spc)
	{
		cout << "��������=" << endl;
		cout << "[�ͷ�counter�ڴ�]" << endl;
		delete _count;
		this->_count = spc._count;
		return *this;
	}
	Sp_counter &GetCounter()
	{
		return *this;
	}
	size_t Get_Reference()
	{
		return *_count;
	}
	virtual void Increase()
	{
		mt.lock();
		(*_count)++;
		//cout<<"_count++:"<<*_count<<endl;
		mt.unlock();
	}
	virtual void Decrease()
	{
		mt.lock();
		(*_count)--;
		//cout<<"_count--:"<<*_count<<endl;
		mt.unlock();
	}
};

template<typename T>
class smart_pointer : public Sp_counter
{
private:
	T *_ptr;
public:
	smart_pointer(T *ptr = NULL);
	~smart_pointer();
	smart_pointer(smart_pointer<T> &);
	smart_pointer<T> &operator=(smart_pointer<T> &);
	T &operator*();
	T *operator->(void);
	size_t use_count();
};

/* ����ι��캯��&���������캯�� */
template<typename T>
inline smart_pointer<T>::smart_pointer(T *ptr)
{
	if (ptr) {
		cout << "����Ĭ�Ϲ���" << endl;
		_ptr = ptr;
		this->Increase();
	}
}

/* ������������ */
template<typename T>
smart_pointer<T>::~smart_pointer()
{
	/* ָ��ǿղ����� */
	if (this->_ptr) {
		cout << "��������,������1" << endl;
		if (this->Get_Reference())
			this->Decrease();
		if (!(this->Get_Reference())) {
			cout << "(((��������,���ڴ汻�ͷ�)))" << endl;
			delete _ptr;
			_ptr = NULL;
		}
	}
}

/* �õ����ü���ֵ */
template<typename T>
inline size_t smart_pointer<T>::use_count()
{
	return this->Get_Reference();
}

/* �������� */
template<typename T>
inline smart_pointer<T>::smart_pointer(smart_pointer<T> &sp)
{
	cout << "���࿽������" << endl;

	/* ��ֹ�Լ����Լ��Ŀ��� */
	if (this != &sp) {
		this->_ptr = sp._ptr;
		this->GetCounter() = sp.GetCounter();
		this->Increase();
	}

}
/* ��ֵ���� */
template<typename T>
inline smart_pointer<T> &smart_pointer<T>::operator=(smart_pointer<T> &sp)
{

	/* ��ֹ�Լ����Լ��ĸ�ֵ�Լ�ָ����ͬ�ڴ浥Ԫ�ĸ�ֵ */
	if (this != &sp) {

		cout << "��ֵ����" << endl;

		/* ������ǹ���һ��������ָ�벢������ֻ��ָ�벻��ָ��ͬһ�ڴ浥Ԫ */
		/* =������ü�����1,=�ұ����ü�����1 */
		if (this->_ptr && this->_ptr != sp._ptr) {
			this->Decrease();

			/* ���ü���Ϊ0ʱ */
			if (!this->Get_Reference()) {
				cout << "���ü���Ϊ0,������������" << endl;
				this->~smart_pointer();
				//this->~Sp_counter();
				cout << "�������" << endl;
			}
		}

		this->_ptr = sp._ptr;
		this->GetCounter() = sp.GetCounter();
		this->Increase();
	}
	return *this;
}

/* ���ؽ�����*����� */
template<typename T>
inline T &smart_pointer<T>::operator*()
{
	return *(this->_ptr);
}
template<typename T>
inline T *smart_pointer<T>::operator->(void)
{
	return this->_ptr;
}