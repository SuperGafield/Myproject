#include "pch.h"
#include"MemoryManagement.h"
#include"Complex.h"
#include <corecrt_malloc.h>

void MemoryManagement::Primitives()
{
	void*  p1 = malloc(512);  //512个字节
	free(p1);

	Complex * p2 = new Complex(1,2);
	delete p2;

	void * p3 =  ::operator new(512);
	::operator delete(p3);

//以下是C++标准库提供的allocators;其接口虽有标准规格，但实现厂商并未完全遵守。以下三种形式略同。
#ifdef _MSC_VER
//以下两个函数都是 non-static，定要通过 object 调用。以下分配 3 个 ints.
	int* p4 = allocator<int>().allocate(3, (int*)0);
	allocator<int>().deallocate(p4, 3);
#endif
#ifdef __BORLANDC__
	//以下两个函数都是 non-static，定要通过 object 调用。以下分配 5 个 ints.
	int* p4 = allocator<int>().allocate(5);
	allocator<int>().deallocate(p4, 5);
#endif
#ifdef __GNUC__
	//以下两个函数都是 static，可通过全名调用之。以下分配 512 bytes.
	void* p4 = alloc::allocate(512); 
	alloc::deallocate(p4,512);   

	//以下两个函数都是 non-static，定要通过 object 调用。以下分配 7个 ints.    
	void* p4 = allocator<int>().allocate(7);
	allocator<int>().deallocate((int*)p4, 7);

	//以下两个函数都是 non-static，定要通过 object 调用。以下分配 9 个 ints. 
	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
	__gnu_cxx::__pool_alloc<int>().deallocate((int*)p5, 9);
#endif

	Complex * p6 = new Complex(1, 2);
	//编译器转为
	Complex * p7=nullptr;
	try
	{
		void* part = ::operator new(sizeof(Complex));
		p7 = static_cast<Complex *>(part);
		//p7->Complex::Complex(1,2);//能不能这样写要看编译器，VC可以这么做（这应该是不太严谨的写法）
		new(p7) Complex(1,2);  //placement new方式
	}
	catch (std::bad_alloc)
	{
	}
	if (p7 != nullptr) { delete p7; }//可以写成if (p7!= nullptr) { p7->~Complex();  ::operator delete(p7);}

	//Array new,Array delete
	int msize = 3;
	Complex * p8 = new Complex[msize];
	//唤起三次“默认构造函数”
	//无法借由参数给予初值
	//可以通过调用placement new来设初值
	for (int i=0;i < msize;i++)
	{
		new(p8++)Complex(1,2);
	}
	delete  [ ]p8; //唤起三次析构函数

	int *p9 = new int[10];
	delete p9;//此处“[]”无任何意义,可以不用

	//没有机会设初值，调用了三次构造函数
	Complex * p10 = new Complex[3];
	//唤起三次析构函数，对class without ptr member可能没有影响，对class  with ptr member可能有影响（这里Complex without ptr member）。
	delete[] p10;

	//没有机会设初值，调用了三次构造函数
	string * p11 = new  string[3];
	//唤起三次析构函数，对class without ptr member可能没有影响，对class  with ptr member可能有影响（这里string with ptr member）。
	delete[] p11;





}