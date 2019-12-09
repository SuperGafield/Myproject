// project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include "pch.h"
#include <iostream>
#include "Smart_pointer.h"

int main()
{

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
