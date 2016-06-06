#include <iostream>
#include "BinarySearchTree.h"
#include "AVLTree.h"


void visit(int& someData)
	{
		someData=0;
	}


int main()
{
	BinarySearchTree<int> tree;
	AVLTree<int> treeAVL;

	
	/**/
	tree.add(5);
	tree.add(9);
	tree.add(4);
	tree.add(1);
	tree.add(8);
	tree.add(2);
	tree.add(7);
	tree.add(6);
	tree.add(3);
	tree.add(19);
	tree.add(15);
	tree.add(12);
	tree.add(14);

	cout << "Root: " << tree.showRoot() << "\n";
	tree.remove(15);

	cout << "Tree Height: " << tree.getHeight() << endl;

	tree.inorderTraverse(visit);
	tree.preorderTraverse(visit);
	tree.postorderTraverse(visit);

	bool is_exist = tree.is_contained(7);
	if (is_exist == true)
		cout << "\n7 is in the tree\n";
	else
		cout << "7 not found\n";

	is_exist = tree.is_contained(50);
	if (is_exist == true)
		cout << "50 is in the tree\n";
	else
		cout << "\n50 not found\n\n";

	tree.clear();


	treeAVL.add(5);
	treeAVL.add(9);
	treeAVL.add(4);
	treeAVL.add(1);
	treeAVL.add(8);
	treeAVL.add(2);
	treeAVL.add(7);
	treeAVL.add(6);
	treeAVL.add(3);
	treeAVL.add(19);
	treeAVL.add(15);
	treeAVL.add(12);
	treeAVL.add(14);

	cout << "Root: " << treeAVL.showRoot() << "\n";
	
	cout << "Tree Height: " << treeAVL.getHeight() << endl;

	treeAVL.inorderTraverse(visit);
	treeAVL.preorderTraverse(visit);
	treeAVL.postorderTraverse(visit);

	treeAVL.remove(3);
	treeAVL.preorderTraverse(visit);

	system("pause");
	return 0;
}