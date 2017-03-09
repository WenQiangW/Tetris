#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>
template<class T>
class Less
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left <= right;
	}
};
template<class T>
class Greater
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left >= right;
	}
};
template<class T,template<class> class Compare = Less> //模板的模板参数
class Heap
{
public:
	Heap()
	{}
	Heap(const T arr[], size_t size)
	{
		//把arr的数据保存到 _heap中
		//_heap.resize(size);
		for (size_t idx = 0; idx < size; ++idx)
		{
			//_heap[idx] = arr[idx];
			_heap.push_back(arr[idx]);
		}

		// 找到最后一个非叶子结点
		size_t root = (size - 2) / 2;
		for (int idx = root; idx >= 0; idx--)
		{
			_AdjustDown(idx, size);//调整堆
		}
	}
	void Insert(const T data)
		// 空 非空
	{
		_heap.push_back(data);
		size_t size = Size();
		if (size > 1)
		{
			_AdJustUp(size);
		}
	}
	void Remove() //把顶端的和最后一位互换，然后删除
	{
		assert(!Empty());
		size_t size = _heap.size();
		if (size > 1)
		{
			std::swap(_heap[0], _heap[size - 1]);
			_heap.pop_back();
			_AdjustDown(0, size - 1);
		}
		else
		{
			_heap.pop_back();
		}
	}
	bool Empty() const
	{
		return _heap.empty();
	}
	size_t Size()
	{
		return _heap.size();
	}
	T& Top()
	{
		return _heap[0];
	}
	~Heap()
	{}

private:
	// 调整新堆
	void _AdjustDown(size_t root, size_t size) //参数：根节点的下标，堆的大小
	{
		size_t parent = root;
		size_t child = (parent * 2) + 1; // 默认最小孩子为左孩子
		while (child < size)
		{
			//找到最小的孩子结点,判断child+1是否越界

			if (child + 1 < size && Compare<T>()(_heap[child + 1], _heap[child]))
				//if (child +1 < size && _heap[child + 1] < _heap[child])
			{
				child = child + 1;
			}
			//比较孩子和双亲结点
			if (Compare<T>()(_heap[child], _heap[parent]))
				//if (_heap[child] < _heap[parent])
			{
				std::swap(_heap[child], _heap[parent]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdJustUp(size_t size) // 插入 向上调整堆
	{
		size_t parent = (size - 2) / 2;
		size_t child = size - 1;
		while (child != 0)
		{
			if (Compare<T>()(_heap[child], _heap[parent]))
				//if (_heap[child] < _heap[parent])
			{
				std::swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

private:
	std::vector<T> _heap;
};


/*
template<class T,class Compare = Less<T>> //模板参数
class Heap
{
public:
Heap()
{}
Heap(const T arr[], size_t size)
{
//把arr的数据保存到 _heap中
//_heap.resize(size);
for (size_t idx = 0; idx < size; ++idx)
{
//_heap[idx] = arr[idx];
_heap.push_back(arr[idx]);
}

// 找到最后一个非叶子结点
size_t root = (size - 2) / 2;
for (int idx = root; idx >= 0; idx--)
{
_AdjustDown(idx, size);//调整堆
}
}
void Insert(const T data)
// 空 非空
{
_heap.push_back(data);
size_t size = Size();
if (size > 1)
{
_AdJustUp(size);
}
}
void Remove() //把顶端的和最后一位互换，然后删除
{
assert(!Empty());
size_t size = _heap.size();
if (size > 1)
{
std::swap(_heap[0], _heap[size - 1]);
_heap.pop_back();
_AdjustDown(0, size - 1);
}
else
{
_heap.pop_back();
}
}
bool Empty() const
{
return _heap.empty();
}
size_t Size()
{
return _heap.size();
}
~Heap()
{}

private:
// 调整新堆
void _AdjustDown(size_t root,size_t size) //参数：根节点的下标，堆的大小
{
size_t parent = root;
size_t child = (parent * 2) + 1; // 默认最小孩子为左孩子
while (child < size)
{
//找到最小的孩子结点,判断child+1是否越界

if (child + 1 < size && Compare()(_heap[child +1], _heap[child]))
//if (child +1 < size && _heap[child + 1] < _heap[child])
{
child = child + 1;
}
//比较孩子和双亲结点
if (Compare()(_heap[child] , _heap[parent]))
//if (_heap[child] < _heap[parent])
{
std::swap(_heap[child] ,_heap[parent]);
parent = child;
child = child * 2 + 1;
}
else
{
break;
}
}
}
void _AdJustUp(size_t size) // 插入 向上调整堆
{
size_t parent = (size - 2) / 2;
size_t child = size - 1;
while (child != 0)
{
if (Compare()(_heap[child], _heap[parent]))
//if (_heap[child] < _heap[parent])
{
std::swap(_heap[child], _heap[parent]);
child = parent;
parent = (child - 1) / 2;
}
else
break;
}
}

private:
std::vector<T> _heap;
};
*/