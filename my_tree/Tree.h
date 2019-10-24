#pragma once
#include "TreeNode.h"
#include <iostream>
using namespace std;


template <typename T>
class Tree
{
private:
	TreeNode<T>* m_pRoot;  // 根节点

public:
	Tree(); // 构造函数
	Tree(Tree<T>& ob); // 复制构造函数
	~Tree(); // 析构函数

	bool Add_Node(T base_value, int direction, T value); // 增加结点,direction的0表示左孩子，1表示右孩子
	bool Del_Node(T value); // 删除结点

	void preOrder(); // 前序遍历
	void inOrder(); // 中序遍历
	void postOrder(); // 后序遍历
	void level_Order(); //           层次遍历
	void it_preOrder(); // 非递归前序遍历
	void it_inOrder(); // 非递归中序遍历
	void it_postOrder(); // 非递归后序遍历

	TreeNode<T>* search(T value); // 搜索函数

	int Cal_levels(T value); // 计算节点所在层次
	int Cal_dus(T value); // 计算节点的度
	bool Find_relations(T value, TreeNode<T>* par, TreeNode<T>* l, TreeNode<T>* r); // 寻找父亲和子女，如果一个都没有返回false，其余返回true

	int Count_Nodes(); // 统计节点数量
	int Count_Yezis(); // 统计叶节点数量
	int Tree_height(); // 计算二叉树的高度

	void Tree_cout(); // 二叉树的输出

private:
	TreeNode<T>* Copy(TreeNode<T>* orignode);
};

template<typename T>
inline Tree<T>::Tree()
{
	m_pRoot = new TreeNode<T>(0);
}

template<typename T>
inline Tree<T>::Tree(Tree<T>& ob)
{
	m_pRoot = Copy(ob.m_pRoot);
}

template<typename T>
inline Tree<T>::~Tree()
{
	m_pRoot->del_node();
}

template<typename T>
inline bool Tree<T>::Add_Node(T base_value, int direction, T value)
{
	TreeNode<T>* temp = this->search(base_value);
	if(temp == nullptr)
	{
		return false;
	}
	else
	{
		if (direction == 0)
		{
			if (temp->left != nullptr)
			{
				return false;
			}
			temp->left = new TreeNode<T>(value);
			if(temp == nullptr)
			{
				return false;
			}
			temp->left->parent = temp;
			return true;
		}
		else if (direction == 1)
		{
			if (temp->right != nullptr)
			{
				return false;
			}
			temp->right = new TreeNode<T>(value);
			if (temp == nullptr)
			{
				return false;
			}
			temp->right->parent = temp;
			return true;
		}
	}
}

template<typename T>
inline bool Tree<T>::Del_Node(T value)
{
	TreeNode<T>* temp = this->search(value);
	if (temp == nullptr)
	{
		return false;
	}
	else
	{
		temp->del_node();
		return true;
	}
}

template<typename T>
inline void Tree<T>::preOrder()
{
	m_pRoot->preOrder();
}

template<typename T>
inline void Tree<T>::inOrder()
{
	m_pRoot->inOrder();
}

template<typename T>
inline void Tree<T>::postOrder()
{
	m_pRoot->postOrder();
}

template<typename T>
inline void Tree<T>::level_Order()
{
	m_pRoot->levelOrder();
}

template<typename T>
inline void Tree<T>::it_preOrder()
{
	m_pRoot->it_preOrder();
}

template<typename T>
inline void Tree<T>::it_inOrder()
{
	m_pRoot->it_inOrder();
}

template<typename T>
inline void Tree<T>::it_postOrder()
{
	m_pRoot->it_postOrder();
}

template<typename T>
inline TreeNode<T>* Tree<T>::search(T value)
{
	TreeNode<T>* temp = m_pRoot->search(value);
	return temp;
}

template<typename T>
inline int Tree<T>::Cal_levels(T value)
{
	TreeNode<T>* temp = search(value);
	if (temp == nullptr)
	{
		return -1;
	}
	else
	{
		int cnt = 0;
		while (temp != m_pRoot)
		{
			temp = temp->parent;
			cnt++;
		}
		return cnt;
	}
}

template<typename T>
inline int Tree<T>::Cal_dus(T value)
{
	TreeNode<T>* temp = search(value);
	if (temp == nullptr)
	{
		return -1;
	}
	else
	{
		int du = 0;
		if (temp->left != nullptr)
		{
			du++;
		}
		if (temp->right != nullptr)
		{
			du++;
		}
		return du;
	}
}

template<typename T>
inline bool Tree<T>::Find_relations(T value, TreeNode<T>* par, TreeNode<T>* l, TreeNode<T>* r)
{
	TreeNode<T>* temp = search(value);
	if (temp == nullptr)
	{
		return false;
	}
	else
	{
		par = temp->parent;
		l = temp->left;
		r = temp->right;
		return true;
	}
}

template<typename T>
inline int Tree<T>::Count_Nodes()
{
	return TreeNode<T>::jd_cnt;
}

template<typename T>
inline int Tree<T>::Count_Yezis()
{
	return m_pRoot->Count_Yezis();
}

template<typename T>
inline int Tree<T>::Tree_height()
{
	return m_pRoot->Tree_height();
}

template<typename T>
inline void Tree<T>::Tree_cout()
{
	level_Order();
}

template<typename T>
inline TreeNode<T>* Tree<T>::Copy(TreeNode<T>* orignode)
{
	// 递归完成复制构造函数，顺序是前序
	if (orignode == nullptr)
	{
		return nullptr;
	}

	TreeNode<T>* temp = new TreeNode<T>();
	if (temp == nullptr)
	{
		return nullptr;
	}
	temp->value = orignode->value;
	temp->left = Copy(orignode->left);
	temp->right = Copy(orignode->right);
	if(temp->left!=nullptr)
	{ 
		temp->left->parent = temp;
	}
	if (temp->right != nullptr)
	{
		temp->right->parent = temp;
	}
	return temp;
}
