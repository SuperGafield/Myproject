// project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include <iostream>
#include "Smart_pointer.h"
#include "Complex.h"
#include "MemoryManagement.h"
#include "LeetCode.h"
#include <functional>
#include <algorithm>

#include <array>
#include <ctime> 
#include <cstdlib> //qsort, bsearch, NULL
const long  ASIZE = 500000;

long get_a_target_long()
{
	long target = 0;

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	return target;
}

string get_a_target_string()
{
	long target = 0;
	char buf[10];

	cout << "target (0~" << RAND_MAX << "): ";
	cin >> target;
	snprintf(buf, 10, "%d", target);
	return string(buf);
}

int compareLongs(const void* a, const void* b)
{
	return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b)
{
	if (*(string*)a > *(string*)b)
		return 1;
	else if (*(string*)a < *(string*)b)
		return -1;
	else
		return 0;
}

	void test_array()
	{
		cout << "\ntest_array().......... \n";

		array<long, ASIZE> c;

		clock_t timeStart = clock();
		for (long i = 0; i < ASIZE; ++i) {
			c[i] = rand();
		}
		cout << "milli-seconds : " << (clock() - timeStart) << endl;	//
		cout << "array.size()= " << c.size() << endl;
		cout << "array.front()= " << c.front() << endl;
		cout << "array.back()= " << c.back() << endl;
		cout << "array.data()= " << c.data() << endl;

		long target = get_a_target_long();

		timeStart = clock();
		::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
		long* pItem = (long*)::bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
		cout << "qsort()+bsearch(), milli-seconds : " << (clock() - timeStart) << endl;	//    
		if (pItem != NULL)
			cout << "found, " << *pItem << endl;
		else
			cout << "not found! " << endl;
}


int main()
{
	array<int, 10> ttt = { 1,2,3,4,5,6,7,8,9,0 };
	Arrayq<int,5>  sss = new  Arrayq<int>();

	SolutionTwoSum * object = new  SolutionTwoSum();
	int dArray[7] = { 1,2,3,4,5,9,8 };
	const vector<int> Nums(dArray, dArray + 7); //从数组中获得初值
	vector<int> indexs = object->GetIndexs(Nums, 5);
	delete object;

	//Complex *integer = new Complex(1,2);
	Complex *integer;
	int complexNum = sizeof(Complex);
	void *  mem = ::operator new(complexNum);
	integer = static_cast<Complex *>(mem);
	integer->Complex::Complex(1,2);
	delete integer;

	MemoryManagement  * memorytest = new MemoryManagement();
	memorytest->Primitives();
	delete memorytest;


	//Complex* pc = new Complex(1, 2); 此处new称为表达式或运算符new，编译器将其转化为一下代码：
	Complex* pc;
	try
	{
		void* mem = operator new(sizeof(Complex));  // 底层调用malloc函数分配内存
		pc = static_cast<Complex*>(mem);
		//pc->Complex::Complex(1, 2); 
		new(pc) Complex(1, 2);
		// 一般由分配器的construct函数完成，主要工作：
									 // 使用placement new: new(mem)(arguments_list)
									 // 即：pc = new(mem)(1,2)完成初始化
									 // 相应的析构对象时调用分配器的destroy函数，释放内
									 // 存则调用operator delete
		pc->Complex::Complex(1, 2);
		new(pc) Complex(1, 2);

	}
	catch (std::bad_alloc)
	{
		// 处理可能出现的异常
	}

	Complex * ptr;
	void *memory = operator new(sizeof(Complex));
	ptr = static_cast<Complex*>(memory);
	ptr->~Complex();
	operator delete(ptr);

	int arraydemo[6] = { 100,56,85,34,24,20 };
	vector<int, allocator<int>> ai(arraydemo, arraydemo+6);
	cout << count_if(ai.begin(), ai.end(), not1(bind2nd(less<int>(), 40)));

	int *a = new int(10);
	int *b = new int(20);
	cout << "-------------默认构造测试----------------->" << endl;
	cout << "构造sp" << endl;
	smart_pointer<int> sp(a);
	cout << "sp.use_count:" << sp.use_count() << endl;
	cout << "------------------------------------------>" << endl << endl;

	{
		cout << "-------------拷贝构造测试----------------->" << endl;
		cout << "构造sp1  :sp1(sp)" << endl;
		smart_pointer<int> sp1(sp);
		cout << "构造sp2  :sp2(sp)" << endl;
		smart_pointer<int> sp2(sp1);
		cout << "sp1和sp2引用计数为3才是正确的" << endl;
		cout << "sp1.use_count:" << sp1.use_count() << endl;
		cout << "sp2.use_count:" << sp2.use_count() << endl;
		cout << "------------------------------------------>" << endl << endl;
		cout << "调用析构释放sp1,sp2" << endl;
	}
	cout << "-------------析构函数测试----------------->" << endl;
	cout << "此处sp.use_count应该为1才是正确的" << endl;
	cout << "sp.use_count:" << sp.use_count() << endl;
	cout << "------------------------------------------>" << endl << endl;

	cout << "-------------赋值构造测试----------------->" << endl;
	cout << "构造sp3  :sp3(b)" << endl;
	smart_pointer<int> sp3(b);
	cout << "sp3.use_count:" << sp3.use_count() << endl;
	cout << "sp3 = sp" << endl;
	sp3 = sp;
	cout << "sp3先被释放,然后sp3引用计数为2才正确,sp的引用计数为2才正确" << endl;
	cout << "sp3.use_count:" << sp3.use_count() << endl;
	cout << "sp.use_count :" << sp.use_count() << endl;
	cout << "------------------------------------------>" << endl << endl;

	cout << "-------------解引用测试----------------->" << endl;
	cout << "*sp3:" << *sp3 << endl;
	cout << "*sp3 = 100" << endl;
	*sp3 = 100;
	cout << "*sp3:" << *sp3 << endl;
	cout << "------------------------------------------>" << endl;



	// cout<<"sp3.use_count:"<<sp3.use_count()<<endl;
	 //cout<<"sp.use_count:"<<sp.use_count()<<endl;


	cout << "===================end main====================" << endl;

	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
