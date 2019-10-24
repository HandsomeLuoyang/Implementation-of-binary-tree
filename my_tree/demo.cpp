#include <iostream>
#include "Tree.h"
using namespace std;



int main()
{
	Tree<int> tr;
	tr.Add_Node(0, 0, 1);
	tr.Add_Node(0, 1, 2);
	tr.Add_Node(1, 0, 3);
	tr.Add_Node(1, 1, 4);
	Tree<int> tr2 = tr;
	 //tr.preOrder();
	 //tr.inOrder();
	 //tr.postOrder();
	 //tr.level_Order();
	 //tr.it_preOrder();
	 //tr.it_inOrder();
	 //tr2.it_postOrder();
	/*cout << tr.Count_Nodes();
	tr.Del_Node(4);
	cout << endl << tr.Count_Nodes();*/
	// cout << tr.Count_Yezis();
	// cout << tr.Tree_height();
	return 0;
}