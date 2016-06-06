#pragma once

#include "BinaryNode.h"
#include "BinarySearchTree.h"
#include <iostream>
using std::cout;
using std::endl;

template <class DataType>
class AVLTree : public BinarySearchTree<DataType>
{
	protected:
		BinaryNode<DataType>* insert(BinaryNode<DataType>* root, BinaryNode<DataType>* newNodePtr);
		void leftBalance(BinaryNode<DataType>* root);
		void rightBalance(BinaryNode<DataType>* root);
		BinaryNode<DataType>* rotateRight(BinaryNode<DataType>* root);
		BinaryNode<DataType>* rotateLeft(BinaryNode<DataType>* root);

		int balanceFactor(BinaryNode<DataType>* root);
		
		BinaryNode<DataType>* balance(BinaryNode<DataType>* root);

		BinaryNode<DataType>* RR_rotation(BinaryNode<DataType>* root);
		BinaryNode<DataType>* LL_rotation(BinaryNode<DataType>* root);
		BinaryNode<DataType>* RL_rotation(BinaryNode<DataType>* root);
		BinaryNode<DataType>* LR_rotation(BinaryNode<DataType>* root);

		BinaryNode<DataType>* minValueNode(BinaryNode<DataType>* root);


	public:
		//CONSTRUCTORS:
		
		AVLTree() : BinarySearchTree() {}
		AVLTree(const DataType& rootItem) : BinarySearchTree(rootItem) {}
		AVLTree(const DataType& rootItem, const BinarySearchTree<DataType>*
			leftTreePtr, const BinarySearchTree<DataType>* rightTreePtr) : BinarySearchTree(rootItem, leftTreePtr, rightTreePtr) {}
		AVLTree(const BinarySearchTree<DataType>& treePtr) : BinarySearchTree(treePtr) {}
		//~AVLTree();


		bool add(const DataType& newData);
		bool remove(DataType target);													// Removes a node
		
		

};

template<class DataType>
int AVLTree<DataType>::balanceFactor(BinaryNode<DataType>* root)
{
	return getHeightHelper(root->getLeftChildPtr()) - getHeightHelper(root->getRightChildPtr());
}

template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::RR_rotation(BinaryNode<DataType>* root) // Rotate left
{
	BinaryNode<DataType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(nodePtr->getLeftChildPtr());
	nodePtr->setLeftChildPtr(root);
	
	return nodePtr;
}

template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::LL_rotation(BinaryNode<DataType>* root) // Rotate right
{
	BinaryNode<DataType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(nodePtr->getRightChildPtr());
	nodePtr->setRightChildPtr(root);

	return nodePtr;
}

template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::RL_rotation(BinaryNode<DataType>* root)
{
	BinaryNode<DataType>* nodePtr = root->getRightChildPtr();
	root->setRightChildPtr(LL_rotation(nodePtr));
	return RR_rotation(root);
}

template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::LR_rotation(BinaryNode<DataType>* root)
{
	BinaryNode<DataType>* nodePtr = root->getLeftChildPtr();
	root->setLeftChildPtr(RR_rotation(nodePtr));
	return LL_rotation(root);
}


template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::balance(BinaryNode<DataType>* root)
{
	int bal_factor = balanceFactor(root);

	if (bal_factor > 1)
	{
		if (balanceFactor(root->getLeftChildPtr()) > 0)
			root = LL_rotation(root);
		else
			root = LR_rotation(root);
	}
	else if (bal_factor < -1)
	{
		if (balanceFactor(root->getRightChildPtr()) > 0)
			root = RL_rotation(root);
		else
			root = RR_rotation(root);
	}
	return root;
}


template<class DataType>
BinaryNode<DataType>* AVLTree<DataType>::insert(BinaryNode<DataType>* root, BinaryNode<DataType>* newNodePtr)
{
	if (root == nullptr)
		return newNodePtr;
	else if (newNodePtr->getItem() < root->getItem())
		root->setLeftChildPtr(insert(root->getLeftChildPtr(),newNodePtr));
	else
		root->setRightChildPtr(insert(root->getRightChildPtr(), newNodePtr));

	return balance(root);
}

template<class DataType>
bool AVLTree<DataType>::add(const DataType& newData)
{
	BinaryNode<DataType>* newNodePtr = new BinaryNode<DataType>(newData);
	set_rootPtr(insert(get_rootPtr(), newNodePtr));
	increment_nodeCounter();
	cout << "Added " << newData << " Total Nodes: " << getNumberOfNodes() << endl;
	return true;
}


// REMOVE
template< class DataType>
bool AVLTree<DataType>::remove(DataType target)
{
	bool success = false;
	set_rootPtr(removeValue(get_rootPtr(), target, success));
	if (success == true) decrement_nodeCounter();
	cout << "Total Nodes: " << getNumberOfNodes() << endl;
	return success;
} // end remove



/* Given a non-empty binary search tree, return the node with minimum
key value found in that tree. Note that the entire tree does not
need to be searched. */
template< class DataType>
BinaryNode<DataType>* AVLTree<DataType>::minValueNode(BinaryNode<DataType>* root)
{
	BinaryNode<DataType>* nodePtr = root;
	// loop down to find the leftmost leaf 
	while (nodePtr->getLeftChildPtr() != nullptr;)
		nodePtr = nodePtr->getLeftChildPtr();
	return nodePtr;
}


