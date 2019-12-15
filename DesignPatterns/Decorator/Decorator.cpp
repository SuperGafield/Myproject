#include <iostream>
using namespace std;

// abstract class
class CChildComponent
{
public:
	virtual void Eat() = 0;
};

class CChild : public CChildComponent
{
public:
	virtual void Eat() {cout << "I'm eating!" << endl;}
};

// decorator class, also derived from class CChildComponent
class CDecorator : public CChildComponent
{
public:
	CDecorator(CChildComponent* pChildCom) {this->m_pChildCom = pChildCom;}
	virtual void Eat() {}
protected:
	CChildComponent* m_pChildCom;
};

// decorator class implement, for eat apple 
class CChildDecorator : public CDecorator
{
public:
	CChildDecorator(CChildComponent* pChildCom) : CDecorator(pChildCom) {}
	virtual void Eat()
	{
		cout << "First I want to eat a apple." << endl;
		//cout << "Do any other thing!" << endl;
		m_pChildCom->Eat();
	}
};

// Client code
int main()
{
	CChild objChild;
	objChild.Eat();

	CChildDecorator objChildDecorator(&objChild);
	objChildDecorator.Eat();

	return 0;
}