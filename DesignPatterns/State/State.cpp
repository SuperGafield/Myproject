#include <iostream>
using namespace std;

class CState
{
public:
	virtual void Run() = 0;
};

class CRedState : public CState
{
public:
	void Run() {cout << "Red " << endl;}
};

class CGreenState : public CState
{
public:
	void Run() {cout << "Green " << endl;}
};

class CBlueState : public CState
{
public:
	void Run() {cout << "Blue " << endl;}
};

class CTrafficLight
{
public:
	CTrafficLight() {m_nRunTimes = 0, m_nTotalRunTimes = 100;}
	void SetState(CState* pState) {this->m_pState = pState;}
	void Run() {this->m_pState->Run(), m_nRunTimes++;}
	bool LightIsBad() 
	{
		if (m_nRunTimes > m_nTotalRunTimes)
		{
			cout << "Light is bad!" << endl;
			return true;
		}
		return false;
	} 
private:
	CState* m_pState;
	int m_nRunTimes;
	int m_nTotalRunTimes;
};

int main()
{
	// There is a traffic light
	CTrafficLight objTrafficLight;

	// Three states
	CRedState objRedState;
	CGreenState objGreenState;
	CBlueState objBlueState;

	while (!objTrafficLight.LightIsBad())
	{
		// change the states
		objTrafficLight.SetState(&objRedState);
		objTrafficLight.Run();
		objTrafficLight.SetState(&objGreenState);
		objTrafficLight.Run();
		objTrafficLight.SetState(&objBlueState);
		objTrafficLight.Run();
	}

	return 0;
}