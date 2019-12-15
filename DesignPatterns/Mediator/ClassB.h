#ifndef _CLASS_B_H
#define _CLASS_B_H

// forward declaration
class A;
class C;
class CMediator;

class B
{
public:
	void SetMediator(CMediator* pMediator);
	void BCallA();
	void BCallC();
	void BFuncSelf();
private:
	A* m_pClassA;
	C* m_pClassC;
	CMediator* m_pMediator;
};

#endif