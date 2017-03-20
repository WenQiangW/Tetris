#include"BinaryTree.hpp"
#include<list>

//求树中两个结点的最低公共祖先

// 树为二叉搜索树
template<class T>
BinaryTreeNode<T>* GetLastCommomParent(BinaryTreeNode<T>* pRoot,int data1,int data2)
{
	if (pRoot)
	{
		if (data1 < pRoot->_data && data2 < pRoot->_data)
			return GetLastCommomParent(pRoot->_pLeftChild,data1,data2);
		else if (data1 > pRoot->_data && data2 > pRoot->_data)
			return GetLastCommomParent(pRoot->_pRightChild, data1, data2);
		else
			return pRoot;
	}
	return NULL;
}

//树中的结点有指向父节点的指针


//树中的结点没有指向父节点的指针
//用两个链表分别保存从根节点到输入的两个节点的路径，然后把问题转换成两个链表的最后公共节点。

//递归算法：
template<class T>
bool FindNode(BinaryTreeNode<T> * pRoot,BinaryTreeNode<T> *pNode)
{
	if (pRoot == NULL || pNode == NULL)
		return false;
	if (pRoot == pNode)
		return true;
	bool found = FindNode(pRoot->_pLeftChild,pNode);
	if (!found)
		return FindNode(pRoot->_pRightChild,pNode);
}
template<class T>
BinaryTreeNode<T>* GetLastCommomParent(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pNode1, BinaryTreeNode<T>* pNode2)
{
	if (FindNode(pRoot->_pLeftChild, pNode1))
	{
		if (FindNode(pRoot->_pRightChild, pNode2))
			return pRoot;
		else
			return GetLastCommomParent(pRoot->_pLeftChild,pNode1,pNode2);
	}
	else
	{
		if (FindNode(pRoot->_pLeftChild, pNode2))
			return pRoot;
		else
			return GetLastCommomParent(pRoot->_pRightChild,pNode1,pNode2);
	}
}


//非递归解法：
//先求从根节点到两个节点的路径，然后再比较对应路径的节点就行，最后一个相同的节点也就是他们在二叉树中的最低公共祖先节点

template<class T>
bool GetPath(BinaryTreeNode<T>* pRoot,BinaryTreeNode<T>* pNode,list<BinaryTreeNode<T>*>& path)
{
	if (pRoot == NULL || pNode == NULL)
		return  false;
	path.push_back(pRoot);
	if (pRoot == pNode)
		return true;
	bool found = false;
	found = GetPath(pRoot->_pLeftChild,pNode,path);
	if (!found)
		found = GetPath(pRoot->_pRightChild,pNode,path);
	if (!found)
		path.pop_back();
	return found;
}
template<class T>
BinaryTreeNode<T>* GetLastCommomAcess(BinaryTreeNode<T>* pRoot, BinaryTreeNode<T>* pNode1, BinaryTreeNode<T>* pNode2)
{
	if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;
	list<BinaryTreeNode<T>*> path1;
	bool res1 = GetPath(pRoot,pNode1,path1);
	list<BinaryTreeNode<T>*> path2;
	bool res2 = GetPath(pRoot, pNode2, path2);
	if (!res1 || !res2)
		return NULL;
	//求两个链表的公共节点
	BinaryTreeNode<T>* Ancestor = NULL;
	list<BinaryTreeNode<T>*>::const_iterator iter1 = path1.end();
	list<BinaryTreeNode<T>*>::const_iterator iter2 = path2.end() ;
	while (--iter1 != path1.begin() && --iter2 != path2.begin())
	{
		if (*iter1 == *iter2)
		{
			Ancestor = *iter1;
			break;
		}
	}
	return Ancestor;
}

void TestGetAncestor()
{
	char *pTreeInfo = "abd###ce##f";
	BinaryTree<char> tree(pTreeInfo, strlen(pTreeInfo));
	BinaryTreeNode<char>* pRoot = tree.GetRoot();
	BinaryTreeNode<char>* Node1 = tree.Find('e');
	BinaryTreeNode<char>* Node2 = tree.Find('f');
	BinaryTreeNode<char>* Ancestot = GetLastCommomAcess(pRoot,Node1,Node2);
}