#include<iostream>

//冒泡排序：两两比较，把最大(最小)值放到末尾
void BubbleSort(int arr[],size_t size)
{
	for (size_t i = 0; i < size;++i) //控制排序次数
	{
		for (size_t j = 0; j < size - i - 1; ++j) //两两比较，注意数组越界
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j],arr[j+1]);
			}
		}
	}
}
//冒泡排序优化，定义一个标志器，
void BubbleSort_P(int arr[], size_t size)
{
	bool flag = true;
	for (size_t i = 0; i < size; ++i) //控制排序次数
	{
		for (size_t j = 0; j < size - i - 1; ++j) //两两比较，注意数组越界
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				flag = false;
			}
		}
		if (flag)
			break;
	}
}


//快速排序  不稳定排序
// 分治法：找一个key值，大于key的放在key之后，小于放在key之前	    
//		 key为数组最后一位,begin从前找大于key的，end从后找小于key，然后交换
//一次快速排序
int Partition(int arr[], int begin, int end)//[]闭区间
{
	int key = arr[begin]; //标记最左边，先从最右边开始找
	while (begin < end)
	{
		while (begin < end && arr[end] > key)
			end--;
		if (begin < end)
		{
			arr[begin] = arr[end];
			begin++;
		}
		while (begin < end && arr[begin] < key)
			begin++;
		if (begin < end)
		{
			arr[end] = arr[begin];
			end--;
		}			
	}
	arr[begin] = key;
	return begin;
	
}
void QuickSort(int arr[],int left,int right)
{
	if (left < right)
	{
		int key = Partition(arr, left, right);
		QuickSort(arr, left, key - 1);
		QuickSort(arr, key + 1,right);
	}
}