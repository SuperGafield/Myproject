#ifndef _MEDIATOR_H
#define _MEDIATOR_H

#include "ClassA.h"
#include "ClassB.h"
#include "ClassC.h"

// forward declaration
class A;
class B;
class C;

class CMediator
{
public:
	CMediator(A* pClassA, B* pClassB, C* pClassC);

	void ACallB();
	void ACallC();

	void BCallA();
	void BCallC();

	void CCallA();
	void CCallB();

private:
	A* m_pClassA;
	B* m_pClassB;
	C* m_pClassC;
};

#endif 