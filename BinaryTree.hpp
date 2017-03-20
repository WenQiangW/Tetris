#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
int leafCountt = 0;
template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
	:_data(data)
	, _pLeftChild(NULL)
	, _pRightChild(NULL)
	{}

	T _data;
	BinaryTreeNode<T>* _pLeftChild;
	BinaryTreeNode<T>* _pRightChild;
};
template<class T>
class BinaryTree
{
public:
	BinaryTree()
		:_pRoot(NULL)
	{}
	BinaryTree(const T array[], size_t size)
		:_pRoot(NULL)
	{
		size_t index = 0;
		_CreatBinaryTree(_pRoot, array, size, index);
	}
	BinaryTree(BinaryTree<T>& tree)
	{
		_pRoot = _CopyBinartTree(tree._pRoot);
	}
	BinaryTree<T>& operator=(BinaryTree<T>& tree)
	{
		if (this != &tree)
		{
			this->~BinaryTree();
			_pRoot = _CopyBinartTree(tree._pRoot);
		}
		return *this;
	}
	void PreOrder() //递归 abdcef
	{
		cout << "前序遍历" << endl;
		_PreOreder(_pRoot);
		cout << endl;
	}
	void PreOrder_Nor() //非递归
		//在栈中存放（后进先出） 先存放右孩子，再存放左孩子
	{
		cout << "前序遍历" << endl;
		if (_pRoot == NULL)
			return;
		stack<BinaryTreeNode<T>*> s;
		s.push(_pRoot);
		while (!s.empty())
		{
			BinaryTreeNode<T>* pCur = s.top();
			cout << pCur->_data << " ";
			s.pop();
			if (pCur->_pRightChild)
				s.push(pCur->_pRightChild);
			if (pCur->_pLeftChild)
				s.push(pCur->_pLeftChild);
		}
		cout << endl;
	}
	void InOrder() //递归：dbaecf
	{
		cout << "中序遍历" << endl;
		_InOrder(_pRoot);
		cout << endl;
	}
	void InOrder_Nor() //非递归
		//存放到栈中 先找到最左边的节点（依次存放）
	{
		cout << "中序遍历" << endl;
		if (NULL == _pRoot)
			return;

		BinaryTreeNode<T>* pCur = _pRoot;
		stack<BinaryTreeNode<T>*> s;
		while (NULL != pCur || !s.empty())
		{
			while (pCur) //存放节点，找到最左边的节点
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}

			BinaryTreeNode<T>* pTop = s.top();
			cout << pTop->_data << " ";
			pCur = pTop->_pRightChild; //再找当前节点的右子树的最左边
			s.pop();
		}
		cout << endl;
	}
	void InOrder_Nor2()
		//从根节点开始，只有当前节点存在或者栈不为空，则重复下面的工作
		//1如果当前结点存在，则进栈并遍历左子树
		//2否则退栈并访问，然后遍历右子树
	{
		stack<BinaryTreeNode<T>*> s;
		BinaryTreeNode<T>* pCur = _pRoot;
		BinaryTreeNode<T>* top = NULL;
		while (NULL != pCur || !s.empty())
		{
			if (pCur != NULL) //根指针进栈，遍历左子树
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}
			else
			{
				//根指针退栈，并访问根节点，遍历右子树
				top = s.top();
				cout << top->_data << "";
				s.pop();
				pCur = pCur->_pRightChild;
			}
		}
	}
	void PostOrder() //递归  dbefca
	{
		cout << "后序遍历" << endl;
		_PostOrder(_pRoot);
		cout << endl;
	}
	void PostOrder_Nor() //非递归
		// 存放到栈中：先找到树的最左边，
	{
		cout << "后序遍历" << endl;
		if (NULL == _pRoot)
			return;
		BinaryTreeNode<T> *pCur = _pRoot;
		BinaryTreeNode<T>* pPre = NULL; //保存已访问过的右子树
		stack<BinaryTreeNode<T>*> s;
		while (NULL != pCur || !s.empty())
		{
			while (pCur) //遍历左子树
			{
				s.push(pCur);
				pCur = pCur->_pLeftChild;
			}
			BinaryTreeNode<T>* pTop = s.top();
			if (NULL == pTop->_pRightChild || pTop->_pRightChild == pPre) //判断右子树是否为空或者访问过
			{
				cout << pTop->_data << " ";
				pPre = pTop;//保存已访问过的结点
				s.pop();
			}
			else
			{
				pCur = pTop->_pRightChild;
			}
		}
		cout << endl;
	}

	~BinaryTree()
	{
		_DestoryBinaryTree(_pRoot);
	}

	void LevelOrder() //层序遍历
		//存放在队列中：先存放根节点，再存放左孩子，再存放右孩子
	{
		cout << "层次遍历" << endl;
		if (NULL == _pRoot)
			return;
		queue<BinaryTreeNode<T> *> q;
		if (_pRoot)
			q.push(_pRoot);
		while (!q.empty())
		{
			BinaryTreeNode<T>* pCur = q.front();
			cout << pCur->_data << " ";
			q.pop();	
			if (pCur->_pLeftChild)
				q.push(pCur->_pLeftChild);
			if (pCur->_pRightChild)
				q.push(pCur->_pRightChild);
		}
		cout << endl;
	}

	BinaryTreeNode<T>* GetLeftChild(BinaryTreeNode<T>* pCur)
	{
		return (NULL == pCur->_pLeftChild) ? NULL : pCur->_pLeftChild;
	}
	BinaryTreeNode<T>* GetRightChild(BinaryTreeNode<T>* pCur)
	{
		return (NULL == pCur->_pRightChild) ? NULL : pCur->_pRightChild;
	}
	BinaryTreeNode<T>* GetParent(BinaryTreeNode<T>* pChild)
	{
		if (pChild == NULL || _pRoot == NULL || _pRoot == pChild)
			return NULL;
		return _GetParent(_pRoot, pChild);
	}
	BinaryTreeNode<T>* GetRoot()
	{
		return _pRoot;
	}
	BinaryTreeNode<T>* Find(const T& data)
	{
		if (NULL == _pRoot)
			return NULL;
		return	_Find(_pRoot, data);
	}

	size_t Height()
	{
		return _Height(_pRoot);
	}
	size_t GetLeafNodeNum()
	{
		return _GetLeafNodeNum(_pRoot);
	}
	size_t GetNodeNum()
	{
		return _GetNodeNum(_pRoot);
	}
	size_t GetKthLeverNodeNum(size_t k)
	{
		return _GetKthLeverNodeNum(_pRoot,k);
	}
	//判断两个二叉树的结构是否相同
	bool StructureCmp(BinaryTreeNode<T> *pRoot1, BinaryTreeNode<T> *pRoot2)
	{
		if (pRoot1 == NULL && pRoot2 == NULL) // 都为空，返回真  
			return true;
		else if (pRoot1 == NULL || pRoot2 == NULL) // 有一个为空，一个不为空，返回假  
			return false;
		bool resultLeft = StructureCmp(pRoot1->m_pLeft, pRoot2->m_pLeft); // 比较对应左子树   
		bool resultRight = StructureCmp(pRoot1->m_pRight, pRoot2->m_pRight); // 比较对应右子树  
		return (resultLeft && resultRight);
	}
	//前序中序 构建二叉树
	void ReBuildBinaryTree(T pre[], size_t preSize, T in[], size_t inSize)
	{
		size_t index = 0;
		_ReBuildBinaryTree(_pRoot, pre, index, preSize, in, inSize, 0, inSize);
	}
	void RebuildBinaryTreee(T pre[],T In[],size_t len)
	{
		if (NULL == pre || NULL == In || len < 0)
			return ;
		_pRoot =  _ConstructTree(pre, pre + len - 1,In,In+len-1);
	}


	//判断一棵二叉树是否为完全二叉树
	//借助层序遍历，采用队列的方式
	bool IsCompleteBinaryTree(BinaryTreeNode<T> *pRoot )
	{
		//空树也是完全二叉树
		if (pRoot == NULL)
			return true; 
		queue<BinaryTreeNode<T>*> q;
		q.push(pRoot); //根节点入队
		bool mustLeft = false;
		bool result = true;
		while (!q.empty())
		{
			BinaryTreeNode<T> *pCur = q.front();
			q.pop();
			if (mustLeft) //出现了 空子树的节点
			{
				if (pCur->_pLeftChild != NULL || pCur->_pRightChild != NULL)
				{
					result = false;
					break;
				}
			}
			else 
			{
				if (pCur->_pLeftChild != NULL && pCur->_pRightChild != NULL)
				{
					q.push(pCur->_pLeftChild);
					q.push(pCur->_pRightChild);
				}
				else if (pCur->_pLeftChild == NULL && pCur->_pRightChild != NULL)
				{
					result = false;
					break;
				}
				else if (pCur->_pRightChild == NULL && pCur->_pLeftChild != NULL)
				{
					q.push(pCur->_pLeftChild);
					mustLeft = true;
				}
				else
				{
					mustLeft = true;
				}
			}
		}
		return result;
	}
	//借助层序遍历，把所有的节点存在
	bool IsCompleteTree(BinaryTreeNode<T> *pRoot)
	{
		if (pRoot == NULL)
			return true;
		queue<BinaryTreeNode<T>*> q;
		q.push(pRoot);
		BinaryTreeNode<T>* pCur = NULL;
		//层序遍历二叉树 ,当遇到空节点是退出
		while ((pCur = q.front()) != NULL)
		{
			q.pop();
			q.push(pCur->_pLeftChild);
			q.push(pCur->_pRightChild);
		}
		q.pop();//把当前节点为空出队
		//查看剩余队列中是否有不为空的节点

		pCur = q.front();
		if (pCur != NULL)
			return false;
		return true;
	}
	//求二叉树的镜像
	BinaryTreeNode<T>* Mirror(BinaryTreeNode<T> * pRoot)
	{
		if (pRoot == NULL) // 返回NULL  
			return NULL;
		BinaryTreeNode<T> * pLeft = Mirror(pRoot->_pLeftChild); // 求左子树镜像  
		BinaryTreeNode<T> * pRight = Mirror(pRoot->_pRightChild); // 求右子树镜像  
		// 交换左子树和右子树  
		pRoot->_pLeftChild = pRight;
		pRoot->_pRightChild = pLeft;
		return pRoot;
	}

	//二叉搜索树转换成双向链表
	BinaryTreeNode<T>* Convert(BinaryTreeNode<T>* pRootInTree)
	{
		BinaryTreeNode<T>* pLastNodeInList = NULL;

		ConvertNode(pRootInTree, &pLastNodeInList);

		//pLastNodeInList指向双向链表的尾结点，再次遍历找到头结点  
		BinaryTreeNode<T>* pHeadOfList = pLastNodeInList;
		while (pHeadOfList != NULL && pHeadOfList->_pLeftChild != NULL)
			pHeadOfList = pHeadOfList->_pLeftChild;

		return pHeadOfList;
	}
private:
	//二叉树搜索树转换双向链表
	void ConvertNode(BinaryTreeNode<T>* pNode, BinaryTreeNode<T>** pLastNodeInList)
	{
		if (pNode == NULL)
			return;
		BinaryTreeNode<T>* pCurrent = pNode;
		//递归处理左子树  
		if (pCurrent->_pLeftChild != NULL)
			ConvertNode(pNode->_pLeftChild, pLastNodeInList);
		//处理当前结点              
		pCurrent->_pLeftChild = *pLastNodeInList;    //将当前结点的左指针指向已经转换好的链表的最后一个位置  
		if (*pLastNodeInList != NULL)
			(*pLastNodeInList)->_pRightChild = pCurrent;//将已转换好的链表的最后一个结点的右指针指向当前结点  

		*pLastNodeInList = pCurrent;//更新链表的最后一个结点  
		//递归处理当前结点的右子树  
		if (pCurrent->_pRightChild != NULL)
			ConvertNode(pNode->_pRightChild, pLastNodeInList);
	}

	void _CreatBinaryTree(BinaryTreeNode<T>*& pRoot, const T array[], size_t size, size_t& index)
	{
		if (index < size && '#' != array[index])
		{
			pRoot = new BinaryTreeNode<T>(array[index]);
			_CreatBinaryTree(pRoot->_pLeftChild, array, size, ++index);
			_CreatBinaryTree(pRoot->_pRightChild, array, size, ++index);
		}
	}
	BinaryTreeNode<T>*& _CopyBinartTree(BinaryTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			BinaryTreeNode<T>* pNewRoot = new BinaryTreeNode<T>(pRoot->_data);
			pNewRoot->_pLeftChild = _CopyBinartTree(pRoot->_pLeftChild);
			pNewRoot->_pRightChild = _CopyBinartTree(pRoot->_pRightChild);
			return pNewRoot;
		}

	}
	void _DestoryBinaryTree(BinaryTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			_DestoryBinaryTree(pRoot->_pLeftChild);
			_DestoryBinaryTree(pRoot->_pRightChild);
			delete pRoot;
			pRoot = NULL;
		}
	}

	void _PreOreder(BinaryTreeNode<T>* proot) //前序遍历
	{
		if (proot)
		{
			cout << proot->_data << " ";
			_PreOreder(proot->_pLeftChild);
			_PreOreder(proot->_pRightChild);
		}
	}
	void _InOrder(BinaryTreeNode<T>* proot) //中序遍历
	{
		if (proot)
		{
			_InOrder(proot->_pLeftChild);
			cout << proot->_data << " ";
			_InOrder(proot->_pRightChild);
		}
	}
	void _PostOrder(BinaryTreeNode<T>* proot)  //后续遍历
	{
		if (proot)
		{
			_PostOrder(proot->_pLeftChild);
			_PostOrder(proot->_pRightChild);
			cout << proot->_data << " ";
		}
	}

	BinaryTreeNode<T>* _GetParent(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pChild)
	{
		if (NULL == pRoot)
			return NULL;
		if (pRoot->_pLeftChild == pChild || pRoot->_pRightChild == pChild)
			return pRoot;
		BinaryTreeNode<T>* pParent;
		if (pParent = _GetParent(pRoot->_pLeftChild, pChild))
			return pParent;
		return _GetParent(pRoot->_pRightChild, pChild);

	}
	BinaryTreeNode<T>* _Find(BinaryTreeNode<T>* pRoot, const T& data)
	{
		if (pRoot == NULL)
			return NULL;
		if (pRoot->_data == data)
			return pRoot;
		BinaryTreeNode<T>* find;
		if (find = _Find(pRoot->_pLeftChild, data))
			return find;
		return _Find(pRoot->_pRightChild, data);
	}
	size_t _Height(BinaryTreeNode<T>* pRoot)
	{
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_pLeftChild && NULL == pRoot->_pRightChild)
			return 1;
		size_t LHeigt = _Height(pRoot->_pLeftChild);
		size_t RHeight = _Height(pRoot->_pRightChild);
		return (LHeigt > RHeight) ? (LHeigt + 1) : (RHeight + 1);
	}
	size_t _GetLeafNodeNum(BinaryTreeNode<T>* pRoot)
		// 采用递归算法，如果空树返回0，如果只有一个节点(根节点)返回1，否则为左右子树的叶子结点树之和
	{
		size_t leafCount = 0;
		if (pRoot == NULL)
			leafCount = 0;
		else if (pRoot->_pLeftChild == NULL && pRoot->_pRightChild == NULL)
			leafCount = 1;
		else
			leafCount = _GetLeafNodeNum(pRoot->_pLeftChild) + _GetLeafNodeNum(pRoot->_pRightChild);
		return leafCount;
	}
	void _GetLeafNodeNum2(BinaryTreeNode<T>* pRoot)
		//后序遍历统计叶子结点
	{
		if (pRoot != NULL)
		{
			_GetLeafNodeNum2(pRoot->_pLeftChild);
			_GetLeafNodeNum2(pRoot->_pRightChild);
			if (pRoot->_pLeftChild == NULL && pRoot->_pRightChild == NULL)
				leftCountt++;
		}
	}
	size_t _GetNodeNum(BinaryTreeNode<T>* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		else
			return _GetNodeNum(pRoot->_pLeftChild) + _GetNodeNum(pRoot->_pRightChild) + 1;
	}
	size_t _GetKthLeverNodeNum(BinaryTreeNode<T>* pRoot,size_t k)
		//：（1）如果二叉树为空或者k<1返回0
		//（2）如果二叉树不为空并且k == 1，返回1
		//（3）如果二叉树不为空且k>1，返回左子树中k - 1层的节点个数与右子树k - 1层节点个数之和
	{
		if (pRoot == NULL || k == 0)
			return 0;
		if (k == 1 && pRoot != NULL)
			return 1;
		int leftNum = _GetKthLeverNodeNum(pRoot->_pLeftChild,k-1);
		int rightNum = _GetKthLeverNodeNum(pRoot->_pRightChild,k-1);
		return leftNum + rightNum;
	}
	void _ReBuildBinaryTree(BinaryTreeNode<T>*& pRoot,T pre[],size_t& index,size_t preSize,T in[],size_t InSize,size_t left,size_t right)
	{
		if (left >= right || preSize != InSize)
			return;
		//前序结果中取一个元素
		// 在中序中找前序index的元素
		size_t idx = left;
		while (idx < right)
		{
			if (pre[index] == in[idx])
				break;
			idx++;
		}
		if (idx == right)
			return;
		pRoot = new BinaryTreeNode<T>(pre[index]);

		if (left < idx) //左子树存在
		_ReBuildBinaryTree(pRoot->_pLeftChild, pre, ++index, preSize, in, InSize,left, idx);

		if (idx + 1 < right)
			_ReBuildBinaryTree(pRoot->_pRightChild, pre, ++index, preSize, in, InSize, idx + 1, right);

	}
	//前中序重建二叉树
	BinaryTreeNode<T>* _ConstructTree(T *startPreOrder,T *endPreOrder,T *startInOrder,T *endInOrder)
	{
		//前序遍历的第一个结点为根节点
		T rootValue = startPreOrder[0];
		BinaryTreeNode<T>* pRoot = new	BinaryTreeNode<T>(rootValue);
		//只有一个元素
		if (startPreOrder == endPreOrder && *startInOrder == *startPreOrder)
			return pRoot;
		//在中序遍历中找到根节点的值
		T* rootInOreder = startInOrder;
		while (rootInOreder <= endInOrder && *rootInOreder != rootValue)
		{
			++rootInOreder;
		}//跳出循环可能没有找到
		if (*rootInOreder != rootValue)
			throw std::exception("Invalid input");

		int leftlength = rootInOreder - startInOrder; //左子树的长度
		T *leftPreEnd = startPreOrder + leftlength; //前序左子树的end位置
		if (leftlength > 0)//构建左子树
		{
			pRoot->_pLeftChild = _ConstructTree(startPreOrder + 1, leftPreEnd, startInOrder, rootInOreder - 1);
		}
		if (leftlength < endPreOrder - startPreOrder)//构建右子树
		{
			pRoot->_pRightChild = _ConstructTree(leftPreEnd + 1, endPreOrder, rootInOreder + 1, endInOrder);
		}
		return pRoot;
	}

private:
	BinaryTreeNode<T>* _pRoot;
};

void Test()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo,strlen(pTreeInfo));
	BinaryTree<char> t1(tree);
	BinaryTree<char> t2;
	t2 = tree;
	tree.PreOrder(); 
	tree.PreOrder_Nor();
	tree.InOrder();
	tree.InOrder_Nor();
	tree.PostOrder();
	tree.PostOrder_Nor();
	BinaryTreeNode<char>* Node = tree.Find('e');
	BinaryTreeNode<char>* Parent = tree.GetParent(Node);
	BinaryTreeNode<char>* Child1 = tree.GetLeftChild(Parent);
	BinaryTreeNode<char>* Child2 = tree.GetRightChild(Parent);
	size_t h = tree.Height();
}

void Test2()
{
	char* pre = "abdcef";
	char* in = "dbaecf";
	BinaryTree<char> t;
	t.ReBuildBinaryTree(pre,strlen(pre),in,strlen(in));
	t.PreOrder();
	t.InOrder();
}
void Test3()
{
	char* pre = "abdcef";
	char* in = "dbaecf";
	BinaryTree<char> t;
	t.RebuildBinaryTreee(pre, in,strlen(pre));
	t.PreOrder();
	t.InOrder();
}

void TestIsCompleteTree()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo, strlen(pTreeInfo));
	BinaryTreeNode<char>* proot = tree.GetRoot();
	bool a = tree.IsCompleteBinaryTree(proot);
	bool b = tree.IsCompleteTree(proot);
}