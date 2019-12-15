#include <iostream>
#include <typeinfo>
#include <map>
using namespace std;

// forward declaration
class COfficeDoc;

// class who observe COfficeDoc
class CDocObserver
{
public:
	// class be observed
	CDocObserver(COfficeDoc* pDoc);
	void UpdateSelf(COfficeDoc* pDoc);
	void SetID(int nID) {this->m_nObserverID = nID;}

private:
	// Current ID
	int m_nObserverID;
};

class COfficeDoc
{
public:
	COfficeDoc() {m_nCnt = 1;}

	void Attach(CDocObserver* pObserver)
	{
		if (NULL == pObserver)
		{
			return;
		}

		m_mapObservers.insert(PAIR_OBSERVER(m_nCnt, pObserver));
		pObserver->SetID(m_nCnt);
		m_nCnt++;
	}

	void Detach(CDocObserver* pObserver)
	{
		if (NULL == pObserver)
		{
			return;
		}

		MAP_OBSERVER::iterator it;
		for (it=m_mapObservers.begin(); it!=m_mapObservers.end();)
		{
			if (pObserver == it->second)
			{
				m_mapObservers.erase(it++);
			}
			else
			{
				it++;
			}
		}
	}

	void ModifyData(int nData)
	{
		cout << "Now the data of the Doc is : " << nData << endl;
		this->m_nData = nData;

		// notify all
		NotifyObserver();
	}

	int GetData() {return this->m_nData;}

private:
	typedef map<int, CDocObserver*> MAP_OBSERVER;
	MAP_OBSERVER m_mapObservers;
	typedef pair<int, CDocObserver*> PAIR_OBSERVER;

	int m_nCnt;
	int m_nData;

	// notify all observer who has been attached
	void NotifyObserver()
	{
		MAP_OBSERVER::iterator it;
		for (it=m_mapObservers.begin(); it!=m_mapObservers.end(); it++)
		{
			it->second->UpdateSelf(this);
		}
	}
};

CDocObserver::CDocObserver(COfficeDoc *pDoc)
{
	pDoc->Attach(this);
}

void CDocObserver::UpdateSelf(COfficeDoc *pDoc)
{
	//const type_info& t = typeid(*pDoc);
	//cout << "I'm observer : " << t.name() << endl;

	cout << "I'm observer : " << m_nObserverID << endl;
	cout << "Update data : " << pDoc->GetData() << endl;

	// Do some other real update
}

int main()
{
	// be observed
	COfficeDoc objDoc;

	// observer
	CDocObserver objObserver1(&objDoc);
	CDocObserver objObserver2(&objDoc);
	CDocObserver objObserver3(&objDoc);
	CDocObserver objObserver4(&objDoc);
	CDocObserver objObserver5(&objDoc);
	CDocObserver objObserver6(&objDoc);
	CDocObserver objObserver7(&objDoc);

	// Update Doc data for test
	objDoc.ModifyData(123);
	objDoc.ModifyData(456);

 	objDoc.Detach(&objObserver1);
 	objDoc.Detach(&objObserver2);
 	objDoc.Detach(&objObserver3);

	objDoc.ModifyData(789);

	return 0;
}