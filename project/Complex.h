#pragma once
using namespace std;
#include<iostream>;

class Complex
{
public:
	Complex(double real = 8.0, double image = 6.0)       //构造函数
		:_real(real), _image(image)
	{
		cout << " Complex(double real, double image)" << endl;
	}
	Complex(const Complex& d)          //拷贝函数
	{
		cout << "Complex(const Complex& d)" << endl;
		_real = d._real;
		_image = d._image;
	}
	~Complex()       //析构函数
	{
		cout << "~Complex() " << endl;
		_real = 0.0;
		_image = 0.0;
	}
	Complex& operator=(const Complex& d)         //赋值运算符重载
	{
		cout << "=" << endl;
		if (this != &d)
		{
			_real = d._real;
			_image = d._image;
		}
		return *this;
	}
	void Display()const                //打印复数
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
	//复数只有当虚部为0时，即_image=0时，才可以比较大小，这时比较的是实部即_real的大小
	bool operator>(const Complex& d)          //>
	{
		if (this->_image != 0 || d._image != 0)
		{
			cout << "无法比较       ";
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
			cout << "无法比较      ";
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
			cout << "无法比较      ";
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
			cout << "无法比较        ";
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
	Complex& operator++()            //前置++
	{
		cout << "前置++" << endl;
		this->_real += 1;
		return *this;
	}
	Complex operator++(int)         //后置++
	{
		cout << "后置++" << endl;
		Complex tmp(*this);
		this->_real += 1;
		return tmp;
	}

protected:
	double _real;
	double _image;
};