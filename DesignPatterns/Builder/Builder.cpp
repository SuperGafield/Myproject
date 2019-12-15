#include <iostream>
#include <string>
using namespace std;

class CCar
{
public:
	void WhoAmI() {cout << m_szBuf << endl;}
	void Drive() {cout << "Now Driving!" << endl;}
	void SetName(char* pszName) {strcpy(m_szBuf, pszName);}
private:
	char m_szBuf[128];
};

// Builder of the car
class CCarBuilder
{
public:
	virtual void BuildCar() = 0;
	virtual CCar* GetResult() = 0;
protected:
	// Constructor
	CCarBuilder() {};
};

// BMW
class CBMWBuilder : public CCarBuilder
{
public:
	CBMWBuilder() {m_pCar = NULL;}
	~CBMWBuilder() 
	{
		if (NULL != m_pCar)
		{
			delete m_pCar;
			m_pCar = NULL;
		}
	}
	virtual void BuildCar()
	{
		if (NULL == m_pCar)
		{
			m_pCar = new CCar();
		}
		m_pCar->SetName("I'm BMW!");
	}
	virtual CCar* GetResult() {return m_pCar;}
private:
	CCar* m_pCar;
};

void Drive(CCarBuilder& rBuilder)
{
	rBuilder.BuildCar();
	CCar* pCar = rBuilder.GetResult();
	pCar->WhoAmI();
	pCar->Drive();
}

int main()
{
	CBMWBuilder objBMWBuilder;
	Drive(objBMWBuilder);

	return 0;
}