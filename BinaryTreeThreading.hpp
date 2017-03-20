#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

enum Info
{
	LINK,
	THREAD
};
template<class T>
struct BinaryTreeNodeThd
{
	BinaryTreeNodeThd(const T& data)
	: _data(data)
	, _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _LeftThread(LINK)
	, _RightThread(LINK)
	{}
	T _data;
	BinaryTreeNodeThd<T>* _pLeft;
	BinaryTreeNodeThd<T>* _pRight;
	BinaryTreeNodeThd<T>* _pParent;
	Info _LeftThread;
	Info _RightThread;
};

template<class T>
class BinaryTreeThd
{
public:
	BinaryTreeThd()
		:_pRoot(NULL)
	{
	}
	BinaryTreeThd(T array[], size_t size)
		:_pRoot(NULL)
	{
		size_t index = 0;
		_CreatBinaryTree(_pRoot, array, size, index);
	}
	//前序线索化
	void PreThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_preThread(_pRoot, prev);
	}
	void PreOrder()
	{
		_PreOrder(_pRoot);
	}
	//中序线索化
	void InThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_InThread(_pRoot, prev);
	}
	void InOrder()
	{
		_InOrder(_pRoot);
	}

	//后序
	void PostThread()
	{
		BinaryTreeNodeThd<T>* prev = NULL;
		_PostThread(_pRoot, prev);
	}
	void PostOrder()
	{
		_PostOrder(_pRoot);
	}

private:
	//          0
	//      1      2
	//    3   4   5
	//     6
	void _CreatBinaryTree(BinaryTreeNodeThd<T>*& pRoot, T array[], size_t size, size_t& index)
	{
		if (index < size && '#' != array[index])
		{
			pRoot = new BinaryTreeNodeThd<T>(array[index]);
			_CreatBinaryTree(pRoot->_pLeft, array, size, ++index);
			if (pRoot->_pLeft)
				pRoot->_pLeft->_pParent = pRoot;
			_CreatBinaryTree(pRoot->_pRight, array, size, ++index);
			if (pRoot->_pRight)
				pRoot->_pRight->_pParent = pRoot;
		}
	}

	void _preThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			//线索化当前节点的左指针域
			if (NULL == pRoot->_pLeft)
			{
				pRoot->_pLeft = prev;
				pRoot->_LeftThread = THREAD;
			}
			//线索化当前节点的前继节点的右指针域
			if (prev && NULL == prev->_pRight)
			{
				prev->_pRight = pRoot;
				prev->_RightThread = THREAD;
			}
			prev = pRoot;
			if (LINK == pRoot->_LeftThread)
				_preThread(pRoot->_pLeft, prev);
			if (LINK == pRoot->_RightThread)
				_preThread(pRoot->_pRight, prev);
		}

	}
	void _PreOrder(BinaryTreeNodeThd<T>* pRoot) //前序遍历 0136425
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;

		while (pCur) //外层循环
		{
			// 找到最左边的节点
			while (LINK == pCur->_LeftThread)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			//此时pCur为最左边的节点还没有访问
			cout << pCur->_data << " ";

			//处理右孩子
			pCur = pCur->_pRight;
			/*
			while (THREAD == pCur->_RightThread) //处理3的右子树
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			if (LINK == pCur->_LeftThread)   //处理4的左子树
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			else
			{
				pCur = pCur->_pRight;
			}*/
		}
		cout << endl;
	}

	void _InThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			_InThread(pRoot->_pLeft, prev);

			if (NULL == pRoot->_pLeft)
			{
				pRoot->_pLeft = prev;
				pRoot->_LeftThread = THREAD;

			}
			if (prev && NULL == prev->_pRight)
			{
				prev->_pRight = pRoot;
				prev->_RightThread = THREAD;
			}

			prev = pRoot;
			if (LINK == pRoot->_RightThread)
				_InThread(pRoot->_pRight, prev);
		}
	}
	void _InOrder(BinaryTreeNodeThd<T>* pRoot) //3614052
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;
		while (pCur)
		{
			//找到最左边的节点
			while (LINK == pCur->_LeftThread)
			{
				pCur = pCur->_pLeft;
			}
			//访问当前节点
			cout << pCur->_data << " ";

			//访问当前节点的后继
			while (pCur && pCur->_RightThread == THREAD) //注意左单支 pCur为空
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			//没有后继，有右子树
			if (pCur)
			{
				pCur = pCur->_pRight;
			}
		}
	}

	void _PostThread(BinaryTreeNodeThd<T>* pRoot, BinaryTreeNodeThd<T>*& prev)
	{
		if (pRoot)
		{
			_PostThread(pRoot->_pLeft,prev);
			_PostThread(pRoot->_pRight,prev);

			if (pRoot->_pLeft == NULL)
			{
				pRoot->_LeftThread = THREAD;
				pRoot->_pLeft = prev;
			}
			
			if (prev && prev->_pRight == NULL)
			{
				prev->_RightThread = THREAD;
				prev->_pRight = pRoot;
			}
			prev = pRoot;
		}
	}
	void _PostOrder(BinaryTreeNodeThd<T>* pRoot) //6341520
		/* 思路：1：先找到最左边的节点
				 2：然后遍历节点的后继(注意左单支的情况)
				 3：当遍历到没有后继时 判断是否到达根节点：到达根节点（如果根节点没有右子树，访问根节点 return；）
				 4：				   没有到达根节点：找当前节点的双亲节点，
				 5：一直找到根节点，继续判断根节点是否有右子树，
		*/
	{
		BinaryTreeNodeThd<T>* pCur = pRoot;
		BinaryTreeNodeThd<T>* prev = NULL;
		while (pCur)
		{
			//找最左边的节点
			while (pCur->_LeftThread == LINK && pCur->_pLeft != prev) //防止陷入死循环  
			{
				pCur = pCur->_pLeft;
			} //跳出循环的条件：pCur为最左边的节点
			
			//访问节点的后继
			while (pCur && THREAD == pCur->_RightThread) // 左单支的情况：所以判断pCur是否为空
			{
				cout << pCur->_data << " ";
				prev = pCur; //perv记录已经访问过的节点
				pCur = pCur->_pRight;
			}//跳出循环的条件：pCur为空（即左单支情况）或者节点有右子树或者节点为根节点

			//跳出循环，判断是否为根节点
			if (pCur == pRoot && pCur->_pRight == prev)
			{
				cout << pCur->_data << " ";
				return;
			}
			//不是根节点，访问当前节点的双亲节点
			while (pCur && pCur->_pRight == prev) // 注意 右单支情况此时pCur == pRoot
			{
				cout << pCur->_data << " ";
				prev = pCur;
				pCur = pCur->_pParent;
			}

			// 判断根节点是否有右子树
			if (pCur && pCur->_RightThread == LINK )
			{
				if (pCur->_pRight == NULL) //解决根结点没有右孩子，没有线索化为LINK，且为NULL
					cout << pCur->_data << " ";
				pCur = pCur->_pRight;
			}
		}
	}
private:
	BinaryTreeNodeThd<T>* _pRoot;
};

void FunTest()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTreeThd<char> bt(pTreeInfo,strlen(pTreeInfo));
	bt.PreThread();
}

void FunTest1()
{
	char* pTreeInfo = "013#6##4##25";
	BinaryTreeThd<char> bt(pTreeInfo,strlen(pTreeInfo));
	//bt.InThread();
	bt.PreThread();
	bt.PreOrder();
	bt.PostThread();
	bt.PostOrder();
}

void FunTest2() //判断第一个循环的防止陷入死循环的
{
	char* pTreeInfo = "1245##6#7###3";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest3() // 右单支 ：判断是否为根的情况下加的条件： pCur->_pRight == prev
{
	char* pTreeInfo = "1#2#3#4";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest4() //测试左单支
{
	char* pTreeInfo = "1#2#3#4";
	BinaryTreeThd<char> bt(pTreeInfo, strlen(pTreeInfo));
	bt.PostThread();
	bt.PostOrder();
}

void FunTest5()
{
	char* pTreeInfo1 = "0124##5##3";
	char* pTreeInfo2 = "01#2";
	BinaryTreeThd<char> bt(pTreeInfo2, strlen(pTreeInfo2));
	bt.PostThread();
	bt.PostOrder();
}