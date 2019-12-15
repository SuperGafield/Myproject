#include <iostream>
#include <cassert>
using namespace std;

// 追MM模板
class CPursuitMMTemplate
{
public:
	CPursuitMMTemplate(char* pszName)
	{
		assert(pszName);
		strcpy(m_szBuf, pszName);
		cout << "I'm " << pszName << endl;
	}
	bool PursuitMM()
	{
		// 失败次数大于等于3失败！
		int nFailedTimes = 0;
		if (!Acquaint())
			nFailedTimes++;
		if (!Chat())
			nFailedTimes++;
		if (!Date())
			nFailedTimes++;

		if (nFailedTimes >= 3)
			return false;
		
		return true;
	}
	char* GetName() 
	{
		return m_szBuf;
	}
private:
	char m_szBuf[20];
// Atomic operations
protected:
	virtual bool Acquaint() = 0;
	virtual bool Chat()		= 0;
	virtual bool Date()		= 0;
};

// 可怜的Bob
class CBob : public CPursuitMMTemplate
{
public:
	CBob(char* pszName) : CPursuitMMTemplate(pszName) {}
protected:
	virtual bool Acquaint()
	{
		cout << "今晚的太阳真圆啊！" << endl;
		// MM : "白痴！"
		return false;
	}
	virtual bool Chat()
	{
		cout << "哇，你手表的时间和我的一样诶！" << endl;
		// MM : "白痴！"
		return false;
	}
	virtual bool Date()
	{
		cout << "晚上请你看电影啊！" << endl;
		// MM : "去死吧！"
		return false;
	}
};

// 幸运的Leo
class CLeo : public CPursuitMMTemplate
{
public:
	CLeo(char* pszName) : CPursuitMMTemplate(pszName) {}
protected:
	virtual bool Acquaint()
	{
		cout << "你们宿舍的XXX好漂亮啊！" << endl;
		// MM : "咦？对我就没有兴趣？？"
		return true;
	}
	virtual bool Chat()
	{
		cout << "我要打游戏，你别烦我啊！" << endl;
		// MM : "我偏不！"
		return true;
	}
	virtual bool Date()
	{
		cout << "晚上刚好没事，要不你就陪我压马路吧！" << endl;
		// MM : "哼，小样！"
		return true;
	}
};

void Pursuit(CPursuitMMTemplate* tPursuit)
{
	if (!tPursuit->PursuitMM())
	{	
		cout << tPursuit->GetName() << "Failed!" << endl;
	}
	else
	{
		cout << tPursuit->GetName() << "Succeed!" << endl;
	}
}

int main()
{
	CBob objBob("Bob");
	Pursuit(&objBob);

	CLeo objLeo("Leo");
	Pursuit(&objLeo);

	return 0;
}