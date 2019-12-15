// the system configure file must be only one
// so we use Singleton Pattern

#include <iostream>
#include <cassert>
using namespace std;

#define OUT

class CConfigFile
{
// private constructor
private:
	CConfigFile() {}
public:
	// static member function for access static member variable
	static CConfigFile* getSingleton();
	void getConfigData(OUT int& rData) {rData = this->m_nData;}
	void setConfigData(int nData) {this->m_nData = nData;}
private:
	// static member variable
	static CConfigFile* _Instance;
	int m_nData;
};

// Initialize static member variable
CConfigFile* CConfigFile::_Instance = NULL;

// get Singleton here
CConfigFile* CConfigFile::getSingleton()
{
	if (NULL == _Instance)
	{
		_Instance = new CConfigFile;
	}

	return _Instance;
}

int main()
{
	CConfigFile* pConfigFile = CConfigFile::getSingleton();

	pConfigFile->setConfigData(3);

	int nTmp = 0;
	pConfigFile->getConfigData(nTmp);

	assert(3 == nTmp);
	cout << "Work Done!" << endl;

	return 0;
}