#include "Mediator.h"

#include <iostream>
using namespace std;

int main()
{
	A objA;
	B objB;
	C objC;

	CMediator objMediator(&objA, &objB, &objC);

	objA.SetMediator(&objMediator);
	objB.SetMediator(&objMediator);
	objC.SetMediator(&objMediator);

	objA.ACallB();
	objA.ACallC();

	objB.BCallA();
	objB.BCallC();

	objC.CCallA();
	objC.CCallB();

	return 0;
}