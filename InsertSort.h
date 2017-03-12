#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
using namespace std;
//直接插入排序，升序
//1保存当前元素 2比较元素，找到插入的位置，搬移元素 3插入元素 
void InsertSort(int arr[],size_t size)
{
	for (size_t idx = 1; idx < size; ++idx)
	{
		int temp = arr[idx];
		size_t pos = idx - 1;
		while (pos >=0 && arr[pos] > temp)
		{
			//搬移,从后向前搬移
			arr[pos + 1] = arr[pos];
			--pos;
		}
		arr[pos + 1] = temp; 
	}
}
//用二分查找优化插入查找
//在查找元素时 用二分查找来优化[]
void InsertSort_P(int arr[],size_t size)
{
	for (size_t idx = 1; idx < size; ++idx)
	{
		int temp = arr[idx];		
		int left = 0;
		int right = idx -1;
		int mid = 0;
		//查找插入的位置
		while (left <= right)
		{
			mid = left + ((right - left) >> 1);
			if (temp < arr[mid]) //相等的话，插入其后面
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;			
			}
		}
		//跳出循环，left为插入的位置
		size_t pos = left;
		for (size_t index = idx -1; index >= pos ; --index)
		{
			arr[index + 1] = arr[index];
			if (index == 0)
				break;
		}
		arr[pos] = temp;
	}
}

//希尔排序
void ShellSort(int arr[],size_t size)
{
	int gsp = size;
	while (gsp > 1)
	{
		gsp = gsp / 3 + 1;
		for (size_t idx = gsp; idx < size; ++idx)
		{
			int temp = arr[idx];
			int pos = idx - gsp;
			while (pos >= 0 && arr[pos] > temp)
			{
				//搬移,从后向前搬移
				arr[pos + gsp] = arr[pos];
				pos = pos - gsp;
			}
			arr[pos + gsp] = temp;
		}
		
	}
}
