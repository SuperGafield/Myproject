#include <iostream>
using namespace std;

// abstract class
class CSubject
{
public:
	virtual void BuyHouse() = 0;
	bool m_bIsDone;
};

// Buyer
class CBuyer : public CSubject
{
public:
	CBuyer() {m_bIsDone = false;}
	virtual void BuyHouse()
	{
		if (!m_bIsDone)
		{
			cout << "I'm User, I'm God! The thing I only do is pay you!" << endl;
			cout << "But there is some problem here, sorry!" << endl;
		}
		else
		{
			cout << "I'm User, I'm God! The thing I only do is pay you!" << endl;
			cout << "OK, All things be done! The house now belongs you!" << endl;
		}
	}
};

// Proxy
class CBuyerProxy : public CSubject
{
public:
	CBuyerProxy(CSubject* pSubject) {this->m_pSubject = pSubject;}
	virtual void BuyHouse()
	{
		cout << "I'm the Proxy, Now do step1" << endl;
		cout << "step2" << endl;
		cout << "step3" << endl;

		cout << "All steps be done, but also need you pay!" << endl;

		m_pSubject->m_bIsDone = true;
		m_pSubject->BuyHouse();
	}
private:
	CSubject* m_pSubject;
};

// global
void BuyHouse(CSubject* pSubject)
{
	pSubject->BuyHouse();
}

int main()
{
	CBuyer objBuyer;
	CBuyerProxy objBuyerProxy(&objBuyer);

	// Normal
	BuyHouse(&objBuyer);

	// Proxy
	BuyHouse(&objBuyerProxy);

	return 0;
}