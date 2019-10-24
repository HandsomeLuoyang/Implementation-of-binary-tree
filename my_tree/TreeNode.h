#include <iostream>
#include <queue>
#include <stack>
using namespace std;
#pragma once

template <typename T>
class TreeNode
{
public:
	T value;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	static int jd_cnt;  // 静态变量，统计节点个数

	TreeNode(T value = 0) :
		value(value), left(nullptr), right(nullptr), parent(nullptr) 
	{
		jd_cnt++;
	}

	~TreeNode() 
	{ 
		jd_cnt--; 
	}

	TreeNode<T>* search(T value); // 搜索
	bool del_node(); // 删除

	void preOrder(); // 前序遍历
	void inOrder(); // 中序遍历
	void postOrder(); // 后序遍历
	void levelOrder(); // 层次遍历

	void it_preOrder(); // 非递归前序遍历
	void it_inOrder(); // 非递归中序遍历
	void it_postOrder(); // 非递归后序遍历

	int Count_Yezis(); // 计算叶子结点数
	int Tree_height(); // 计算树的高度

private:
	void levelOrderImply(queue<TreeNode<T>*> cur);// 层次遍历实现
};

template<typename T>
int TreeNode<T>::jd_cnt = 0;

template<typename T>
inline TreeNode<T>* TreeNode<T>::search(T value)
{
	if (this == nullptr)
	{
		return nullptr;
	}
	if (this->value == value)
	{
		return this;
	}
	else
	{
		TreeNode<T>* temp;
		if (this->left != nullptr)
		{
			temp = this->left->search(value);
			if (temp != nullptr)
			{
				return temp;
			}
		}
		if (this->right != nullptr)
		{
			temp = this->right->search(value);
			if (temp != nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}

}

template<typename T>
inline bool TreeNode<T>::del_node()
{
	if (this->left != nullptr)
	{
		this->left->del_node();
	}
	if (this->right != nullptr)
	{
		this->right->del_node();
	}
	if (this->parent != nullptr)
	{
		if (this == this->parent->left)
		{
			this->parent->left = nullptr;
		}
		else if (this == this->parent->right)
		{
			this->parent->right = nullptr;
		}
	}
	delete this;
	return true;
}

template<typename T>
inline void TreeNode<T>::preOrder()
{
	cout << this->value << " ";
	if (this->left != nullptr)
	{
		this->left->preOrder();
	}
	if (this->right != nullptr)
	{
		this->right->preOrder();
	}
}

template<typename T>
inline void TreeNode<T>::inOrder()
{
	if (this->left != nullptr)
	{
		this->left->inOrder();
	}
	cout << this->value << " ";
	if (this->right != nullptr)
	{
		this->right->inOrder();
	}
}

template<typename T>
inline void TreeNode<T>::postOrder()
{
	if (this->left != nullptr)
	{
		this->left->postOrder();
	}
	if (this->right != nullptr)
	{
		this->right->postOrder();
	}
	cout << this->value << " ";
}

template<typename T>
inline void TreeNode<T>::levelOrder()
{
	queue<TreeNode<T>*> cur;
	cout << this->value << " ";
	if (this->left != nullptr)
	{
		cur.push(this->left);
	}
	if (this->right != nullptr)
	{
		cur.push(this->right);
	}
	if (cur.empty())
	{
		return;
	}
	this->levelOrderImply(cur);
}

template<typename T>
inline void TreeNode<T>::it_preOrder()
{
	TreeNode<T>* temp = this;
	stack<TreeNode<T>*> st;
	while (temp != nullptr || !st.empty())
	{
		while (temp != nullptr)
		{
			cout << temp->value << " ";
			st.push(temp);
			temp = temp->left;
		}
		if (!st.empty())
		{
			temp = st.top();
			st.pop();
			temp = temp->right;
		}
	}
}

template<typename T>
inline void TreeNode<T>::it_inOrder()
{
	TreeNode<T>* temp = this;
	stack<TreeNode<T>*> st;
	while (temp != nullptr || !st.empty())
	{
		while (temp != nullptr)
		{
			st.push(temp);
			temp = temp->left;
		}
		if (!st.empty())
		{
			temp = st.top();
			cout << temp->value << " ";
			st.pop();
			temp = temp->right;
		}
	}
}

template<typename T>
inline void TreeNode<T>::it_postOrder()
{
	// temp 当前访问节点，pVisited上次访问节点
	TreeNode<T>* temp = this;
	TreeNode<T>* pVisited = nullptr;
	stack<TreeNode<T>*> st;

	// 先把temp 移动到左子树最下面
	while (temp)
	{
		st.push(temp);
		temp = temp->left;
	}

	while (!st.empty())
	{
		// 到这里，temp肯定为空，并且到了左子树的最下端的外面
		temp = st.top();
		st.pop();
		// 一个根节点访问的前提是，无右子树或者右子树已经被访问过
		if (temp->right == nullptr || pVisited == temp->right)
		{
			cout << temp->value << " ";
			// 修改最近被访问的节点
			pVisited = temp;
		}
		else
		{
			// 此时，将根节点重新放回栈中，先访问右子树，右子树肯定不为空
			st.push(temp);
			temp = temp->right;
			while (temp)
			{
				st.push(temp);
				temp = temp->left;
			}
		}
	}
	cout << endl;
}

template<typename T>
inline int TreeNode<T>::Count_Yezis()
{
	if (this == nullptr)
	{
		return 0;
	}
	if (this->left == nullptr&&this->right == nullptr)
	{
		return 1;
	}
	return (this->left->Count_Yezis() + this->right->Count_Yezis());
}

template<typename T>
inline int TreeNode<T>::Tree_height()
{
	int height = 0;
	if (this != nullptr)
	{
		int left_height = this->left->Tree_height();
		int right_height = this->right->Tree_height();
		height = left_height > right_height ? ++left_height : ++right_height;
	}
	return height;
}

template<typename T>
inline void TreeNode<T>::levelOrderImply(queue<TreeNode<T>*> cur)
{
	TreeNode<T>* temp = cur.front();
	cur.pop();
	cout << temp->value << " ";
	if (temp->left != nullptr)
	{
		cur.push(temp->left);
	}
	if (temp->right != nullptr)
	{
		cur.push(temp->right);
	}
	if (cur.empty())
	{
		return;
	}
	this->levelOrderImply(cur);
}

