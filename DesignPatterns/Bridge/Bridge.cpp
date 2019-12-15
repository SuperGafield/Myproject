#include <iostream>
using namespace std;

class CDrawLib1
{
public:
	void DrawCircle()
	{
		cout << "Draw Circle Operation USE LIB 1" << endl;
	}
	void DrawRect()
	{
		cout << "Draw Rect Operation USE LIB 1" << endl;
	}
	void DrawTriangle()
	{
		cout << "Draw Triangle Operation USE LIB 1" << endl;
	}
};

class CDrawLib2
{
public:
	void DrawCircle()
	{
		cout << "Draw Circle Operation USE LIB 2" << endl;
	}
	void DrawRect()
	{
		cout << "Draw Rect Operation USE LIB 2" << endl;
	}
	void DrawTriangle()
	{
		cout << "Draw Triangle Operation USE LIB 2" << endl;
	}
};

class CShapeImpl
{
public:
	virtual void DrawCircle() = 0;
	virtual void DrawRect() = 0;
};

class CShapeImpl1 : public CShapeImpl
{
public:
	virtual void DrawCircle() {m_objDrawLib1.DrawCircle();}
	virtual void DrawRect()	{m_objDrawLib1.DrawRect();}
private:
	CDrawLib1 m_objDrawLib1;
};

class CShapeImpl2 : public CShapeImpl
{
public:
	virtual void DrawCircle() {m_objDrawLib2.DrawCircle();}
	virtual void DrawRect() {m_objDrawLib2.DrawRect();}
private:
	CDrawLib2 m_objDrawLib2;
};

class CShape
{
public:
	virtual void Draw() = 0;
protected:
	CShapeImpl* m_pShapeImpl;
};

class CCircle : public CShape
{
public:
	CCircle(CShapeImpl* pShapeImpl) {m_pShapeImpl = pShapeImpl;}
	virtual void Draw() {m_pShapeImpl->DrawCircle();}
};

class CRect : public CShape
{
public:
	CRect(CShapeImpl* pShapeImpl) {m_pShapeImpl = pShapeImpl;}
	virtual void Draw() {m_pShapeImpl->DrawRect();}
};

// Use Bridge Pattern
int main()
{
	CShapeImpl1 objShapeImpl1;
	CShapeImpl2 objShapeImpl2;

	// Use Lib1
	CCircle objCircle1(&objShapeImpl1);
	CRect objRect1(&objShapeImpl1);
	objCircle1.Draw();
	objRect1.Draw();

	// Use Lib2
	CCircle objCircle2(&objShapeImpl2);
	CRect objRect2(&objShapeImpl2);
	objCircle2.Draw();
	objRect2.Draw();

	return 0;
}