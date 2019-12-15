#include <iostream>
using namespace std;

// Command class
class CCommand
{
public:
	virtual ~CCommand() {}
	virtual void Execute() = 0;
};

class CReceiver
{
public:
	CReceiver(char* pszName) {strcpy(m_szName, pszName);}
	void Action() {cout << this->m_szName << " Receive the COMMAND!" << endl;}
private:
	char m_szName[128];
};

class CCommandPK : public CCommand
{
public:
	CCommandPK(CReceiver* pReceive) : m_pReceive(pReceive) {}
	virtual void Execute() {m_pReceive->Action();}
private:
	CReceiver* m_pReceive;
};

class CCommandGM : public CCommand
{
public:
	CCommandGM(CReceiver* pReceive) : m_pReceive(pReceive) {}
	virtual void Execute() {m_pReceive->Action();}
private:
	CReceiver* m_pReceive;
};

class CInvoker
{
public:
	CInvoker(CCommand* pCommand) : m_pCommand(pCommand) {}
	void Invoke() {m_pCommand->Execute();} 
private:
	CCommand* m_pCommand;
};

int main()
{
	// There are two RECEIVERS
	CReceiver objReceive1("Bob");
	CReceiver objReceive2("Leo");

	CCommandPK objCommandPK(&objReceive1); // Bob PK
	CCommandGM objCommandGM(&objReceive2); // Leo GM

	CInvoker objInvoker1(&objCommandPK);   // Invoke PK
	CInvoker objInvoker2(&objCommandGM);   // Invoke GM

	objInvoker1.Invoke();
	objInvoker2.Invoke();

	return 0;
}