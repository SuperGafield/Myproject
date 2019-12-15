#include <iostream>
#include <string>
using namespace std;

class CElement;

class CVisitor
{
public:
	virtual void Visit(CElement* pElement) = 0;
};

class CVisitorA : public CVisitor
{
public:
	virtual void Visit(CElement* pElement) {cout << " Execute OPERATION A" << endl;}
};

class CVisitorB : public CVisitor
{
public:
	virtual void Visit(CElement* pElement) {cout << " Execute OPERATION B" << endl;}
};

class CElement
{
public:
	virtual void Accept(CVisitor* pVisitor) {cout << m_strName, pVisitor->Visit(this);}
	string& GetName() {return m_strName;}
protected:
	string m_strName;
};

class CElementA : public CElement
{
public:
	CElementA(string strName) {m_strName = strName;}
};

class CElementB : public CElement
{
public:
	CElementB(string strName) {m_strName = strName;}
};

int main()
{
	CElementA objElementA("Element A");
	CElementB objElementB("Element B");

	CVisitorA objVisitorA;
	CVisitorB objVisitorB;

	objElementA.Accept(&objVisitorA);
	objElementA.Accept(&objVisitorB);
	
	objElementB.Accept(&objVisitorA);
	objElementB.Accept(&objVisitorB);

	return 0;
}