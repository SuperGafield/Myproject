#include "Mediator.h"

#include <iostream>
using namespace std;

CMediator::CMediator(A* pClassA, B* pClassB, C* pClassC)
{
	this->m_pClassA = pClassA;
	this->m_pClassB = pClassB;
	this->m_pClassC = pClassC;
}

void CMediator::ACallB()
{
	cout << "A Call : ";
	m_pClassB->BFuncSelf();
}

void CMediator::ACallC()
{
	cout << "A Call : ";
	m_pClassC->CFuncSelf();
}

void CMediator::BCallA()
{
	cout << "B Call : ";
	m_pClassA->AFuncSelf();
}

void CMediator::BCallC()
{
	cout << "B Call : ";
	m_pClassC->CFuncSelf();
}

void CMediator::CCallA()
{
	cout << "C Call : ";
	m_pClassA->AFuncSelf();
}

void CMediator::CCallB()
{
	cout << "C Call : ";
	m_pClassB->BFuncSelf();
}