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
	static int jd_cnt;  // ��̬������ͳ�ƽڵ����

	TreeNode(T value = 0) :
		value(value), left(nullptr), right(nullptr), parent(nullptr) 
	{
		jd_cnt++;
	}

	~TreeNode() 
	{ 
		jd_cnt--; 
	}

	TreeNode<T>* search(T value); // ����
	bool del_node(); // ɾ��

	void preOrder(); // ǰ�����
	void inOrder(); // �������
	void postOrder(); // �������
	void levelOrder(); // ��α���

	void it_preOrder(); // �ǵݹ�ǰ�����
	void it_inOrder(); // �ǵݹ��������
	void it_postOrder(); // �ǵݹ�������

	int Count_Yezis(); // ����Ҷ�ӽ����
	int Tree_height(); // �������ĸ߶�

private:
	void levelOrderImply(queue<TreeNode<T>*> cur);// ��α���ʵ��
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
	// temp ��ǰ���ʽڵ㣬pVisited�ϴη��ʽڵ�
	TreeNode<T>* temp = this;
	TreeNode<T>* pVisited = nullptr;
	stack<TreeNode<T>*> st;

	// �Ȱ�temp �ƶ���������������
	while (temp)
	{
		st.push(temp);
		temp = temp->left;
	}

	while (!st.empty())
	{
		// �����temp�϶�Ϊ�գ����ҵ��������������¶˵�����
		temp = st.top();
		st.pop();
		// һ�����ڵ���ʵ�ǰ���ǣ��������������������Ѿ������ʹ�
		if (temp->right == nullptr || pVisited == temp->right)
		{
			cout << temp->value << " ";
			// �޸���������ʵĽڵ�
			pVisited = temp;
		}
		else
		{
			// ��ʱ�������ڵ����·Ż�ջ�У��ȷ������������������϶���Ϊ��
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

