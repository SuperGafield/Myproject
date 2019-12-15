#include <iostream>
using namespace std;

// Scanner
class CScaner
{
public:
	void Scan(char* lpszFileNameIn) {cout << "Now scan: " << lpszFileNameIn << endl;}
};

// Parser
class CParser
{
public:
	void Parse(char* lpszFileNameIn) {cout << "Now parse: " << lpszFileNameIn << endl;}
};

// CodeGenerator
class CCodeGenerator
{
public:
	void CodeGenerate(char* lpszFileNameOut) {cout << "Now generate code: " << lpszFileNameOut << endl;}
};

// Compiler 
// Provide a Facade
class CCompiler
{
public:
	void Compile(char* lpszFileNameIn, char* lpszFileNameOut)
	{
		m_objScanner.Scan(lpszFileNameIn);
		m_objParser.Parse(lpszFileNameIn);
		m_objCodeGenerator.CodeGenerate(lpszFileNameOut);
	}
private:
	CScaner m_objScanner;
	CParser m_objParser;
	CCodeGenerator m_objCodeGenerator;
};

int main()
{
	// user only operate the compiler facade
	CCompiler objCompiler;
	objCompiler.Compile("TestFile.cpp", "TestFile.exe");

	return 0;
}