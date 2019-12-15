#include <iostream>
using namespace std;

// class already existed
class CCircle_X
{
public:
	CCircle_X() {cout << "I'm Circle_X" << endl;}
	void DisplayX() {cout << "Display a circle" << endl;}
};

// abstract class
class CShape
{
public:
	virtual void Display() = 0;
};

// use adapter
class CCircle : public CShape
{
public:
	CCircle() {cout << "I'm CCircle" << endl;}
	virtual void Display()
	{
		cout << "use already existed class to help us" << endl;
		m_CircleX.DisplayX();	
	}

private:
	CCircle_X m_CircleX;
};

int main()
{
	CCircle objCircle;
	objCircle.Display();
}