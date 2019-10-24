#pragma once
#include "TreeNode.h"
#include <iostream>
using namespace std;


template <typename T>
class Tree
{
private:
	TreeNode<T>* m_pRoot;  // ���ڵ�

public:
	Tree(); // ���캯��
	Tree(Tree<T>& ob); // ���ƹ��캯��
	~Tree(); // ��������

	bool Add_Node(T base_value, int direction, T value); // ���ӽ��,direction��0��ʾ���ӣ�1��ʾ�Һ���
	bool Del_Node(T value); // ɾ�����

	void preOrder(); // ǰ�����
	void inOrder(); // �������
	void postOrder(); // �������
	void level_Order(); //           ��α���
	void it_preOrder(); // �ǵݹ�ǰ�����
	void it_inOrder(); // �ǵݹ��������
	void it_postOrder(); // �ǵݹ�������

	TreeNode<T>* search(T value); // ��������

	int Cal_levels(T value); // ����ڵ����ڲ��
	int Cal_dus(T value); // ����ڵ�Ķ�
	bool Find_relations(T value, TreeNode<T>* par, TreeNode<T>* l, TreeNode<T>* r); // Ѱ�Ҹ��׺���Ů�����һ����û�з���false�����෵��true

	int Count_Nodes(); // ͳ�ƽڵ�����
	int Count_Yezis(); // ͳ��Ҷ�ڵ�����
	int Tree_height(); // ����������ĸ߶�

	void Tree_cout(); // �����������

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
	// �ݹ���ɸ��ƹ��캯����˳����ǰ��
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
