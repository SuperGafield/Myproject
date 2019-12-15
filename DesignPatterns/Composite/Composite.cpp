#include <iostream>
#include <vector>

using namespace std;

// abstract class
class CPersonComponent
{
public:
	CPersonComponent() {}
	virtual ~CPersonComponent() {}

	virtual void DoClean() = 0;
	virtual void Add(const CPersonComponent* pPerson) {}

protected:
	char m_szName[20];
};

class CPersonComposite : public CPersonComponent
{
public:
	virtual void DoClean()
	{
		VEC_PERSONCOMPONENT::iterator it;
		for (it=m_vecPersonComponent.begin(); it!=m_vecPersonComponent.end(); it++)
		{
			(*it)->DoClean();
		}
	}

	virtual void Add(CPersonComponent* pPerson) {m_vecPersonComponent.push_back(pPerson);}

	virtual void Release()
	{
		VEC_PERSONCOMPONENT::iterator it;
		for (it=m_vecPersonComponent.begin(); it!=m_vecPersonComponent.end(); it++)
		{
			delete (*it);
		}
	}

private:
	typedef vector<CPersonComponent*> VEC_PERSONCOMPONENT;
	VEC_PERSONCOMPONENT m_vecPersonComponent;
};

class CStudent : public CPersonComponent
{
public:
	CStudent(const char* pszName) {strcpy(m_szName, pszName);}
	virtual ~CStudent() {}

	virtual void DoClean()
	{
		cout << "I'm student : " << m_szName << endl;
		cout << "I'm do cleaning now!" << endl;
	}
};

int main()
{
	CStudent* s1 = new CStudent("No. 1");
	s1->DoClean();
	cout << endl;

	char szBuf[20];
	CPersonComposite sGroup;
	for (int i=2; i<11; i++)
	{
		sprintf(szBuf, "No. %d", i);
		CStudent* ss = new CStudent(szBuf);
		sGroup.Add(ss);
	}
	sGroup.DoClean();

	delete s1;
	sGroup.Release();

	return 0;
}