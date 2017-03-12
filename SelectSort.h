#include<iostream>

//直接选择排序：找到最大值（最小值） 放到最后一个
//不稳定的
void SelectionSort(int arr[],size_t size)
{
	for (size_t idx = 0; idx < size -1; ++idx) //控制趟树 ,少一次趟树，最后一趟 就一个元素
	{
		int maxpos = 0;
		int find = arr[maxpos];
		for (size_t i = 1; i < size - idx; ++i) //找最大值或最小值
		{			
			if (arr[i] > find)
			{
				find = arr[i];
				maxpos = i;
			}
		}
		if (maxpos != (size - idx - 1)) //判断是不是位置正好 就不用交换
			std::swap(arr[maxpos],arr[size - idx -1]);
	}
}


//找到最小（升序）或最大（降序） 放到开始位置
void SelectionSort2(int arr[],size_t size) //升序,找最小值放到前面
{
	for (size_t i = 0; i < size - 1; ++i) //少一次趟数
	{
		int pos = i; //标记最大或最小值
		for (size_t j = i + 1; j < size; ++j)
		{
			if (arr[pos] > arr[j])
			{
				pos = j;
			}
		}
		if (i != pos)
			std::swap(arr[i],arr[pos]);
	}
}
// 优化版本，同时找，找到最小值和最大值，放到起始和末尾
void SelectionSort_P(int arr[],size_t size)
{
	int left = 0;
	int right = size - 1;
	int max = left;
	int min = right;
	while (left < right)
	{
		max = left;
		min = right;
		for (int i = left; i <= right;++ i)
		{
			if (arr[max] < arr[i])
				max = i;
			if (arr[min] > arr[i])
				min = i;
		}
//有两种特殊情况：1 最大值-> left  && 最大值 right ,注意交换了两次
//			      2 最大值-> left || 最小值 right,注意交换后位置可能改变了
// 处理这两种情况：先把最小值交换到最左边，如果最左边是最大值的话，就把最小值赋值给最大值(因为最小值和left交换了)
//					
		std::swap(arr[left], arr[min]);
		if (left == max)
			max = min;
		std::swap(arr[max], arr[right]);
		left++;
		right--;
	}
}

//堆排序: 升序-> 大堆 降序->小堆
// 升序 1创建堆
//		2把堆顶 与最后一位交换位置，调整堆
void HeapAdjust(int arr[], int root, size_t size) //从根节点向下调整
{
	size_t parent = root;
	size_t child = 2 * parent + 1; //默认孩子最小值为左孩子,右孩子可能不存在
	while (child < size)//根节点改变，可能左子树或右子树不满足堆
	{
		//找最大的孩子
		if (child + 1 < size && arr[child] < arr[child + 1])
		{
			child = child + 1;
		}

		if (arr[parent] < arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}
void HeapSort(int arr[],size_t size) //升序
{
	//1创建堆，从最后一个非叶子节点开始调整
	int idx = (size - 2) >> 1;
	while (idx >= 0)
	{
		HeapAdjust(arr,idx,size);
		idx--;
	}
	// 堆顶和最后一个交换
	int last = size;
	while (last > 1) //最后剩余一个元素，不用交换
	{
		std::swap(arr[0], arr[last -1]);
		last--;
		HeapAdjust(arr,0,last);
	}
}