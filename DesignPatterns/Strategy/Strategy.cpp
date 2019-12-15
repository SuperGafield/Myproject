#include <iostream>
#include <string>
using namespace std;

class IStrategy
{
public:
	virtual void OutputDebug(string strDebug) = 0;
};

class CPrintStrategy : public IStrategy
{
public:
	virtual void OutputDebug(string strDebug) {cout << "Use Print STRATEGY" << strDebug << endl;}
};

class CLogStrategy : public IStrategy
{
public:
	virtual void OutputDebug(string strDebug) {cout << "Use Log STRATEGY" << strDebug << endl;}
};

// 使用Strategy的上下文Context
class CContext
{
public:
	void SetStrategy(IStrategy* pStrategy) {this->pStrategy = pStrategy;}
	void Function() {this->pStrategy->OutputDebug(" Succeed");}
private:
	IStrategy* pStrategy;
};

int main()
{
	CContext objContext;
	CPrintStrategy objPrintStrategy;
	CLogStrategy objLogStrategy;

	// Use Print STRATEGY
	objContext.SetStrategy(&objPrintStrategy);
	objContext.Function();

	// Use Log STRATEGY
	objContext.SetStrategy(&objLogStrategy);
	objContext.Function();

	return 0;
}