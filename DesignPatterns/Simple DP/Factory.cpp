#include <iostream>
using namespace std;

// Interface only
class CFruit
{
public:
	virtual void Something() = 0;
};

// Instances
class CApple : public CFruit
{
public:
	virtual void Something() {cout << "I'm a Apple." << endl;}
};

class CPear : public CFruit
{
public:
	virtual void Something() {cout << "I'm a Pear." << endl;}
};

class COrange : public CFruit
{
public:
	virtual void Something() {cout << "I'm a Orange." << endl;}
};

enum eFruitType {APPLE = 1, PEAR, ORANGE};

// return a Instance
class CFruitFactory
{
public:
	CFruit* getFruitInstance(eFruitType etype)
	{
		cout << "Fruit now producing in factory..." << endl;

		switch (etype)
		{
		case APPLE:
			{
				return new CApple();
			}
			break;
		case PEAR:
			{
				return new CPear();
			}
			break;
		case ORANGE:
			{
				return new COrange();
			}
			break;
		default:
			{
				return NULL;
			}
			break;
		}
	}
};

int main()
{
	CFruitFactory factory;
	CFruit* fruit;

	cout << "Which fruit do you want?" << endl;
	cout << "1 Apple, 2 Pear, 3 Orange" << endl;
	int nType = 0;
	cin >> nType;

	fruit = factory.getFruitInstance((eFruitType)nType);
	if (NULL == fruit)
	{
		cout << "This fruit is not produced by the factory..." << endl;
		return -1;
	}

	fruit->Something();

	return 0;
}