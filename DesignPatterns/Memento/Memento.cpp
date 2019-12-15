#include <iostream>
#include <string>
using namespace std;

class CMemento
{
public:
	string GetState() {return m_strState;}
	void SetState(string strState) {this->m_strState = strState;}
private:
	string m_strState;
};

class COriginator
{
public:
	CMemento* CreateMemento()
	{
		CMemento* pMemento = new CMemento();
		pMemento->SetState(this->m_strState);
		return pMemento;
	}
	void SetMemento(CMemento* pMemento) {this->m_strState = pMemento->GetState();}
	void SetState(string& rstrState) {this->m_strState = rstrState;}
	string GetState() {return this->m_strState;}
private:
	string m_strState;
};

int main()
{
	COriginator objOriginator;
	objOriginator.SetState(string("State 1"));

	cout << "State of the Originator : " << objOriginator.GetState() << endl;

	// Save the state
	CMemento* pMemento = objOriginator.CreateMemento();

	objOriginator.SetState(string("State 2"));
	cout << "State of the Originator NOW : " << objOriginator.GetState() << endl;

	// Resume the state
	objOriginator.SetMemento(pMemento);
	cout << "State of the Originator AFTER RESUME : " << objOriginator.GetState() << endl;
	
	delete pMemento;
	pMemento = NULL;

	return 0;
}