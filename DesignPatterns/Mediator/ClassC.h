#ifndef _CLASS_C_H
#define _CLASS_C_H

// forward declaration
class A;
class B;
class CMediator;

class C
{
public:
	void SetMediator(CMediator* pMediator);
	void CCallA();
	void CCallB();
	void CFuncSelf();
private:
	A* m_pClassA;
	B* m_pClassB;
	CMediator* m_pMediator;
};

#endif