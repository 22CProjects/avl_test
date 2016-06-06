#pragma once

#include "BinaryNode.h"
#include <iostream>
using std::cout;
using std::endl;

template<class DataType>
class BinarySearchTree
{
	private:
		BinaryNode<DataType>* rootPtr;	// point to the highest root of the tree
		int nodeCounter;

	protected:
		// Methods for derived class to access private variables
		BinaryNode<DataType>* get_rootPtr()				{ return rootPtr; }		// return the address of rootPtr
		void set_rootPtr(BinaryNode<DataType>* aNode)	{ rootPtr = aNode; }	// Point rootPtr to and address
		void set_nodeCounter(int num_node)				{ nodeCounter = num_node; }	// set nodeCounter to a number --MIGHT NOT NEED
		void increment_nodeCounter()					{ ++nodeCounter; }		// Increment nodeCounter
		void decrement_nodeCounter()					{ --nodeCounter; }		// Decrement nodeCounter


		/*************************************************************************************
			getHeightHelper - Protected
			- Recursively goes through the tree to count the height of the tree
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: an int (the height)
		*************************************************************************************/
		int getHeightHelper(BinaryNode<DataType>* subTreePtr) const;


		
		/*************************************************************************************
			destroyTree - Protected
			- Recursively deletes all nodes from the tree.
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: none
		*************************************************************************************/
		void destroyTree(BinaryNode<DataType>* subTreePtr);


		
		/*************************************************************************************
			insertInorder - Protected
			- Recursively adds a new node to the tree in a left/right fashion to keep the tree balanced. 
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ a BinaryNode pointer to new node needed to be inserted
			- Return: a BinaryNode pointer
		*************************************************************************************/
		BinaryNode<DataType>* insertInorder(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr);

		

		/*************************************************************************************
			removeValue - Protected
			- It removes value indicated in the parameter 
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ a DataType value needs to be removed
				+ a booline to indicate success or not
			- Return: a BinaryNode pointer

			removeValue calls removeNode calls removeLeftMostNode
		*************************************************************************************/
		BinaryNode<DataType>* removeValue(BinaryNode<DataType>* subTreePtr, DataType target, bool& success);
		BinaryNode<DataType>* removeNode(BinaryNode<DataType>* nodePtr);
		BinaryNode<DataType>* removeLeftMostNode(BinaryNode<DataType>* nodePtr, DataType& inorderSuccesssor);


		
		/*************************************************************************************
			findNode - Protected
			- Recursively searches for target value in the tree by using a preorder traversal.
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
				+ a DataType value needs to be found
				+ a booline to indicate successfully found or not
			- Return: a BinaryNode pointer to the node found
		*************************************************************************************/
		BinaryNode<DataType>* findNode(BinaryNode<DataType>* treePtr, const DataType& target, bool& success);


		
		/*************************************************************************************
			findNode - Protected
			- Copies the tree rooted at treePtr
			- Parameters:
				+ a BinaryNode pointer to a node of the tree
			- Return: a BinaryNode pointer of the new copied tree

			Mainly used in constructors
		*************************************************************************************/
		BinaryNode<DataType>*copyTree(const BinaryNode<DataType>* treePtr) const;



		// RECURSIVE TRAVERAL HELPER METHODS:

			/*************************************************************************************
				IN ORDER - Protected
					- It recursively traverse inorder through the tree
					- Parameters:
						+ a void function visit that takes DataType parameter
						+ a BinaryNode pointer to a particular node of the tree
					- Return: none

				Algorithm Inorder(tree)
				1. Traverse the left subtree, i.e., call Inorder(left-subtree)
				2. Visit the root.
				3. Traverse the right subtree, i.e., call Inorder(right-subtree)
			*************************************************************************************/
			void inorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const;


			/*************************************************************************************
				PRE ORDER - Protected
					- It recursively traverse preorder through the tree
					- Parameters:
						+ a void function visit that takes DataType parameter
						+ a BinaryNode pointer to a particular node of the tree
					- Return: none

				Algorithm Preorder(tree)
				1. Visit the root.
				2. Traverse the left subtree, i.e., call Preorder(left-subtree)
				3. Traverse the right subtree, i.e., call Preorder(right-subtree)
			*************************************************************************************/
			void preorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const;


			/*************************************************************************************
			POST ORDER - Protected
				- It recursively traverse postorder through the tree
				- Parameters:
					+ a void function visit that takes DataType parameter
					+ a BinaryNode pointer to a particular node of the tree
				- Return: none

				Algorithm Postorder(tree)
				1. Traverse the left subtree, i.e., call Postorder(left-subtree)
				2. Traverse the right subtree, i.e., call Postorder(right-subtree)
				3. Visit the root.
			*************************************************************************************/
			void postorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const;




	public:
		//------------------------------------------------------------
		// Constructor and Destructor Section.
		//------------------------------------------------------------
		BinarySearchTree() : rootPtr(nullptr), nodeCounter(0) {}

		BinarySearchTree(const DataType& rootItem) { rootPtr = new BinaryNode<DataType>(rootItem, nullptr, nullptr); }

		BinarySearchTree(const DataType& rootItem, const BinarySearchTree<DataType>*
			leftTreePtr, const BinarySearchTree<DataType>* rightTreePtr); // Definition below

		BinarySearchTree(const BinarySearchTree<DataType>& treePtr) { rootPtr = copyTree(treePtr.rootPtr); }// copy constructor
		virtual ~BinarySearchTree()								    { destroyTree(rootPtr); }				// Destructor


		//------------------------------------------------------------
		// Public BinaryTreeInterface Methods Section.
		//------------------------------------------------------------
		bool isEmpty() const			{ if (nodeCounter < 1) return true; else return false; }// True: tree empty
		int getHeight() const			{ return getHeightHelper(rootPtr); }					// Get height of the tree
		int getNumberOfNodes() const	{ return nodeCounter; }									// Total nodes in the tree

		

		virtual bool add(const DataType& newData);												// Adds a node
		virtual bool remove(DataType target);													// Removes a node
		void clear() { destroyTree(rootPtr); }													// Delete all nodes of the tree

		BinaryNode<DataType>* getEntry_address(const DataType& anEntry);						// Get address of a data
		bool is_contained(const DataType& anEntry);												// Check if an entry is existed in the tree
		
		DataType showRoot() { return rootPtr->getItem(); } // TEMPORARY


		//------------------------------------------------------------
		// Public Traversals Section.
		//------------------------------------------------------------
		void inorderTraverse(void visit(DataType&)) const	{ inorder(visit, rootPtr); }
		void postorderTraverse(void visit(DataType&)) const { postorder(visit, rootPtr); }
		void preorderTraverse(void visit(DataType&)) const	{ preorder(visit, rootPtr); }
};




// CONSTRUCTOR - Public
template<class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& rootItem,
	const BinarySearchTree<DataType>* leftTreePtr,
	const BinarySearchTree<DataType>* rightTreePtr)
{
	nodeCounter = 0;
	rootPtr = new BinaryNode<DataType>(rootItem, copyTree(leftTreePtr->rootPtr),
		copyTree(rightTreePtr->rootPtr));
	nodeCounter++;
}

// COPYTREE
template< class DataType>
BinaryNode<DataType>* BinarySearchTree<DataType>::copyTree(const BinaryNode<DataType>* treePtr) const
{
	BinaryNode<DataType>* newTreePtr = nullptr;
	// Copy tree nodes during a preorder traversal
	if (treePtr != nullptr)
	{
		// Copy node
		newTreePtr = new BinaryNode<DataType>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	} // end if
	// Else tree is empty (newTreePtr is nullptr)
	return newTreePtr;
} // end copyTree 



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		GET HEIGHT
//		 - And supporting function
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// MAX FUNCTION for getHeightHelper
	int max(int l, int r)
	{
		if (l > r) return l;
		else return r;
	}

	// GET HEIGHT
	template< class DataType>
	int BinarySearchTree<DataType>::getHeightHelper(BinaryNode<DataType>* subTreePtr) const
	{
		if (subTreePtr == nullptr)
			return 0;
		else
			return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()),
			getHeightHelper(subTreePtr->getRightChildPtr()));
	} // end getHeightHelper 



//DESTROY TREE - Protected
template< class DataType>
void BinarySearchTree<DataType>::destroyTree(BinaryNode<DataType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
		nodeCounter--;
	} // end if
	rootPtr = nullptr;
} // end destroyTree 



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		GET ENTRY & CONTAIN
//		 - And supporting function
//			+ findNode - protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// FIND NODE
	template<class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::findNode(BinaryNode<DataType>* treePtr, const DataType& target, bool& success)
	{
		if (treePtr == nullptr)
		{
			success = false;
			return nullptr;
		}


		if (target < treePtr->getItem())
			return findNode(treePtr->getLeftChildPtr(), target, success);
		else if (target > treePtr->getItem())
			return findNode(treePtr->getRightChildPtr(), target, success);
		else
		{
			success = true;
			return treePtr;
		}
	} // end findNode


	// GET ENTRY
	template<class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::getEntry_address(const DataType& anEntry)
	{
		bool isFound = false;
		BinaryNode<DataType>* entry_address = findNode(rootPtr, anEntry, isFound);
		return entry_address;
	}

	// IS CONTAINED?
	template<class DataType>
	bool BinarySearchTree<DataType>::is_contained(const DataType& anEntry)
	{
		bool isFound = false;
		BinaryNode<DataType>* result = findNode(rootPtr, anEntry, isFound);
		return isFound;
	}



//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		ADD - Public
//		 - and supporting add method: INSERT INORDER - Protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// ADD
	template< class DataType>
	bool BinarySearchTree<DataType>::add(const DataType& newData)
	{
		BinaryNode<DataType>* newNodePtr = new BinaryNode<DataType>(newData);
		rootPtr = insertInorder(rootPtr, newNodePtr);
		nodeCounter++;
		cout << "Added " << newData << " Total Nodes: " << nodeCounter << endl;
		return true;
	} // end add

	// INSERT INORDER - for ADD
	template< class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::insertInorder(BinaryNode<DataType>* subTreePtr, BinaryNode<DataType>* newNodePtr)
	{
		BinaryNode<DataType>* tempPtr = nullptr;

		if (subTreePtr == nullptr)
			return newNodePtr;

		else if (subTreePtr->getItem() > newNodePtr->getItem())
		{
			tempPtr = insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr);
			subTreePtr->setLeftChildPtr(tempPtr);
		}
		else
		{
			tempPtr = insertInorder(subTreePtr->getRightChildPtr(), newNodePtr);
			subTreePtr->setRightChildPtr(tempPtr);
		}
		return subTreePtr;
	}




//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		REMOVE - Public
//		 - and supporting methods: 
//			+ removeValue - Protected
//			+ removeNode  - Protected 
//			+ removeLeftMostNode - Protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	// REMOVE
	template< class DataType>
	bool BinarySearchTree<DataType>::remove(DataType target)
	{
		bool success = false;
		rootPtr = removeValue(rootPtr, target, success);
		if (success == true) nodeCounter--;
		cout << "Total Nodes: " << nodeCounter << endl;
		return success;
	} // end remove

	// REMOVE VALUE
	template< class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::removeValue(BinaryNode<DataType>* subTreePtr, DataType target, bool& success)
	{
		BinaryNode<DataType>* tempPtr = nullptr;

		if (subTreePtr == nullptr)
		{
			success = false;
			return nullptr;
		}
		else if (subTreePtr->getItem() == target)
		{
			// Item is in the root of some subtree
			subTreePtr = removeNode(subTreePtr); // Remove item
			success = true;
			return subTreePtr;
		}
		else if (subTreePtr->getItem() > target)
		{
			tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
			subTreePtr->setLeftChildPtr(tempPtr);
			return subTreePtr;
		}
		else
		{
			tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
			subTreePtr->setRightChildPtr(tempPtr);
			return subTreePtr;
		}
	} // End remove value

	// REMOVE NODE
	template< class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::removeNode(BinaryNode<DataType>* nodePtr)
	{
		BinaryNode<DataType>* tempPtr = nullptr;
		if (nodePtr->isLeaf() == true)
		{
			//Remove leaf from the tree
			delete nodePtr;
			nodePtr = nullptr;
			return nodePtr;
		}
		else if (nodePtr->getLeftChildPtr() != nullptr && nodePtr->getRightChildPtr() != nullptr) // has two children
		{
			DataType newNodeValue;
			tempPtr = removeLeftMostNode(nodePtr->getRightChildPtr(), newNodeValue);
			nodePtr->setRightChildPtr(tempPtr);
			nodePtr->setItem(newNodeValue);
			return nodePtr;
		}
		else
		{
			if (nodePtr->getLeftChildPtr() != nullptr)
				tempPtr = nodePtr->getLeftChildPtr();
			else
			{
				tempPtr = nodePtr->getRightChildPtr();
			}	
			delete nodePtr;
			nodePtr = nullptr;
			return tempPtr;
			
		}
	} // End removeNode


	// REMOVE LEFT MOST NODE
	template< class DataType>
	BinaryNode<DataType>* BinarySearchTree<DataType>::removeLeftMostNode(BinaryNode<DataType>* nodePtr, DataType& inorderSuccesssor)
	{
		if (nodePtr->getLeftChildPtr() == nullptr)
		{
			inorderSuccesssor = nodePtr->getItem();
			return removeNode(nodePtr);
		}
		else
			return removeLeftMostNode(nodePtr->getLeftChildPtr(), inorderSuccesssor);
	} // End remove left most node





//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
//		TRAVERAL methods - protected
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------

	// IN ORDER
	template< class DataType>
	void BinarySearchTree<DataType>::inorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const
	{
		if (treePtr != nullptr)
		{
			inorder(visit, treePtr->getLeftChildPtr());

			cout << "Inorder: " << treePtr->getItem() << endl;

			DataType theItem = treePtr->getItem();
			visit(theItem);

			inorder(visit, treePtr->getRightChildPtr());

		} // end if
	} // end inorder 



	// PRE ORDER
	template< class DataType>
	void BinarySearchTree<DataType>::preorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const
	{
		if (treePtr != nullptr)
		{
			DataType theItem = treePtr->getItem();
			visit(theItem);

			cout << "Pre-order: " << treePtr->getItem() << endl;

			preorder(visit, treePtr->getLeftChildPtr());

			preorder(visit, treePtr->getRightChildPtr());

		} // end if
	} // end preorder 


	// POST ORDER
	template< class DataType>
	void BinarySearchTree<DataType>::postorder(void visit(DataType&), BinaryNode<DataType>* treePtr) const
	{
		if (treePtr != nullptr)
		{
			postorder(visit, treePtr->getLeftChildPtr());

			postorder(visit, treePtr->getRightChildPtr());

			DataType theItem = treePtr->getItem();
			visit(theItem);

			cout << "Post-order: " << treePtr->getItem() << endl;
		} // end if
	} // end postorder 