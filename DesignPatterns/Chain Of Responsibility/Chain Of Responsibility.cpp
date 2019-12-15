#include <iostream>
using namespace std;

class IHandler
{
public:
	// assign the next
	IHandler(IHandler* pSuccessor) : m_pSuccessor(pSuccessor) {}
	virtual ~IHandler() {}

	virtual void HandleRequest()
	{
		if (m_pSuccessor)
		{
			cout << this->m_szBuf << ": " << "I have no Apple, Ask " << m_pSuccessor->m_szBuf << endl;
			m_pSuccessor->HandleRequest();
		}
		else
		{
			cout << "Just to buy one..." << endl;
		}
	}
	virtual bool HasHandle() {return false;}
	virtual void SetSuccessor(IHandler* pSuccessor) {m_pSuccessor = pSuccessor;}
public:
	IHandler* m_pSuccessor;
	char m_szBuf[128];
};

class CMum : public IHandler
{
public:
	CMum(IHandler* pSuccessor) : IHandler(pSuccessor) {strcpy(m_szBuf, "Mum");}
	virtual void HandleRequest()
	{
		if (HasHandle())
		{
			cout << "Come on, Mum give you a Apple!" << endl;
		}
		else
		{
			IHandler::HandleRequest();
		}
	}
	virtual bool HasHandle() {return false;}
};

class CDad : public IHandler
{
public:
	CDad(IHandler* pSuccessor) : IHandler(pSuccessor) {strcpy(m_szBuf, "Dad");}
	virtual void HandleRequest()
	{
		if (HasHandle())
		{
			cout << "Come on, Dad give you a Apple!" << endl;
		}
		else
		{
			IHandler::HandleRequest();
		}
	}
	virtual bool HasHandle() {return false;}
};

class CUncle : public IHandler
{
public:
	CUncle(IHandler* pSuccessor) : IHandler(pSuccessor) {strcpy(m_szBuf, "Uncle");}
	virtual void HandleRequest()
	{
		if (HasHandle())
		{
			cout << "Come on, Uncle give you a Apple!" << endl;
		}
		else
		{
			IHandler::HandleRequest();
		}
	}
	// end of the chain of responsibility, so return true
	virtual bool HasHandle() {return true;}	 
};

void AskApple(IHandler* pHandle)
{
	cout << "Ask " << pHandle->m_szBuf << " to get a Apple" << endl;
	pHandle->HandleRequest();
}

int main()
{
	// create a chain of responsibility
	CUncle objUncle(NULL);
	CDad objDad(&objUncle);
	CMum objMun(&objDad);

	AskApple(&objMun);

	return 0;
}