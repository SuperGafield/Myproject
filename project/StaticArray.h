//Array.h
#include <iostream>
#include <exception>

template<typename T>
class Arrayq
{
public:
	virtual bool set(int i, const T& e) //����Ŀ��λ�õ�Ԫ��ֵ
	{
		bool ret = ((0 <= i) && (i < length()));
		if (ret)
			m_array[i] = e;

		return ret;
	}

	virtual bool get(int i, T& e)   //��ȡĿ��λ�õ�Ԫ��ֵ
	{
		bool ret = ((0 <= i) && (i < length()));
		if (ret)
			e = m_array[i];

		return ret;
	}

	T& operator[](int i)    //[]���������غ�����ʵ���±����
	{
		if ((0 <= i) && (i < length()))
			return m_array[i];
		else
			throw(std::out_of_range("Array::operator[] out of range"));
	}

	T& operator[](int i) const  //[]���������غ�����const�汾���������const����ʹ��
	{
		return const_cast<Arrayq<T>&>(*this)[i];
	}

	virtual int length() const = 0;

protected:
	T* m_array;
};

template<typename T, int N>
class StaticArray : public Arrayq<T>
{
protected:
	T m_space[N];   //��������

public:
	StaticArray()
	{
		this->m_array = m_space;
	}

	StaticArray(const StaticArray<T, N>& obj)   //ʵ�������Ŀ���
	{
		for (int i = 0; i < N; i++)
			m_space[i] = obj.m_space[i];

		this->m_array = m_space;
	}

	StaticArray<T, N>& operator=(const StaticArray<T, N>& obj) //ʵ�������Ŀ���
	{
		if (this != &obj)
		{
			for (int i = 0; i < N; i++)
				m_space[i] = obj.m_space[i];
		}

		return *this;
	}

	int length() const { return N; }
};

//main.cpp
//int main(void)
//{
//	StaticArray<int, 6> p;
//	StaticArray<int, 6> p1;
//
//	for (int i = 0; i < 6; i++)
//		p[i] = i;
//
//	p1 = p;
//
//	for (int i = 0; i < 6; i++)
//		std::cout << p1[i] << std::endl;
//
//	getchar();
//
//	return 0;
//}
//