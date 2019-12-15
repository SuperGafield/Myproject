#pragma once
#include "Complex.h"
#include <assert.h>

#define MAX_SIZE 50000
//�ڴ����
class MemoryAlloc
{
public:
	MemoryAlloc()
	{
		_pBuff = nullptr;
		_pHead = nullptr;
		_nBlockSize = 0;
		_nSize = 0;
	}
	~MemoryAlloc()
	{
		if (_pBuff)
			free(_pBuff);
		_pBuff = nullptr;
		_pHead = nullptr;
		_nBlockSize = 0;
		_nSize = 0;
	}
	//�����ڴ�
	void* allocMemory(size_t nSize)
	{
		if (!_pBuff)
		{
			initMemory();
		}
		MemoryBlock* pReturn = nullptr;
		if (!_pHead)	//�ڴ��û�п��п����
		{
			pReturn = (MemoryBlock*)malloc(nSize + sizeof(MemoryBlock));
			pReturn->bPool = false;
			pReturn->nID = -1;
			pReturn->nRef = 1;
			pReturn->pAlloc = nullptr;
			pReturn->pNext = nullptr;
		}
		else
		{
			pReturn = _pHead;
			_pHead = _pHead->pNext;
			assert(0 == pReturn->nRef);
			pReturn->nRef++;
		}
		printf("allocMem: %lx,id=%d, size=%d\n", pReturn, pReturn->nID, nSize);
		return ((char*)pReturn + sizeof(MemoryBlock));
	}
	//�ͷ��ڴ�
	void freeMem(void* pMem)
	{
		//ƫ��sizeof(MemoryBlock)  
		//��Ϊ�û��õ��ڴ��ַ�� �ڴ��ȥ��ͷ���Ĳ��֣����������Ҫ��ǰƫ��һ���ڴ��ͷ����С�ĵ�ַ
		MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		assert(1 == pBlock->nRef);
		if (--pBlock->nRef != 0)
		{
			return;
		}
		if (pBlock->bPool == true)	//	�ڳ���
		{
			pBlock->pNext = _pHead;
			_pHead = pBlock;
		}
		else  //�ڳ��⣬ϵͳ������ڴ�
		{
			free(pBlock);
			return;
		}
	}
	//��ʼ���ڴ��
	void initMemory()
	{
		assert(_pBuff == nullptr); //���ԣ�������������� �����˳�
		if (_pBuff)
		{
			return;
		}
		//Ϊ�ڴ����ϵͳ�����ڴ�
		size_t size = _nSize * (_nBlockSize + sizeof(MemoryBlock));
		_pBuff = (char*)malloc(size);
		//��ʼ���ڴ��
		_pHead = (MemoryBlock*)_pBuff;
		_pHead->nID = 0;
		_pHead->bPool = true;
		_pHead->nRef = 0;
		_pHead->pAlloc = this;
		_pHead->pNext = nullptr;
		//MemoryBlock* pTemp = _pHead;
		for (int i = 1; i < _nSize; i++)
		{
			MemoryBlock* pTemp = (MemoryBlock*)((char*)_pBuff + (sizeof(MemoryBlock) + _nBlockSize) * i);
			pTemp->bPool = true;
			pTemp->nID = i;
			pTemp->nRef = 0;
			pTemp->pAlloc = this;
			pTemp->pNext = nullptr;
			_pHead->pNext = pTemp;
			_pHead = pTemp;
		}
		_pHead = (MemoryBlock*)_pBuff;	//ͷ���ص����
	}
protected:
	MemoryBlock* _pHead;	//�ڴ��ͷ��
	size_t _nBlockSize;	//�ڴ��Ĵ�С
	size_t _nSize;	//�ڴ�������
	char* _pBuff;	//�ڴ���׵�ַ
};

template<size_t nBlockSize, size_t nSize>
class MemoryAllocator : public MemoryAlloc
{
public:
	MemoryAllocator()
	{
		size_t n = sizeof(void*);
		if (nBlockSize - (nBlockSize / n) * n == 0)
		{
			_nBlockSize = nBlockSize;
			_nSize = nSize;
		}
		else
		{
			_nBlockSize = (nBlockSize / n + 1) * n;
			_nSize = nSize;
		}
	}
};

//�ڴ����  ���
class MemoryBlock
{
public:
	MemoryBlock()
	{
		pAlloc = nullptr;
		pNext = nullptr;
	}
	~MemoryBlock()
	{

	}

public:
	//�ڴ����
	int nID;
	// ���ô���
	int nRef;
	//�����ڴ��
	MemoryAlloc* pAlloc;
	//��һ��λ��
	MemoryBlock* pNext;
	//�Ƿ����ڴ����
	bool bPool;
private:
	//Ԥ��
	char c1;
	char c2;
	char c3;
};

//�ڴ��������
class MemoryMgr
{
private:
	MemoryMgr()
	{
		init_map(0, 64, &_mem_pool_64);
		init_map(65, 128, &_mem_pool_128);
		init_map(129, 256, &_mem_pool_256);
		init_map(257, 512, &_mem_pool_512);
		init_map(513, 1024, &_mem_pool_1024);
	}
	~MemoryMgr()
	{

	}
public:
	static MemoryMgr& Instance()
	{
		static MemoryMgr mgr;
		return mgr;
	}
	//�����ڴ�
	void* allocMem(size_t nSize)
	{
		if (nSize > MAX_SIZE)
		{
			MemoryBlock* pReturn = (MemoryBlock*)malloc(nSize + sizeof(MemoryBlock));
			pReturn->bPool = false;
			pReturn->nID = -1;
			pReturn->nRef = 1;
			pReturn->pAlloc = nullptr;
			pReturn->pNext = nullptr;
			printf("allocMem: %lx,id=%d, size=%d\n", pReturn, pReturn->nID, nSize);
			return ((char*)pReturn + sizeof(MemoryBlock));
		}
		else
		{
			return _szAlloc[nSize]->allocMemory(nSize);
		}
		return nullptr;
	}
	//�ͷ��ڴ�
	void freeMem(void* pMem)
	{
		MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		printf("freeMem: %lx,id=%d\n", pBlock, pBlock->nID);
		if (pBlock->bPool == true)
		{
			pBlock->pAlloc->freeMem(pMem);
		}
		else
		{
			if (--pBlock->nRef == 0)
			{
				free(pBlock);
			}
		}
	}
	//�����ڴ�����ü���
	void addRef(void* pMem)
	{
		MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		pBlock->nRef++;
	}

private:
	void init_map(int nBegin, int nEnd, MemoryAlloc* pMem_pool)	//��ʼ���ڴ��ӳ������
	{
		for (int i = nBegin; i <= nEnd; i++)
		{
			_szAlloc[i] = pMem_pool;
		}
	}
private:
	MemoryAllocator<64, 100> _mem_pool_64;	//���������ʱ�򣬶������ݳ�Ա�ĸ�ֵ
	MemoryAllocator<128, 100> _mem_pool_128;
	MemoryAllocator<256, 100> _mem_pool_256;
	MemoryAllocator<512, 100> _mem_pool_512;
	MemoryAllocator<1024, 100> _mem_pool_1024;
	MemoryAlloc* _szAlloc[MAX_SIZE + 1];		//�ڴ�ص�ӳ������ �洢��ÿ���ֽڶ�Ӧ���ڴ��ָ��
};


