#include "pch.h"
#include"MemoryManagement.h"
#include"Complex.h"
#include <corecrt_malloc.h>

void MemoryManagement::Primitives()
{
	void*  p1 = malloc(512);  //512���ֽ�
	free(p1);

	Complex * p2 = new Complex(1,2);
	delete p2;

	void * p3 =  ::operator new(512);
	::operator delete(p3);

//������C++��׼���ṩ��allocators;��ӿ����б�׼��񣬵�ʵ�ֳ��̲�δ��ȫ���ء�����������ʽ��ͬ��
#ifdef _MSC_VER
//���������������� non-static����Ҫͨ�� object ���á����·��� 3 �� ints.
	int* p4 = allocator<int>().allocate(3, (int*)0);
	allocator<int>().deallocate(p4, 3);
#endif
#ifdef __BORLANDC__
	//���������������� non-static����Ҫͨ�� object ���á����·��� 5 �� ints.
	int* p4 = allocator<int>().allocate(5);
	allocator<int>().deallocate(p4, 5);
#endif
#ifdef __GNUC__
	//���������������� static����ͨ��ȫ������֮�����·��� 512 bytes.
	void* p4 = alloc::allocate(512); 
	alloc::deallocate(p4,512);   

	//���������������� non-static����Ҫͨ�� object ���á����·��� 7�� ints.    
	void* p4 = allocator<int>().allocate(7);
	allocator<int>().deallocate((int*)p4, 7);

	//���������������� non-static����Ҫͨ�� object ���á����·��� 9 �� ints. 
	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
	__gnu_cxx::__pool_alloc<int>().deallocate((int*)p5, 9);
#endif

	Complex * p6 = new Complex(1, 2);
	//������תΪ
	Complex * p7=nullptr;
	try
	{
		void* part = ::operator new(sizeof(Complex));
		p7 = static_cast<Complex *>(part);
		//p7->Complex::Complex(1,2);//�ܲ�������дҪ����������VC������ô������Ӧ���ǲ�̫�Ͻ���д����
		new(p7) Complex(1,2);  //placement new��ʽ
	}
	catch (std::bad_alloc)
	{
	}
	if (p7 != nullptr) { delete p7; }//����д��if (p7!= nullptr) { p7->~Complex();  ::operator delete(p7);}

	//Array new,Array delete
	int msize = 3;
	Complex * p8 = new Complex[msize];
	//�������Ρ�Ĭ�Ϲ��캯����
	//�޷����ɲ��������ֵ
	//����ͨ������placement new�����ֵ
	for (int i=0;i < msize;i++)
	{
		new(p8++)Complex(1,2);
	}
	delete  [ ]p8; //����������������

	int *p9 = new int[10];
	delete p9;//�˴���[]�����κ�����,���Բ���

	//û�л������ֵ�����������ι��캯��
	Complex * p10 = new Complex[3];
	//��������������������class without ptr member����û��Ӱ�죬��class  with ptr member������Ӱ�죨����Complex without ptr member����
	delete[] p10;

	//û�л������ֵ�����������ι��캯��
	string * p11 = new  string[3];
	//��������������������class without ptr member����û��Ӱ�죬��class  with ptr member������Ӱ�죨����string with ptr member����
	delete[] p11;





}