#include "ClassA.h"
#include "ClassB.h"
#include "ClassC.h"
#include "Mediator.h"

#include <iostream>
using namespace std;

void B::SetMediator(CMediator* pMediator)
{
	this->m_pMediator = pMediator;
}

void B::BCallA()
{
	this->m_pMediator->BCallA();
}

void B::BCallC()
{
	this->m_pMediator->BCallC();
}

void B::BFuncSelf()
{
	cout << "This is B's Function Self!" << endl;
}