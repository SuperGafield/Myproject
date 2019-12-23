#pragma once

//DynamicArray.h
template<typename T>
class DynamicArray : public Arrayq<T>
{
protected:
	int m_length;

public:
	DynamicArray(int length)
	{
		this->m_array = new T[length];
		if (this->m_array)
		{
			this->m_length = length;
		}
		else
		{
			throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
		}
	}

	DynamicArray(const DynamicArray<T>& obj)     //ʵ�������Ŀ���
	{
		this->m_array = new T[obj.m_length];
		if (this->m_array)
		{
			this->m_length = obj.m_length;
			for (int i = 0; i < obj.m_length; i++)
				this->m_array[i] = obj.m_array[i];
		}
		else
			throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
	}

	DynamicArray<T>& operator=(const DynamicArray<T>& obj)   //ʵ�������Ŀ���
	{
		if (this != &obj)
		{
			T* array = new T[obj.m_length];
			if (array)
			{
				for (int i = 0; i < obj.m_length; i++)
				{
					array[i] = obj.m_array[i];
				}

				//ע���쳣��ȫ
				T* tmp = this->m_array;
				this->m_array = array;
				this->m_length = obj.m_length;

				delete[] tmp;
			}
			else
				throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
		}

		return *this;
	}

	int length() const { return m_length; }

	void resize(int length)     /* ��������ռ�ݵ��ڴ�ռ� */
	{
		if (this->m_length != length)
		{
			T* array = new T[length];
			if (array)
			{
				int sz = (length > this->m_length) ? this->m_length : length;
				for (int i = 0; i < sz; i++)
					array[i] = this->m_array[i];

				//ע���쳣��ȫ
				T* tmp = this->m_array;
				this->m_array = array;
				this->m_length = length;
				delete[] tmp;
			}
			else
				throw(std::out_of_range("DynamicArray::resize out of range"));
		}
	}

	~DynamicArray() { delete[] this->m_array; }
};

template<typename T>
class DynamicArray : public Arrayq<T>
{
protected:
	int m_length;

public:
	DynamicArray(int length)
	{
		this->m_array = new T[length];
		if (this->m_array)
		{
			this->m_length = length;
		}
		else
		{
			throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
		}
	}

	DynamicArray(const DynamicArray<T>& obj)     //ʵ�������Ŀ���
	{
		this->m_array = new T[obj.m_length];
		if (this->m_array)
		{
			this->m_length = obj.m_length;
			for (int i = 0; i < obj.m_length; i++)
				this->m_array[i] = obj.m_array[i];
		}
		else
			throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
	}

	DynamicArray<T>& operator=(const DynamicArray<T>& obj)   //ʵ�������Ŀ���
	{
		if (this != &obj)
		{
			T* array = new T[obj.m_length];
			if (array)
			{
				for (int i = 0; i < obj.m_length; i++)
				{
					array[i] = obj.m_array[i];
				}

				//ע���쳣��ȫ
				T* tmp = this->m_array;
				this->m_array = array;
				this->m_length = obj.m_length;

				delete[] tmp;
			}
			else
				throw(std::out_of_range("DynamicArray::DynamicArray out of range"));
		}
		return *this;
	}

	int length() const { return m_length; }
	void resize(int length)     /* ��������ռ�ݵ��ڴ�ռ� */
	{
		if (this->m_length != length)
		{
			T* array = new T[length];
			if (array)
			{
				int sz = (length > this->m_length) ? this->m_length : length;
				for (int i = 0; i < sz; i++)
					array[i] = this->m_array[i];

				//ע���쳣��ȫ
				T* tmp = this->m_array;
				this->m_array = array;
				this->m_length = length;
				delete[] tmp;
			}
			else
				throw(std::out_of_range("DynamicArray::resize out of range"));
		}
	}

	~DynamicArray() { delete[] this->m_array; }
};


