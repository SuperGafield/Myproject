#include <iostream>
#include <cassert>
using namespace std;

// prototype class
class CPrototype
{
public:
	virtual CPrototype* Clone() const = 0;
};

class CCircle : public CPrototype
{
public:
	CCircle() {cout << "New a circle by Constructor." << endl;}

	// copy constructor
	CCircle(const CCircle& rCircle) {strcpy(m_szBuf, rCircle.m_szBuf);}

	virtual CPrototype* Clone() const
	{
		cout << "Clone a circle, I'll call the constructor!" << endl;
		return new CCircle(*this);
	}

	void SetName(char* lpszName) {strcpy(m_szBuf, lpszName);}
	void WhoAmI() {cout << "I'm circle : " << m_szBuf << endl;}
private:
	char m_szBuf[100];
};

int main()
{
	cout << "New a circle." << endl;
	CCircle c1;
	c1.SetName("No.1");
	c1.WhoAmI();

	CCircle* c2 = static_cast<CCircle*>(c1.Clone());

	cout << "What object has been copy?" << endl;
	c2->WhoAmI();

	cout << "Now I'm be assigned a new name, I'm a new object now!" << endl;
	c2->SetName("No.2");
	c2->WhoAmI();

	delete c2;

	return 0;
}