#pragma once


#define MAX_SIZE 50000


struct MsgToPut
{
	unsigned _wr_ptr;
	unsigned _rd_ptr;
	unsigned _length;
	char _base[1024];

	void reset()
	{
		this->_rd_ptr = this->_wr_ptr = 0;
		this->_length = 1024;
	}
};

ObjectPool<MsgToPut> MsgPool;

void* newthread(void* argv)
{
	long long int start = get_os_system_time();

	for (int i = 0; i < MAX_SIZE; i++)
	{
		MsgToPut* msg;
		MsgPool.pop(msg);
		if (msg == NULL)
		{
			printf("error\n");
		}
	}

	long long int end = get_os_system_time();

	printf("newthread ObjectPool:%d\n", end - start);


	MsgToPut* mtp[MAX_SIZE];

	for (int i = 0; i < MAX_SIZE; i++)
	{
		mtp[i] = (MsgToPut*)tc_malloc(sizeof(MsgToPut));
		mtp[i]->reset();
	}

	start = get_os_system_time();
	printf("newthread tc malloc :%d\n", start - end);

	return (void*)0;
}

int main()
{

	pthread_t pid;
	pthread_create(&pid, NULL, newthread, NULL);
	pthread_create(&pid, NULL, newthread, NULL);
	pthread_create(&pid, NULL, newthread, NULL);

	long long int start = get_os_system_time();

	for (int i = 0; i < MAX_SIZE; i++)
	{
		MsgToPut* msg = NULL;
		MsgPool.pop(msg);
		if (msg == NULL)
		{
			printf("error\n");
		}
	}

	long long int end = get_os_system_time();

	printf("main ObjectPool:%d\n", end - start);


	MsgToPut* mtp[MAX_SIZE];

	for (int i = 0; i < MAX_SIZE; i++)
	{
		mtp[i] = (MsgToPut*)tc_malloc(sizeof(MsgToPut));
		mtp[i]->reset();
	}

	start = get_os_system_time();
	printf("main tc malloc :%d\n", start - end);

	return 0;
}

