#pragma once
#include <array>
#include <iostream>
#include <vector>
#include <stack>  // ʹ��ջstack
using namespace std;

class SortAlgorithm
{
	// ð������
	void bubbleSort(vector<int>& array) {
		for (size_t i = 0; i < array.size(); i++) {
			// ��ǰ���Ƿ����������¼���־λ����δ����������������б�������
			bool isExchanged = false;
			for (size_t j = 0; j < array.size() - i - 1; j++) {
				if (array[j] > array[j + 1]) {
					int temp = array[j];
					array[j] = array[j + 1];
					array[j + 1] = temp;
					isExchanged = true;
				}
			}
			if (!isExchanged) {
				break;
			}
		}
	}

	// ѡ������
	void selectSort(vector<int>& array) {
		for (size_t i = 0; i < array.size(); i++) {
			size_t minIndex = i;
			for (size_t j = i + 1; j < array.size(); j++) {
				if (array[minIndex] > array[j]) {
					minIndex = j;
				}
			}
			if (minIndex != i) {
				swap(array[i], array[minIndex]);
			}
		}
	}

	// ��������
	void insertionSort(vector<int>& array) {
		// i ��������������Ԫ�أ���������ǰΪ�������У�
		size_t i = 1;
		while (i < array.size()) {
			size_t j = i - 1;
			int itermToInsert = array[i];
			while (j >= 0) {
				if (array[j] >= itermToInsert) {
					array[j + 1] = array[j];
					j--;
				}
				else {
					break;
				}
			}
			array[j + 1] = itermToInsert;
			i++;
		}
	}

	// ϣ������
	void shellSort(vector<int>& array) {
		int n = array.size();
		for (int gap = n / 2; gap >= 1; gap /= 2) {
			for (int i = gap; i < n; i++) {
				// ʹ�ò��������㷨����Ԫ�����β�������С����������б���
				// ������Ԫ��
				int itermToInsert = array[i];
				int j = i - gap;
				while (j >= 0 && array[j] >= itermToInsert) {
					array[j + gap] = array[j];
					j -= gap;
				}
				array[j + gap] = itermToInsert;
			}
		}
	}


	// �鲢����,
// �ϲ����������У������зֱ�Ϊarray��0��mid���ֺ�mid+1��ĩβ���֡�
	void merge(vector<int>& array, vector<int>& copyArray, int left, int right) {
		int mid = (left + right) / 2;
		int i = left, j = mid + 1, k = 0;
		while (i <= mid || j <= right) {
			if (i > mid) {
				copyArray[k] = array[j];
				j++;
			}
			else if (j > right) {
				copyArray[k] = array[i];
				i++;
			}
			else if (array[i] > array[j]) {
				copyArray[k] = array[j];
				j++;
			}
			else {
				copyArray[k] = array[i];
				i++;
			}

			k++;
		}

		for (size_t i = left; i <= right; i++) {
			array[i] = copyArray[i - left];
		}

	}
	void mergeSortHelp(vector<int>& array, vector<int>& copyArray, int left, int right) {
		if (left < right) {
			int mid = (left + right) / 2;
			mergeSortHelp(array, copyArray, left, mid);
			mergeSortHelp(array, copyArray, mid + 1, right);
			merge(array, copyArray, left, right);
		}
	}
	// �鲢���� �ݹ�ʵ��
	void mergeSort(vector<int>& array) {
		vector<int> copyArray(array);
		mergeSortHelp(array, copyArray, 0, array.size() - 1);
	}

	// �鲢���� ����ʵ��
	void mergeSortIteration(vector<int>& array) {
		vector<int> copyArray(array);
		int left = 0, right = array.size() - 1;
		stack<vector<int>> boundaries;
		while (left < right || !boundaries.empty()) {
			if (left < right) {
				boundaries.push({ left, right });
				right = (left + right) / 2;
			}
			else {
				vector<int> boundary = boundaries.top();
				boundaries.pop();
				left = boundary[0];
				right = boundary[1];
				merge(array, copyArray, left, right);

				if (boundaries.empty()) {
					break;
				}
				boundary = boundaries.top();
				left = right + 1;
				right = boundary[1];
			}
		}
	}

	
	// �������򣨵ݹ飩
// ѡ������ˡ����Ҷ˺��м�λ��3Ԫ�ص���ֵ��Ϊ��׼ֵ������3Ԫ�����򣬷��ػ�׼ֵ
	int medianPovit(vector<int>& array, int left, int mid, int right) {
		if (array[left] > array[mid]) {
			swap(array[mid], array[left]);
		}
		if (array[left] > array[right]) {
			swap(array[left], array[right]);
		}
		if (array[mid] > array[right]) {
			swap(array[mid], array[right]);
		}
		return array[mid];
	}
	// ����,���ػ�׼����
	int partition(vector<int>& array, int left, int right) {
		// �м�λ������
		int mid = (left + right) / 2;
		// ��׼ֵ����ʱ��׼ֵ��Ӧ����Ϊmid��
		int povit = medianPovit(array, left, mid, right);
		// ����׼ֵ�뵹���ڶ���Ԫ�ؽ���
		array[mid] = array[right - 1];
		array[right - 1] = povit;

		int i = left, j = right - 1;
		while (i < j) {
			if (array[i] < povit) {
				i++;
			}
			else if (array[j] >= povit) {
				j--;
			}
			else {
				swap(array[i], array[j]);
			}
		}
		// ������׼ֵ��iλ��Ԫ��
		swap(array[i], array[right - 1]);
		return i;
	}
	void quickSortHelp(vector<int>& array, int left, int right) {
		if (left < right) {
			int pivotLoction = partition(array, left, right);
			quickSortHelp(array, left, pivotLoction - 1);
			quickSortHelp(array, pivotLoction + 1, right);
		}
	}
	// ��������
	void quickSort(vector<int>& array) {
		quickSortHelp(array, 0, array.size() - 1);
	}

	// �������� �ǵݹ�(������)
	void quickSortIteration(vector<int>& array) {
		stack<vector<int>> boundaries;
		int left = 0, right = array.size() - 1;
		while (left < right || !boundaries.empty()) {
			if (left >= right) {
				vector<int> boundary = boundaries.top();
				boundaries.pop();
				left = boundary[0];
				right = boundary[1];
			}
			int pivotLoction = partition(array, left, right);
			if (pivotLoction + 1 < right) {
				boundaries.push({ pivotLoction + 1, right });
			}
			right = pivotLoction - 1;
		}
	}

	// ������
// �����ѣ���Ԫ�����������ƶ���ֱ�������λ�ã�first��last�ֱ�Ϊ�Ѷ��Ͷѵ�������array�е�����
	void moveDown(vector<int>& array, int first, int last) {
		// first�����ӽڵ�����
		int curIndex = first * 2 + 1;
		while (curIndex <= last) {
			// ��first��2�ӽڵ㣬��curIndexΪ��ֵ����ӽڵ�����
			if (curIndex < last && array[curIndex] < array[curIndex + 1]) {
				curIndex++;
			}
			// �����ڵ�ֵС���ӽڵ�ֵ���򽻻�
			if (array[first] < array[curIndex]) {
				swap(array[first], array[curIndex]);
				first = curIndex;
				curIndex = first * 2 + 1;
			}
			else {
				break;
			}
		}
	}
	// ������ʵ�ֶ�
	void buildHeap(vector<int>& array) {
		// ���һ����Ҷ�ڵ�Ľڵ�����
		int i = array.size() / 2 - 1;
		while (i >= 0) {
			moveDown(array, i, array.size() - 1);
			i--;
		}
	}
	// ������
	void heapSort(vector<int>& array) {
		// ���ɶ�
		buildHeap(array);
		// �Ѷ���������
		int first = 0, last = array.size() - 1;
		while (first <= last) {
			swap(array[first], array[last]);
			last--;
			moveDown(array, first, last);
		}
	}

	// ��������
	void countSort(vector<int>& array) {
		if (array.empty()) {
			return;
		}
		//�ҳ������Сֵ
		int min = array.front(), max = array.front();
		for (int i = 1; i < array.size(); i++) {
			if (min > array[i]) {
				min = array[i];
			}
			else if (max < array[i]) {
				max = array[i];
			}
		}

		// ��¼��Ԫ�س��ִ���
		vector<int> counts(max - min + 1);
		for (int i = 0; i < array.size(); i++) {
			counts[array[i] - min]++;
		}

		// ���ݼ�¼�Ĵ��������ӦԪ��
		int index = 0;
		for (int j = 0; j < counts.size(); j++) {
			int n = counts[j];
			while (n--) {
				array[index] = j + min;
				index++;
			}
		}
	}


	// Ͱ����
	void bucketSort(vector<int>& array, int bucketCount) {
		if (array.empty()) {
			return;
		}
		// �ҳ������Сֵ
		int max = array.front(), min = array.front();
		for (int i = 1; i < array.size(); i++) {
			if (min > array[i]) {
				min = array[i];
			}
			else if (max < array[i]) {
				max = array[i];
			}
		}

		// ��������ĸ�Ԫ�ط����ӦͰ��
		vector<vector<int>> buckets(bucketCount);
		int bucketSize = ceil((double)(max - min + 1) / bucketCount);
		for (int i = 0; i < array.size(); i++) {
			int bucketIndex = (array[i] - min) / bucketSize;
			buckets[bucketIndex].push_back(array[i]);
		}
		// �Ը�Ͱ��Ԫ�ؽ���ѡ������
		int index = 0;
		for (vector<int> bucket : buckets) {
			if (!bucket.empty()) {
				// ʹ��ѡ�������㷨��Ͱ��Ԫ�ؽ�������
				selectSort(bucket);
				for (int value : bucket) {
					array[index] = value;
					index++;
				}
			}
		}

	}
	// Ͱ����
	void bucketSort(vector<int>& array) {
		bucketSort(array, array.size() / 2);
	}

	// �������� ��ֻ�������������˴������ã�
	void radixSort(vector<int>& array) {
		// ��ǰλ��
		int curdigit = 10;
		// ��ǰλ�Ƿ��ѳ������Ϊ
		bool isOverHighest = false;
		while (!isOverHighest) {
			isOverHighest = true;
			// ���÷�Ͱ��˼����ʵ�ְ���λ��������
			vector<vector<int>> buckets(10);
			for (int curVal : array) {
				int bucketIndex = curVal % curdigit - curVal % (curdigit / 10);
				buckets[bucketIndex].push_back(curVal);
				if (isOverHighest && curVal / curdigit) {
					isOverHighest = false;
				}
			}
			// ����Ͱ��˳�򣬽���Ͱ��Ԫ��ƴ������
			int index = 0;
			for (vector<int> bucket : buckets) {
				for (int value : bucket) {
					array[index] = value;
					index++;
				}
			}
			curdigit *= 10;
		}
	}
};
