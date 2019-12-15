#include <iostream>
using namespace std;

const int MAX_NUM = 100;
template <typename T>

class CContainer
{
public:
	typedef T* Iterator;
	CContainer() {m_nCnt = 0;}
public:
	Iterator Begin() {return &m_arrT[0];}
	Iterator End()	 {return &m_arrT[m_nCnt];}
	void Insert(T tVal) 
	{
		if (m_nCnt > MAX_NUM)
		{
			cout << "Container full, can not insert new value..." << endl;
			return;
		}
		else
		{
			m_arrT[m_nCnt] = tVal;
			m_nCnt++;
		}
	}
private:
	int m_nCnt;
	T m_arrT[MAX_NUM];
};

int main()
{
	CContainer<float> objContainer;
	objContainer.Insert(1.0f);
	objContainer.Insert(2.0f);
	objContainer.Insert(3.0f);

	CContainer<float>::Iterator it;
	for (it=objContainer.Begin(); it!=objContainer.End(); it++)
	{
		cout << fixed << *it << endl;
	}

	return 0;
}