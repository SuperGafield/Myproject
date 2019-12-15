#include "ClassA.h"
#include "ClassB.h"
#include "ClassC.h"
#include "Mediator.h".

#include <iostream>
using namespace std;

void C::SetMediator(CMediator* pMediator)
{
	this->m_pMediator = pMediator;
}

void C::CCallA()
{
	this->m_pMediator->CCallA();
}

void C::CCallB()
{
	this->m_pMediator->CCallB();
}

void C::CFuncSelf()
{
	cout << "This is C's Function Self!" << endl;
}