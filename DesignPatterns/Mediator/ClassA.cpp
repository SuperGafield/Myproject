#include "ClassA.h"
#include "ClassB.h"
#include "ClassC.h"
#include "Mediator.h"

#include <iostream>
using namespace std;

void A::SetMediator(CMediator* pMediator)
{
	this->m_pMediator = pMediator;
}

void A::ACallB()
{
	this->m_pMediator->ACallB();
}

void A::ACallC()
{
	this->m_pMediator->ACallC();
}

void A::AFuncSelf()
{
	cout << "This is A's Function Self!" << endl;
}