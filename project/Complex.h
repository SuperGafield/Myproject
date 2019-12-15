#pragma once
using namespace std;
#include<iostream>;

class Complex
{
public:
	Complex(double real = 8.0, double image = 6.0)       //���캯��
		:_real(real), _image(image)
	{
		cout << " Complex(double real, double image)" << endl;
	}
	Complex(const Complex& d)          //��������
	{
		cout << "Complex(const Complex& d)" << endl;
		_real = d._real;
		_image = d._image;
	}
	~Complex()       //��������
	{
		cout << "~Complex() " << endl;
		_real = 0.0;
		_image = 0.0;
	}
	Complex& operator=(const Complex& d)         //��ֵ���������
	{
		cout << "=" << endl;
		if (this != &d)
		{
			_real = d._real;
			_image = d._image;
		}
		return *this;
	}
	void Display()const                //��ӡ����
	{
		cout << "_real:" << _real;
		cout << "      _image:" << _image << endl;
	}

	bool operator==(const Complex& d)             //==
	{
		cout << "==" << endl;
		return this->_real == d._real
			&& this->_image == d._image;
	}
	bool operator!=(const Complex& d)             //!=
	{
		cout << "!=" << endl;
		return this->_real != d._real
			|| this->_image == d._image;
	}
	//����ֻ�е��鲿Ϊ0ʱ����_image=0ʱ���ſ��ԱȽϴ�С����ʱ�Ƚϵ���ʵ����_real�Ĵ�С
	bool operator>(const Complex& d)          //>
	{
		if (this->_image != 0 || d._image != 0)
		{
			cout << "�޷��Ƚ�       ";
			return false;
		}

		else
		{
			return this->_real > d._real;
		}
	}
	bool operator<(const Complex& d)           //<
	{
		if (this->_image != 0 || d._image != 0)
		{
			cout << "�޷��Ƚ�      ";
			return false;
		}
		else
		{
			return this->_real < d._real;
		}
	}
	bool operator<=(const Complex& d)           //<=
	{
		if (this->_image != 0 || d._image != 0)
		{
			cout << "�޷��Ƚ�      ";
			return false;
		}
		else
		{
			return this->_real <= d._real;
		}
	}
	bool operator>=(const Complex& d)           //>=
	{
		if (this->_image != 0 || d._image != 0)
		{
			cout << "�޷��Ƚ�        ";
			return false;
		}
		else
		{
			return this->_real >= d._real;
		}
	}
	Complex operator+ (const Complex& d)           //+
	{
		cout << "+" << endl;
		Complex ret;
		ret._real = (this->_real + d._real);
		ret._image = (this->_image + d._image);
		return ret;
	}
	Complex& operator+=(const Complex& d)          //+=
	{
		cout << "+=" << endl;
		this->_real += d._real;
		this->_image += d._image;
		return *this;
	}
	Complex& operator++()            //ǰ��++
	{
		cout << "ǰ��++" << endl;
		this->_real += 1;
		return *this;
	}
	Complex operator++(int)         //����++
	{
		cout << "����++" << endl;
		Complex tmp(*this);
		this->_real += 1;
		return tmp;
	}

protected:
	double _real;
	double _image;
};