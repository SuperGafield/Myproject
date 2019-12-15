#ifndef _CLASS_A_H
#define _CLASS_A_H

// forward declaration
class B;
class C;
class CMediator;

class A
{
public:
	void SetMediator(CMediator* pMediator);
	void ACallB();
	void ACallC();
	void AFuncSelf();
private:
	B* m_pClassB;
	C* m_pClassC;
	CMediator* m_pMediator;
};

#endif