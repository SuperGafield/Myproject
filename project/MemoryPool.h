#pragma once
#include "Complex.h"
#include <assert.h>

#define MAX_SIZE 50000
//内存池类
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
	//申请内存
	void* allocMemory(size_t nSize)
	{
		if (!_pBuff)
		{
			initMemory();
		}
		MemoryBlock* pReturn = nullptr;
		if (!_pHead)	//内存池没有空闲块可用
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
	//释放内存
	void freeMem(void* pMem)
	{
		//偏移sizeof(MemoryBlock)  
		//因为用户用的内存地址是 内存块去掉头部的部分，因此这里需要向前偏移一个内存块头部大小的地址
		MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		assert(1 == pBlock->nRef);
		if (--pBlock->nRef != 0)
		{
			return;
		}
		if (pBlock->bPool == true)	//	在池内
		{
			pBlock->pNext = _pHead;
			_pHead = pBlock;
		}
		else  //在池外，系统申请的内存
		{
			free(pBlock);
			return;
		}
	}
	//初始化内存池
	void initMemory()
	{
		assert(_pBuff == nullptr); //断言，如果不满足条件 程序退出
		if (_pBuff)
		{
			return;
		}
		//为内存池向系统申请内存
		size_t size = _nSize * (_nBlockSize + sizeof(MemoryBlock));
		_pBuff = (char*)malloc(size);
		//初始化内存池
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
		_pHead = (MemoryBlock*)_pBuff;	//头部回到最初
	}
protected:
	MemoryBlock* _pHead;	//内存块头部
	size_t _nBlockSize;	//内存块的大小
	size_t _nSize;	//内存块的数量
	char* _pBuff;	//内存池首地址
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

//内存块类  结点
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
	//内存块编号
	int nID;
	// 引用次数
	int nRef;
	//所属内存池
	MemoryAlloc* pAlloc;
	//下一块位置
	MemoryBlock* pNext;
	//是否在内存池中
	bool bPool;
private:
	//预留
	char c1;
	char c2;
	char c3;
};

//内存管理工具类
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
	//申请内存
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
	//释放内存
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
	//增加内存块引用计数
	void addRef(void* pMem)
	{
		MemoryBlock* pBlock = (MemoryBlock*)((char*)pMem - sizeof(MemoryBlock));
		pBlock->nRef++;
	}

private:
	void init_map(int nBegin, int nEnd, MemoryAlloc* pMem_pool)	//初始化内存池映射数组
	{
		for (int i = nBegin; i <= nEnd; i++)
		{
			_szAlloc[i] = pMem_pool;
		}
	}
private:
	MemoryAllocator<64, 100> _mem_pool_64;	//声明对象的时候，对于数据成员的赋值
	MemoryAllocator<128, 100> _mem_pool_128;
	MemoryAllocator<256, 100> _mem_pool_256;
	MemoryAllocator<512, 100> _mem_pool_512;
	MemoryAllocator<1024, 100> _mem_pool_1024;
	MemoryAlloc* _szAlloc[MAX_SIZE + 1];		//内存池的映射数组 存储了每个字节对应的内存池指针
};


