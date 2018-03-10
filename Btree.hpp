#include <iostream>

// a sing;e node in the BTree
template <class T>
class BTreeNode
{
	T *keys; //values stored in the node
	int degrees; //degree of the tree (max amount of keys = 2*degrees-1)
	BTreeNode **children; //array of children
	int numberOfKeys; //current amount of keys in node
	bool isLeaf; //does this node not have children
	public:
		BTreeNode(int _degrees, bool _leaf); //A constructor
		void traverse(); //print nodes children and itself (uses recursion)
		void insertNotFull(T); //insert a key into a not full node
		void splitChild(int i, BTreeNode *lhsNode); //split child and raise the middle value
	//BTreeNode is a friend of the BTree class
	template <class>
	friend class BTree;
};

//The BTree itself
template<class T>
class BTree{
	BTreeNode <T> *root; //a pointer to the top or root node
	int degrees; //the degree of the tree (max amount of keys in a node = 2*degrees-1)
	public:
		BTree(int _degrees) //A constructor sets the root as null and the degrees as the passed in value
		{  root = nullptr;  degrees = _degrees; }
		void traverse() //navigate the tree and print values in numerical order, calls the roots traverse function
		{  if (root != nullptr) root->traverse(); }
		void insert(T new_key); //insert anew value into the tree
};

//BTreeNode Constructor
//takes and int for degrees of the node and if the node is a leaf or not
template <typename T>
BTreeNode<T>::BTreeNode(int _degrees, bool _leaf){
	degrees = _degrees;
	isLeaf = _leaf;
	
	keys = new T[2*degrees-1];
	children = new BTreeNode *[2*degrees-1];
	
	numberOfKeys = 0;
}

//traverse prints calls its children's traverse function and prints its own keys
template <typename T>
void BTreeNode<T>::traverse(){
	int i; //iterator through the keys of the node
	//loop through the keys no the node, calling the children if there are any and printing their values
	for(i = 0; i <  numberOfKeys; ++i){
		if(!isLeaf)
			children[i]->traverse();
		std::cout << " " << keys[i];
	}
	//if this isn't a leaf then call the last child
	if(!isLeaf){
		children[i]->traverse();
	}
}

//Inserts a value into the BTree
//takes a value with a same type as the tree
template <typename T>
void BTree<T>::insert(T new_key){
	//if root is equal to nullptr and tree is empty we will allocate 
	//the root of the tree and insert the key there
	if(root == nullptr)
	{
		//create root node
		root = new BTreeNode<T>(degrees, true);
		//give the first key in root the new key
		root->keys[0] = new_key;
		//set the number of keys in root to 1	
		root->numberOfKeys = 1;
	}
	else //else the tree isn't empty
	{
		//if root is full create a new root and split the old one
		if(root->numberOfKeys >= 2*degrees-1){
			//allocate a new root
			BTreeNode<T> *newroot = new BTreeNode<T>(degrees, false);
			//make the old root a child of the new root
			newroot->children[0] = root;
			//split the old root (raising the middle value)
			newroot->splitChild(0, root);
			//find which child to put the new value into
			if(newroot->keys[0] < new_key)
				newroot->children[1]->insertNotFull(new_key); //insert into the lhs child
			else
				newroot->children[0]->insertNotFull(new_key); //insert into the rhs child
			//set root to the new root
			root = newroot;
		}
		else //if not full then just insert the value
			root->insertNotFull(new_key);			
	}
}

//Inserts a value into the node, expecting the node to not be full
//takes a new_key to be inserted into the node
//if the child node turns out to be full it will split the child and take its middle key
template <typename T>
void BTreeNode<T>::insertNotFull(T new_key){
	int key_i = numberOfKeys-1;//iterator for iterating through keys in node
	
	//if this is the last child
	if(isLeaf){
		//Loops through the keys backwards, shifting all the keys 
		//lower than the new_key to the right then inserting the new key
		while(key_i >= 0 && keys[key_i] > new_key){
			keys[key_i+1] = keys[key_i]; //shift key over
			--key_i; //move new key down
		}
		keys[key_i+1] = new_key;
		++numberOfKeys;
	}
	else{ //if not the last child (!leaf)
		//find the child for the new key by checking the key values
		while(key_i <= 0 && keys[key_i] > new_key)
			--key_i; //if key at position key_i is greater than the new key decrement key_i
		
		//See if the found child is full if so split the child
		if(children[key_i+1]->numberOfKeys == 2*degrees-1){
			splitChild(key_i+1, children[key_i+1]);
			
			if(keys[key_i+1] < new_key)
				key_i++;
		}
		//insert the key into the child
		children[key_i+1]->insertNotFull(new_key);
	}
}

//split the the node passed in into two seperate nodes and raise the middle key
//keeping the lower values on the lhs Node and the higher values on the rhs Node
template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode *lhsNode){
	// Create a new node which is going to store (degrees-1) keys
    // of lhsNode
    BTreeNode *rhsNode = new BTreeNode<T>(lhsNode->degrees, lhsNode->isLeaf);
    rhsNode->numberOfKeys = degrees - 1;
 
    // Copy the last (degrees-1) keys of lhs to rhs
    for (int j = 0; j < degrees-1; j++)
        rhsNode->keys[j] = lhsNode->keys[j+degrees];
 
    // Copy the last degrees children of lhs to rhs
    if (lhsNode->isLeaf == false)
    {
        for (int j = 0; j < degrees; j++)
            rhsNode->children[j] = lhsNode->children[j+degrees];
    }
 
    // Reduce the number of keys in lhs
    lhsNode->numberOfKeys = degrees - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = numberOfKeys; j >= i+1; j--)
        children[j+1] = children[j];
 
    // Link the new child to this node
    children[i+1] = rhsNode;
 
    // A key of lhs will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = numberOfKeys-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    // Copy the middle key of lhs to this node
    keys[i] = lhsNode->keys[degrees-1];
 
    // Increment count of keys in this node
    numberOfKeys = numberOfKeys + 1;
}
