#ifndef _BINARYNODE
#define _BINARYNODE

template<class DataType>
class BinaryNode
{
private:
	DataType item;							// Data portion
	BinaryNode<DataType>* leftChildPtr;		// Pointer to left child
	BinaryNode<DataType>* rightChildPtr;	// Pointer to right child

public:
	// Default constructor: initialize two right and left pointer to nullptr
	BinaryNode() :leftChildPtr(0), rightChildPtr(0){}
	// Constructor 1: initialize item = anItem input, and two right and left pointer to nullptr
	BinaryNode(const DataType& anItem) : item(anItem), leftChildPtr(0), rightChildPtr(0){}
	// Constructor 2: initialize item, right pointer and left pointer equal to the according parameters 
	BinaryNode(const DataType& anItem, BinaryNode<DataType>* leftPtr, BinaryNode<DataType>* rightPtr):
		item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr){}

	// Check if the node is a leaf (left and right pointers point to null)
	bool isLeaf() const
	{
		if (leftChildPtr == nullptr && rightChildPtr == nullptr)
			return true;
		else return false;
	}

	// Mutators
	DataType getItem() const								{ return item; }
	BinaryNode<DataType>* getLeftChildPtr() const			{ return leftChildPtr; }
	BinaryNode<DataType>* getRightChildPtr() const			{ return rightChildPtr; }

	// Accessors
	void setItem(const DataType& anItem)					{ item = anItem; }
	void setLeftChildPtr(BinaryNode<DataType>* leftPtr)		{ leftChildPtr = leftPtr; }
	void setRightChildPtr(BinaryNode<DataType>* rightPtr)	{ rightChildPtr = rightPtr; }


};
#endif // !_BINARYNODE

